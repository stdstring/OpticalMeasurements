#pragma once

#include <QObject>

#include "ITransport.h"

namespace CalcApp
{

class Transport : public QObject, public ITransport
{
    Q_OBJECT
public:
    explicit Transport(QObject *parent = 0);
};

}

