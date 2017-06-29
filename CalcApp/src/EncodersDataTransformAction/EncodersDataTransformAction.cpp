#include <QObject>
#include <QReadLocker>
#include <QString>
#include <QWriteLocker>

#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Data/EncodersData.h"
#include "Common/Data/Vertex3D.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "EncodersDataTransformAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<EncodersData> EncodersDataContextItem;
typedef QListContextItem<Vertex3D> Vertex3DContextItem;

void TransformData(EncodersDataContextItem *sourceItem, Vertex3DContextItem *destItem, int start)
{
    QReadLocker _readLocker(&sourceItem->Lock);
    QWriteLocker _writeLocker(&destItem->Lock);
    bool transformed = false;
    for (int index = start; index < sourceItem->Data.length(); ++index)
    {
        transformed = true;
        EncodersData sourceValue = sourceItem->Data[index];
        Q_UNUSED(sourceValue);
        // TODO (std_string) : add transformation from EncodersData into Vertex3D
        destItem->Data.append(Vertex3D(0, 0, 0));
    }
    if (transformed)
        emit destItem->NotifyDataChange();
}

}

EncodersDataTransformAction::EncodersDataTransformAction(QString const &name,
                                                         QString const &sourceKey,
                                                         QString const &destKey,
                                                         ContextPtr context,
                                                         ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey)
{
    context.get()->Set(_destKey, std::make_shared<Vertex3DContextItem>(new Vertex3DContextItem()));
}

QString EncodersDataTransformAction::GetName()
{
    return _name;
}

/*void EncodersDataTransformAction::StartAction(Context &context)
{
}*/

/*void EncodersDataTransformAction::Run(Context &context)
{
}*/

void EncodersDataTransformAction::ProcessStartImpl()
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

void EncodersDataTransformAction::ProcessStopImpl()
{
    // do nothing
}

void EncodersDataTransformAction::CleanupNonFinished()
{
    // do nothing
}

void EncodersDataTransformAction::ProcessData()
{
    ProcessData(GetContext());
}

void EncodersDataTransformAction::FinishProcessData()
{
    ContextPtr context = GetContext();
    ProcessData(context);
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

void EncodersDataTransformAction::ProcessData(ContextPtr context)
{
    EncodersDataContextItem *sourceItem = context.get()->GetValue<EncodersDataContextItem>(_sourceKey);
    Vertex3DContextItem *destItem = context.get()->GetValue<Vertex3DContextItem>(_destKey);
    TransformData(sourceItem, destItem, _index + 1);
    _index = sourceItem->Data.length() - 1;
}

}
