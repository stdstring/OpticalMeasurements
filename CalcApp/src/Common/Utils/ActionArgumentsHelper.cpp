#include <QList>
#include <QMultiMap>
#include <QString>

#include <stdexcept>

#include "ActionArgumentsHelper.h"

namespace CalcApp
{

QString GetStringArgValue(QMultiMap<QString, QString> const &args, QString const &key)
{
    QList<QString> values = args.values(key);
    if (values.size() != 1)
        throw std::invalid_argument(key.toStdString());
    return values[0];
}

int GetIntArgValue(QMultiMap<QString, QString> const &args, QString const &key)
{
    bool ok;
    QList<QString> values = args.values(key);
    if (values.size() != 1)
        throw std::invalid_argument(key.toStdString());
    int value = values[0].toInt(&ok);
    if (!ok)
        throw std::invalid_argument(key.toStdString());
    return value;
}

double GetDoubleArgValue(QMultiMap<QString, QString> const &args, QString const &key)
{
    bool ok;
    QList<QString> values = args.values(key);
    if (values.size() != 1)
        throw std::invalid_argument(key.toStdString());
    double value = values[0].toDouble(&ok);
    if (!ok)
        throw std::invalid_argument(key.toStdString());
    return value;
}

}
