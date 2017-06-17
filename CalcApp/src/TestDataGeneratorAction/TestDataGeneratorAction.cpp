#include <QString>
#include <QTimer>
#include <QWriteLocker>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestDataGeneratorAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

void ProcessValue(IntContextItem *item, int value)
{
    QWriteLocker locker(&item->Lock);
    item->Data.append(value);
}

}

TestDataGeneratorAction::TestDataGeneratorAction(QString const &name, QString const &key, int sleepTime, int dataCount, ContextPtr context) :
    IAction(context),
    _name(name),
    _key(key),
    _sleepTime(sleepTime)
{
    context.get()->Set(key, IntContextItemPtr(new IntContextItem()));
    for (int index = 0; index < dataCount; ++index)
    {
        _data.enqueue(index + 1);
    }
}

QString TestDataGeneratorAction::GetName()
{
    return _name;
}

/*void TestDataGeneratorAction::StartAction(Context &context)
{
}*/

/*void TestDataGeneratorAction::Run(Context &context)
{
}*/

void TestDataGeneratorAction::ProcessStartImpl()
{
    QTimer::singleShot(_sleepTime, this, [this](){ emit GenerateNextItem(); });
}

void TestDataGeneratorAction::ProcessStopImpl()
{
    // do nothing
}

void TestDataGeneratorAction::CleanupNonFinished()
{
}

void TestDataGeneratorAction::GenerateNextItem()
{
    ContextPtr context = GetContext();
    IntContextItem *item = context.get()->GetValue<IntContextItem>(_key);
    ProcessValue(item, _data.dequeue());
    emit item->NotifyDataChange();
    if (_data.empty())
    {
        emit context.get()->DataCompleted(_key);
        emit ActionFinished();
    }
    else
    {
        QTimer::singleShot(_sleepTime, this, [this](){ emit GenerateNextItem(); });
    }
}

}
