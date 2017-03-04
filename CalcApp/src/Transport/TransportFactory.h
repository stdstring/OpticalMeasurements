#pragma once

#include <QObject>

#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"

namespace CalcApp
{

class TransportFactory : public QObject, public ITransportFactory
{
    Q_OBJECT
public:
    explicit TransportFactory(QObject *parent = 0);

    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) override;
};

}
