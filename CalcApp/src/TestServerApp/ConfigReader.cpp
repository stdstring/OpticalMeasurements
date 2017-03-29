#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <functional>
#include <map>
#include <stdexcept>
#include <tuple>

#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"
#include "ConfigReader.h"

namespace CalcApp
{

namespace
{

const QChar CommentStart = '#';

const int ServerConfigLinesCount = 4;

const int ExpectedMessageDefParts = 3;

std::map<QString, MessageType> MessageTypeMap =
{
    {"REQUEST", MessageType::REQUEST},
    {"RESPONSE", MessageType::RESPONSE},
    {"DATA", MessageType::DATA},
    {"EVENT", MessageType::EVENT}
};

std::map<QString, std::function<QByteArray(QString const&)>> MessageBodyConvertMap =
{
    {"HEX", [](QString const &source){ return QByteArray::fromHex(source.toUtf8()); }},
    {"BASE64", [](QString const &source){ return QByteArray::fromBase64(source.toUtf8()); }}
};

template <typename TResult> TResult Convert(QString &data)
{
    TResult result;
    QTextStream textStream(&data, QIODevice::OpenModeFlag::ReadOnly);
    textStream >> result;
    if (!textStream.atEnd())
        // TODO (std_string) : think about type of generated exception
        throw std::logic_error("Bad convertation");
    return result;
}

QString ReadLine(QTextStream &stream)
{
    QString line = stream.readLine().trimmed();
    return (line.size() > 0 && line[0] == CommentStart) ? QString() : line;
}

QStringList ReadLines(QTextStream &stream, int count)
{
    QStringList dest;
    while (!stream.atEnd() && dest.size() < count)
    {
        QString line = ReadLine(stream);
        if (!line.isEmpty())
            dest.append(line);
    }
    return dest;
}

TestServerConfig CreateServerConfig(QStringList &lines)
{
    int timerInterval = Convert<int>(lines[0]);
    // TODO (std_string) : check server address in future
    QString &serverAddress = lines[1];
    quint16 tcpPortNumber = Convert<quint16>(lines[2]);
    quint16 udpPortNumber = Convert<quint16>(lines[3]);
    return TestServerConfig(timerInterval, serverAddress, tcpPortNumber, udpPortNumber);
}

bool IsResponseRequired(QList<Message> const &messages)
{
    return (messages.size() > 0) && (messages.last().GetType() == MessageType::REQUEST);
}

void ProcessMessageLine(QList<Message> &messages, QString const &line)
{
    if (line.isEmpty())
        return;
    QStringList parts = line.split(QRegExp("\\s+"));
    // TODO (std_string) : write some warning
    if (parts.size() != ExpectedMessageDefParts)
        return;
    std::map<QString, MessageType>::const_iterator messageTypeIterator = MessageTypeMap.find(parts[0]);
    if (messageTypeIterator == MessageTypeMap.cend())
        return;
    MessageType messageType = messageTypeIterator->second;
    bool responseRequired = IsResponseRequired(messages);
    if (!responseRequired && messageType == MessageType::RESPONSE)
        return;
    if (responseRequired && messageType != MessageType::RESPONSE)
        messages.append(Message(MessageType::RESPONSE, QByteArray()));
    std::map<QString, std::function<QByteArray(QString const&)>>::const_iterator messageBodyIterator = MessageBodyConvertMap.find(parts[1]);
    if (messageBodyIterator == MessageBodyConvertMap.cend())
        return;
    QByteArray messageBody = messageBodyIterator->second(parts[2]);
    messages.append(Message(messageType, messageBody));
}

}

std::tuple<TestServerConfig, QList<Message>> ConfigReader::Read(QString const &filename)
{
    QFile configFile(filename);
    QTextStream textStream(&configFile);
    QStringList serverConfigLines = ReadLines(textStream, ServerConfigLinesCount);
    if (serverConfigLines.size() < ServerConfigLinesCount)
        // TODO (std_string) : think about type of generated exception
        throw std::logic_error("Bad config");
    TestServerConfig serverConfig = CreateServerConfig(serverConfigLines);
    QList<Message> messages;
    while (!textStream.atEnd())
    {
        QString line = ReadLine(textStream);
        ProcessMessageLine(messages, line);
    }
    if (IsResponseRequired(messages))
        messages.append(Message(MessageType::RESPONSE, QByteArray()));
    return std::tuple<TestServerConfig, QList<Message>>(serverConfig, messages);
}

}
