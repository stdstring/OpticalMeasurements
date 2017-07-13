#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"
#include "ConfigReader.h"

namespace CalcApp
{

namespace
{

constexpr QChar CommentStart = '#';

constexpr int ServerConfigLinesCount = 4;

//const int ExpectedMessageDefParts = 3;
constexpr int MinMessageDefParts = 3;

typedef std::map<QString, MessageType> MessageTypeMapType;

MessageTypeMapType MessageTypeMap =
{
    {"REQUEST", MessageType::REQUEST},
    {"RESPONSE", MessageType::RESPONSE},
    {"DATA", MessageType::DATA},
    {"EVENT", MessageType::EVENT}
};

typedef std::map<QString, std::function<QByteArray(QString const&)>> DataConvertMapType;

DataConvertMapType DataConvertMap =
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

bool IsResponseRequired(QList<MessagePtr> const &messages)
{
    return (messages.size() > 0) && (messages.last().get()->GetType() == MessageType::REQUEST);
}

void ProcessResponseRequired(QList<MessagePtr> &messages)
{
    if (IsResponseRequired(messages))
        messages.append(std::make_shared<Message>(MessageType::RESPONSE, QByteArray()));
}

void ProcessRequest(QList<MessagePtr> &messages, QString const &dataType, QStringList &parts)
{
    constexpr int partsCount = 1;
    if (parts.size() != partsCount)
        return;
    ProcessResponseRequired(messages);
    DataConvertMapType::const_iterator dataIterator = DataConvertMap.find(dataType);
    if (DataConvertMap.cend() == dataIterator)
        return;
    QByteArray messageBody = dataIterator->second(parts[0]);
    messages.append(std::make_shared<Message>(MessageType::REQUEST, messageBody));
}

void ProcessResponse(QList<MessagePtr> &messages, QString const &dataType, QStringList &parts)
{
    constexpr int partsCount = 1;
    if (parts.size() != partsCount)
        return;
    if (!IsResponseRequired(messages))
        return;
    DataConvertMapType::const_iterator dataIterator = DataConvertMap.find(dataType);
    if (DataConvertMap.cend() == dataIterator)
        return;
    QByteArray messageBody = dataIterator->second(parts[0]);
    messages.append(std::make_shared<Message>(MessageType::RESPONSE, messageBody));
}

void ProcessEvent(QList<MessagePtr> &messages, QString const &dataType, QStringList &parts)
{
    constexpr int partsCount = 1;
    if (parts.size() != partsCount)
        return;
    ProcessResponseRequired(messages);
    DataConvertMapType::const_iterator dataIterator = DataConvertMap.find(dataType);
    if (DataConvertMap.cend() == dataIterator)
        return;
    QByteArray messageBody = dataIterator->second(parts[0]);
    messages.append(std::make_shared<Message>(MessageType::EVENT, messageBody));
}

void ProcessData(QList<MessagePtr> &messages, QString const &dataType, QStringList &parts)
{
    constexpr int partsCount = 3;
    if (parts.size() != partsCount)
        return;
    ProcessResponseRequired(messages);
    int packageNumber = Convert<int>(parts[0]);
    int calcNumber = Convert<int>(parts[1]);
    DataConvertMapType::const_iterator dataIterator = DataConvertMap.find(dataType);
    if (DataConvertMap.cend() == dataIterator)
        return;
    QByteArray data = dataIterator->second(parts[2]);
    QByteArray messageBody;
    QDataStream stream(&messageBody, QIODevice::WriteOnly);
    stream.setVersion(DataStreamVersion);
    stream << packageNumber << calcNumber << data;
    messages.append(std::make_shared<Message>(MessageType::DATA, messageBody));
}

typedef std::map<MessageType, std::function<void(QList<MessagePtr>&, QString const&, QStringList&)>> MessageProcessMapType;

MessageProcessMapType MessageProcessMap =
{
    {MessageType::REQUEST, ProcessRequest},
    {MessageType::RESPONSE, ProcessResponse},
    {MessageType::EVENT, ProcessEvent},
    {MessageType::DATA, ProcessData}
};

void ProcessMessageLine(QList<MessagePtr> &messages, QString const &line)
{
    if (line.isEmpty())
        return;
    QStringList parts = line.split(QRegExp("\\s+"));
    // TODO (std_string) : write some warning
    if (parts.size() < MinMessageDefParts)
        return;
    MessageTypeMapType::const_iterator messageTypeIterator = MessageTypeMap.find(parts.takeFirst());
    if (messageTypeIterator == MessageTypeMap.cend())
        return;
    MessageType messageType = messageTypeIterator->second;
    QString dataType = parts.takeFirst();
    MessageProcessMapType::const_iterator messageProcessIterator = MessageProcessMap.find(messageType);
    if (messageProcessIterator == MessageProcessMap.cend())
        return;
    messageProcessIterator->second(messages, dataType, parts);
}

/*void ProcessMessageLine(QList<MessagePtr> &messages, QString const &line)
{
    if (line.isEmpty())
        return;
    QStringList parts = line.split(QRegExp("\\s+"));
    // TODO (std_string) : write some warning
    if (parts.size() != ExpectedMessageDefParts)
        return;
    MessageTypeMapType::const_iterator messageTypeIterator = MessageTypeMap.find(parts[0]);
    if (messageTypeIterator == MessageTypeMap.cend())
        return;
    MessageType messageType = messageTypeIterator->second;
    bool responseRequired = IsResponseRequired(messages);
    if (!responseRequired && messageType == MessageType::RESPONSE)
        return;
    if (responseRequired && messageType != MessageType::RESPONSE)
        messages.append(std::make_shared<Message>(MessageType::RESPONSE, QByteArray()));
    MessageBodyConvertMapType::const_iterator messageBodyIterator = MessageBodyConvertMap.find(parts[1]);
    if (messageBodyIterator == MessageBodyConvertMap.cend())
        return;
    QByteArray messageBody = messageBodyIterator->second(parts[2]);
    messages.append(std::make_shared<Message>(messageType, messageBody));
}*/

}

std::tuple<TestServerConfig, QList<MessagePtr>> ReadConfig(QString const &filename)
{
    QFile configFile(filename);
    configFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&configFile);
    QStringList serverConfigLines = ReadLines(textStream, ServerConfigLinesCount);
    if (serverConfigLines.size() < ServerConfigLinesCount)
        // TODO (std_string) : think about type of generated exception
        throw std::logic_error("Bad config");
    TestServerConfig serverConfig = CreateServerConfig(serverConfigLines);
    QList<MessagePtr> messages;
    while (!textStream.atEnd())
    {
        QString line = ReadLine(textStream);
        ProcessMessageLine(messages, line);
    }
    if (IsResponseRequired(messages))
        messages.append(std::make_shared<Message>(MessageType::RESPONSE, QByteArray()));
    return std::tuple<TestServerConfig, QList<MessagePtr>>(serverConfig, messages);
}

}
