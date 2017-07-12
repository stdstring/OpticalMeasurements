#include <QFile>
#include <QIODevice>
#include <QLocale>
#include <QObject>
#include <QReadLocker>
#include <QString>
#include <QTextStream>

#include "Common/CommonDefs.h"
#include "Common/Data/Vertex3D.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "SaveVertexDataAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<Vertex3D> Vertex3DContextItem;

// TODO (std_string) : think about location and value of this const
constexpr int RealNumberPrecision = 8;

void SaveData(QTextStream &stream, Vertex3DContextItem *item, int start)
{
    QReadLocker locker(&item->Lock);
    for (int index = start; index < item->Data.length(); ++index)
    {
        Vertex3D value  = item->Data[index];
        stream << "# vertex " << index + 1 << endl;
        stream << value.X << " " << value.Y << " " << value.Z << endl;
    }
}

void SaveData(QString const &filename, Vertex3DContextItem *item, int start)
{
    QFile file(filename);
    file.open(start == 0 ? QIODevice::WriteOnly : QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    // we using C locale
    stream.setLocale(QLocale::c());
    // set real number params
    stream.setRealNumberNotation(QTextStream::RealNumberNotation::FixedNotation);
    stream.setRealNumberPrecision(RealNumberPrecision);
    if (start == 0)
        stream << "# vertex 3D data" << endl;
    SaveData(stream, item, start);
}

}

SaveVertexDataAction::SaveVertexDataAction(QString const &actionName, QString const &key, QString const &filename, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _actionName(actionName),
    _key(key),
    _filename(filename)
{
}

QString SaveVertexDataAction::GetName()
{
    return _actionName;
}

/*void SaveVertexDataAction::StartAction(Context &context)
{
}*/

/*void SaveVertexDataAction::Run(Context &context)
{
}*/

void SaveVertexDataAction::ProcessStartImpl()
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

void SaveVertexDataAction::ProcessStopImpl()
{
}

void SaveVertexDataAction::CleanupNonFinished()
{
    QFile::remove(_filename);
}

void SaveVertexDataAction::ProcessData()
{
    ProcessDataImpl();
}

void SaveVertexDataAction::FinishProcessData()
{
    ProcessDataImpl();
    emit ActionFinished();
}

void SaveVertexDataAction::ProcessDataImpl()
{
    ContextPtr context = GetContext();
    Vertex3DContextItem *item = context.get()->GetValue<Vertex3DContextItem>(_key);
    SaveData(_filename, item, _index + 1);
    _index = item->Data.length() - 1;
}

}
