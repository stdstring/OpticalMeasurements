#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QReadLocker>
#include <QString>
#include <QTextStream>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestSaveDataAction.h"

namespace CalcApp
{

namespace
{

void SaveData(QTextStream &stream, QStringListContextItem *item, int start)
{
    QReadLocker locker(&item->Lock);
    for (int index = start; index < item->Data.length(); ++index)
    {
        QString value  = item->Data[index];
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : " << value << endl;
    }
}

void SaveData(QString const &filename, QStringListContextItem *item, int start, bool lastSave)
{
    QFile file(filename);
    file.open(start == 0 ? QIODevice::WriteOnly : QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    if (start == 0)
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : start" << endl;
    SaveData(stream, item, start);
    if (lastSave)
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : finish" << endl;
}

}

TestSaveDataAction::TestSaveDataAction(QString const &actionName, QString const &key, QString const &filename, ContextPtr context) :
    IAction(context),
    _actionName(actionName),
    _key(key),
    _filename(filename)
{
}

QString TestSaveDataAction::GetName()
{
    return _actionName;
}

/*void TestSaveDataAction::StartAction(Context &context)
{
}*/

/*void TestSaveDataAction::Run(Context &context)
{
}*/

void TestSaveDataAction::CleanupAtFailure()
{
}

void TestSaveDataAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataChanged, this, [this](QString const &key){
        if (key == _key)
            ProcessData();
    });
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _key)
            FinishProcessData();
    });
    _index = -1;
}

void TestSaveDataAction::ProcessStopImpl()
{
}

void TestSaveDataAction::ProcessData()
{
    ProcessData(false);
}

void TestSaveDataAction::FinishProcessData()
{
    ProcessData(true);
    emit ActionFinished();
}

void TestSaveDataAction::ProcessData(bool last)
{
    ContextPtr context = GetContext();
    QStringListContextItem *item = context.get()->GetValue<QStringListContextItem>(_key);
    SaveData(_filename, item, _index + 1, last);
    _index = item->Data.length() - 1;
}

}

