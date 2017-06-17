#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QReadLocker>
#include <QString>
#include <QTextStream>
#include <QWriteLocker>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestTotalDataConsumerAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

void SaveData(QTextStream &stream, IntContextItem *item)
{
    QReadLocker locker(&item->Lock);
    for(int value : item->Data)
    {
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : value = " << value << endl;
    }
}

}

TestTotalDataConsumerAction::TestTotalDataConsumerAction(QString const &name, QString const &key, QString const &filename, ContextPtr context) :
    IAction(context),
    _name(name),
    _key(key),
    _filename(filename)
{
}

QString TestTotalDataConsumerAction::GetName()
{
    return _name;
}

/*void TestTotalDataConsumerAction::StartAction(Context &context)
{
}*/

/*void TestTotalDataConsumerAction::Run(Context &context)
{
}*/

void TestTotalDataConsumerAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _key)
            ProcessTotalData();
    });
}

void TestTotalDataConsumerAction::ProcessStopImpl()
{
    // do nothing
}

void TestTotalDataConsumerAction::CleanupNonFinished()
{
    // do nothing
}

void TestTotalDataConsumerAction::ProcessTotalData()
{
    ContextPtr context = GetContext();
    IntContextItem *item = context.get()->GetValue<IntContextItem>(_key);
    QFile destFile(_filename);
    destFile.open(QIODevice::WriteOnly);
    QTextStream stream(&destFile);
    stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : start" << endl;
    SaveData(stream, item);
    stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : finish" << endl;
    emit ActionFinished();
}

}
