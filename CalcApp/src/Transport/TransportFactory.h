#pragma once

#include <QObject>

#include "ITransport.h"
#include "ITransportFactory.h"

namespace CalcApp
{

class TransportFactory : public QObject, public ITransportFactory
{
    Q_OBJECT
public:
    explicit TransportFactory(QObject *parent = 0);

    virtual ITransport* Create(QObject *parent) override;
};

}
