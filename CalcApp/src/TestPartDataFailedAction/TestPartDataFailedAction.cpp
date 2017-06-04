#include <QString>

#include <exception>
#include <memory>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/IAction.h"
#include "TestPartDataFailedAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

}

TestPartDataFailedAction::TestPartDataFailedAction(QString const &name, QString const &sourceKey, QString const &destKey, int failedIteration, ContextPtr context) :
    IAction(context),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey),
    _failedIteration(failedIteration)
{
    context.get()->Set(_destKey, IntContextItemPtr(new IntContextItem()));
}

QString TestPartDataFailedAction::GetName()
{
    return _name;
}

/*void TestPartDataFailedAction::StartAction(Context &context)
{
}*/

/*void TestPartDataFailedAction::Run(Context &context)
{
}*/

void TestPartDataFailedAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataChanged, this, [this](QString const &key){
        if (key == _sourceKey)
            ProcessData();
    });
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _sourceKey)
            FinishProcessData();
    });
    _index = -1;
    _failed = false;
}

void TestPartDataFailedAction::ProcessStopImpl()
{
    // do nothing
}

void TestPartDataFailedAction::ProcessData()
{
    if (_failed)
        return;
    ProcessData(GetContext());
}

void TestPartDataFailedAction::FinishProcessData()
{
    if (_failed)
        return;
    ContextPtr context = GetContext();
    ProcessData(context);
    if (_failed)
        return;
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

void TestPartDataFailedAction::ProcessData(ContextPtr context)
{
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    bool transformed = false;
    for (int index = _index + 1; index < sourceItem->Data.length(); ++index)
    {
        transformed = true;
        int sourceValue = sourceItem->Data[index];
        destItem->Data.append(sourceValue);
        if (index == _failedIteration)
        {
            ExceptionData exception(std::make_exception_ptr(std::logic_error("some error")));
            emit ErrorOccured(exception);
            _failed = true;
            return;
        }
    }
    if (transformed)
        emit destItem->NotifyDataChange();
    _index = sourceItem->Data.length() - 1;
}

}