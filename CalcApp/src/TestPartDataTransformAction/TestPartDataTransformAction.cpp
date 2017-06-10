#include <QReadLocker>
#include <QString>
#include <QWriteLocker>

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

void TransformData(IntContextItem *sourceItem, IntContextItem *destItem, int start)
{
    QReadLocker _readLocker(&sourceItem->Lock);
    QWriteLocker _writeLocker(&destItem->Lock);
    bool transformed = false;
    for (int index = start; index < sourceItem->Data.length(); ++index)
    {
        transformed = true;
        int sourceValue = sourceItem->Data[index];
        destItem->Data.append(sourceValue + 75000);
        destItem->Data.append(sourceValue + 76000);
        destItem->Data.append(sourceValue + 77000);
    }
    if (transformed)
        emit destItem->NotifyDataChange();
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
    ProcessData(GetContext());
}

void TestPartDataTransformAction::FinishProcessData()
{
    ContextPtr context = GetContext();
    ProcessData(context);
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

void TestPartDataTransformAction::ProcessData(ContextPtr context)
{
    IntContextItem *sourceItem = context.get()->GetValue<IntContextItem>(_sourceKey);
    IntContextItem *destItem = context.get()->GetValue<IntContextItem>(_destKey);
    TransformData(sourceItem, destItem, _index + 1);
    _index = sourceItem->Data.length() - 1;
}

}
