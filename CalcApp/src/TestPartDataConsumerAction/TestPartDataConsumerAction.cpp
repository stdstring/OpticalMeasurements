#include <QDateTime>
#include <QFile>
#include <QIODevice>
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
    for (int index = start; index < item->Data.length(); ++index)
    {
        int value  = item->Data[index];
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : value =" << value << endl;
    }
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
    ContextPtr context = GetContext();
    IntContextItem *item = context.get()->GetValue<IntContextItem>(_key);
    if (_index == -1)
    {
        QFile destFile(_filename);
        destFile.open(QIODevice::WriteOnly);
        QTextStream stream(&destFile);
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : start" << endl;
        SaveData(stream, item, 0);
    }
    else
    {
        QFile destFile(_filename);
        destFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream stream(&destFile);
        SaveData(stream, item, _index + 1);
    }
    _index = item->Data.length() - 1;
}

void TestPartDataConsumerAction::FinishProcessData()
{
    QFile destFile(_filename);
    destFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&destFile);
    stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : finish" << endl;
}

}
