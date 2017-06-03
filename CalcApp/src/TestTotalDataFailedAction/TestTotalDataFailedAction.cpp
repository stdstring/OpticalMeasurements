#include <QString>

#include <exception>
#include <memory>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/IAction.h"
#include "TestTotalDataFailedAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

}

TestTotalDataFailedAction::TestTotalDataFailedAction(QString const &name, QString const &sourceKey, QString const &destKey, int failedIteration, ContextPtr context) :
    IAction(context),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey),
    _failedIteration(failedIteration)
{
    context.get()->Set(_destKey, IntContextItemPtr(new IntContextItem()));
}

QString TestTotalDataFailedAction::GetName()
{
    return _name;
}

/*void TestTotalDataFailedAction::StartAction(Context &context)
{
}*/

/*void TestTotalDataFailedAction::Run(Context &context)
{
}*/

void TestTotalDataFailedAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _sourceKey)
            ProcessTotalData();
    });
}

void TestTotalDataFailedAction::ProcessStopImpl()
{
    // do nothing
}

void TestTotalDataFailedAction::ProcessTotalData()
{
    ContextPtr context = GetContext();
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    for (int index = 0; index < sourceItem->Data.size(); ++index)
    {
        int sourceValue = sourceItem->Data[index];
        destItem->Data.append(sourceValue);
        if (index == _failedIteration)
        {
            ExceptionData exception(std::make_exception_ptr(std::logic_error("some error")));
            emit ErrorOccured(exception);
            return;
        }
    }
    emit destItem->NotifyDataChange();
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

}
