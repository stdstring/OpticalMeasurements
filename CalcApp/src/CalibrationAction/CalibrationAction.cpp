#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QWriteLocker>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/ExecutionState.h"
#include "Common/IAction.h"
#include "Common/ITransport.h"
#include "CalibrationAction.h"

namespace CalcApp
{

namespace
{

const QString CalibrationRequest("CALIBR");
const QString CalibrationResponse("OK");

// TODO (std_string) : probably move into common place
/*QString ReadUtf8CString(QDataStream &stream)
{
    QByteArray utf8String;
    //return QString::fromUtf8()
}*/

// TODO (std_string) : probably move into common place
/*void WriteUtf8CString(QDataStream &stream, QString const &string)
{
    QByteArray utf8String(string.toUtf8());
    stream.writeRawData(utf8String.data(), utf8String.size());
    stream << static_cast<quint8>(0);
}*/

/*QByteArray CreateRequest(QByteArray const &sourceData)
{
    QByteArray dest;
    QDataStream stream(&dest, QIODevice::WriteOnly);
    stream.setVersion(DataStreamVersion);
    WriteUtf8CString(stream, CalibrationRequest);
    stream.writeRawData(sourceData.data(), sourceData.size());
    return dest;
}

QByteArray ExtractResultData(QByteArray const &message)
{
}*/

QByteArray CreateRequest(QByteArray const &sourceData)
{
}

QByteArray ExtractResultData(QByteArray const &message)
{
}

}

CalibrationAction::CalibrationAction(QString const &name, QByteArray const &sourceData, QString const &key, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _sourceData(sourceData),
    _key(key)
{
    context.get()->Set(_key, std::make_shared<QByteArrayContextItem>());
}

QString CalibrationAction::GetName()
{
    return _name;
}

/*void CalibrationAction::StartAction(Context &context)
{
}*/

/*void CalibrationAction::Run(Context &context)
{
}*/

void CalibrationAction::ProcessStartImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::connect(transport.get(), &ITransport::ResponseReceived, this, &CalibrationAction::ProcessResponseReceived);
    QObject::connect(transport.get(), &ITransport::DataReceived, this, &CalibrationAction::ProcessDataReceived);
    QObject::connect(transport.get(), &ITransport::DataProcessFailed, this, &CalibrationAction::ProcessDataProcessFailed);
    QObject::connect(transport.get(), &ITransport::EventReceived, this, &CalibrationAction::ProcessEventReceived);
    transport.get()->Connect();
    transport.get()->Send(std::make_shared<Message>(MessageType::REQUEST, CreateRequest(_sourceData)));
}

void CalibrationAction::ProcessStopImpl()
{
    TransportPtr transport = GetExecutionState().get()->GetTransport();
    QObject::disconnect(transport.get(), &ITransport::ResponseReceived, this, &CalibrationAction::ProcessResponseReceived);
    QObject::disconnect(transport.get(), &ITransport::DataReceived, this, &CalibrationAction::ProcessDataReceived);
    QObject::disconnect(transport.get(), &ITransport::DataProcessFailed, this, &CalibrationAction::ProcessDataProcessFailed);
    QObject::disconnect(transport.get(), &ITransport::EventReceived, this, &CalibrationAction::ProcessEventReceived);
}

void CalibrationAction::CleanupNonFinished()
{
    // Log warning
}

void CalibrationAction::ProcessResponseReceived(MessagePtr message)
{
    QByteArray resultData = ExtractResultData(message.get()->GetData());
    Context *context = GetContext().get();
    QByteArrayContextItem *item = context->GetValue<QByteArrayContextItem>(_key);
    QWriteLocker locker(&item->Lock);
    item->Data.clear();
    item->Data.append(resultData);
    emit context->DataCompleted(_key);
    emit ActionFinished();
}

void CalibrationAction::ProcessDataReceived(MessagePtr message)
{
    // Log warning
}

void CalibrationAction::ProcessDataProcessFailed()
{
    // Log warning
}

void CalibrationAction::ProcessEventReceived(MessagePtr message)
{
    // Log warning
}

}

