#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestSaveDataAction.h"

namespace CalcApp
{

TestSaveDataAction::TestSaveDataAction(QString const &actionName, const QString &contextKey, const QString &destFilename, QObject *parent) :
    IAction(parent),
    _actionName(actionName),
    _contextKey(contextKey),
    _destFilename(destFilename)
{
}

QString TestSaveDataAction::GetName()
{
    return _actionName;
}

void TestSaveDataAction::Run(Context &context)
{
    Q_UNUSED(context);
    QFile destFile(_destFilename);
    destFile.open(QIODevice::WriteOnly);
    QTextStream stream(&destFile);
    QStringList data; // read from context by key
    foreach (QString item, data)
    {
        stream << item;
    }
}

}

