#include <QMultiMap>
#include <QString>

#pragma once

namespace CalcApp
{

QString GetStringArgValue(QMultiMap<QString, QString> const &args, QString const &key);
int GetIntArgValue(QMultiMap<QString, QString> const &args, QString const &key);
double GetDoubleArgValue(QMultiMap<QString, QString> const &args, QString const &key);

}
