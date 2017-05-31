#include <QString>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestPartDataTransformAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

void TransformData(ContextPtr context, QString const &destKey, IntContextItem *sourceItem, IntContextItem *destItem, int start)
{
    bool transformed = false;
    for (int index = start; index < sourceItem->Data.length(); ++index)
    {
        transformed = true;
        int sourceValue = sourceItem->Data[index];
        destItem->Data.append(sourceValue + 90000);
        destItem->Data.append(sourceValue + 91000);
        destItem->Data.append(sourceValue + 92000);
    }
    if (transformed)
        emit context.get()->DataChanged(destKey);
}

}

TestPartDataTransformAction::TestPartDataTransformAction(QString const &name, QString const &sourceKey, QString const &destKey, ContextPtr context) :
    IAction(context),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey)
{
    context.get()->Set(_destKey, IntContextItemPtr(new IntContextItem()));
}

QString TestPartDataTransformAction::GetName()
{
    return _name;
}

/*void TestPartDataTransformAction::StartAction(Context &context)
{
}*/

/*void TestPartDataTransformAction::Run(Context &context)
{
}*/

void TestPartDataTransformAction::ProcessStartImpl()
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
}

void TestPartDataTransformAction::ProcessStopImpl()
{
    // do nothing
}

void TestPartDataTransformAction::ProcessData()
{
    ContextPtr context = GetContext();
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    TransformData(context, _destKey, sourceItem, destItem, _index + 1);
    _index = sourceItem->Data.length() - 1;
}

void TestPartDataTransformAction::FinishProcessData()
{
    ContextPtr context = GetContext();
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    TransformData(context, _destKey, sourceItem, destItem, _index + 1);
    emit context.get()->DataCompleted(_destKey);

}

}
