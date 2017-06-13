#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QReadLocker>
#include <QString>
#include <QTextStream>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestPartDataConsumerAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

void SaveData(QTextStream &stream, IntContextItem *item, int start)
{
    QReadLocker locker(&item->Lock);
    for (int index = start; index < item->Data.length(); ++index)
    {
        int value  = item->Data[index];
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : value = " << value << endl;
    }
}

void SaveData(QString const &filename, IntContextItem *item, int start, bool lastSave)
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

TestPartDataConsumerAction::TestPartDataConsumerAction(QString const &name, QString const &key, QString const &filename, ContextPtr context) :
    IAction(context),
    _name(name),
    _key(key),
    _filename(filename)
{
}

QString TestPartDataConsumerAction::GetName()
{
    return _name;
}

/*void TestPartDataConsumerAction::StartAction(Context &context)
{
}*/

/*void TestPartDataConsumerAction::Run(Context &context)
{
}*/

void TestPartDataConsumerAction::CleanupAtFailure()
{
}

void TestPartDataConsumerAction::ProcessStartImpl()
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

void TestPartDataConsumerAction::ProcessStopImpl()
{
    // do nothing
}

void TestPartDataConsumerAction::ProcessData()
{
    ProcessData(false);
}

void TestPartDataConsumerAction::FinishProcessData()
{
    ProcessData(true);
    emit ActionFinished();
}

void TestPartDataConsumerAction::ProcessData(bool last)
{
    ContextPtr context = GetContext();
    IntContextItem *item = context.get()->GetValue<IntContextItem>(_key);
    SaveData(_filename, item, _index + 1, last);
    _index = item->Data.length() - 1;
}

}
