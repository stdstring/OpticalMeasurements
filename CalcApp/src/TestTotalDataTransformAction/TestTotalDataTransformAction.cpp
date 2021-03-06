#include <QReadLocker>
#include <QString>
#include <QWriteLocker>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestTotalDataTransformAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<int> IntContextItem;
typedef std::shared_ptr<IntContextItem> IntContextItemPtr;

void TransformData(IntContextItem *sourceItem, IntContextItem *destItem)
{
    QReadLocker _readLocker(&sourceItem->Lock);
    QWriteLocker _writeLocker(&destItem->Lock);
    for (int sourceValue : sourceItem->Data)
    {
        destItem->Data.append(sourceValue + 10000);
        destItem->Data.append(sourceValue + 11000);
        destItem->Data.append(sourceValue + 12000);
    }
}

}

TestTotalDataTransformAction::TestTotalDataTransformAction(QString const &name,
                                                           QString const &sourceKey,
                                                           QString const &destKey,
                                                           ContextPtr context,
                                                           ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey)
{
    context.get()->Set(_destKey, IntContextItemPtr(new IntContextItem()));
}

QString TestTotalDataTransformAction::GetName()
{
    return _name;
}

/*void TestTotalDataTransformAction::StartAction(Context &context)
{
}*/

/*void TestTotalDataTransformAction::Run(Context &context)
{
}*/

void TestTotalDataTransformAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _sourceKey)
            ProcessTotalData();
    });
}

void TestTotalDataTransformAction::ProcessStopImpl()
{
    // do nothing
}

void TestTotalDataTransformAction::CleanupNonFinished()
{
    // do nothing
}

void TestTotalDataTransformAction::ProcessTotalData()
{
    ContextPtr context = GetContext();
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    TransformData(sourceItem, destItem);
    emit destItem->NotifyDataChange();
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

}
