//#include <QDateTime>
#include <QFile>
//#include <QIODevice>
#include <QObject>
//#include <QReadLocker>
//#include <QString>
//#include <QTextStream>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "SaveVertexDataAction.h"

namespace CalcApp
{

namespace
{

/*void SaveData(QTextStream &stream, QStringListContextItem *item, int start)
{
    QReadLocker locker(&item->Lock);
    for (int index = start; index < item->Data.length(); ++index)
    {
        QString value  = item->Data[index];
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : " << value << endl;
    }
}

void SaveData(QString const &filename, QStringListContextItem *item, int start, bool lastSave)
{
    QFile file(filename);
    file.open(start == 0 ? QIODevice::WriteOnly : QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    if (start == 0)
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : start" << endl;
    SaveData(stream, item, start);
    if (lastSave)
        stream << QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss:zzz") << " : finish" << endl;
}*/

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
    ProcessData(false);
}

void SaveVertexDataAction::FinishProcessData()
{
    ProcessData(true);
    emit ActionFinished();
}

void SaveVertexDataAction::ProcessData(bool last)
{
    /*ContextPtr context = GetContext();
    QStringListContextItem *item = context.get()->GetValue<QStringListContextItem>(_key);
    SaveData(_filename, item, _index + 1, last);
    _index = item->Data.length() - 1;*/
}

}
