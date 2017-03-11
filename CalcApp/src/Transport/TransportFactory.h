#pragma once

#include <QObject>

#include "Common/IComponentInfo.h"
#include "Common/ITransport.h"
#include "Common/ITransportFactory.h"
#include "Common/TransportConfig.h"

namespace CalcApp
{

class TransportFactory : public QObject, public ITransportFactory, public IComponentInfo
{
    Q_OBJECT
public:
    explicit TransportFactory(QObject *parent = 0);

    virtual ITransport* Create(TransportConfig const &transportConfig, QObject *parent) override;
    virtual ComponentType GetComponentType() override { return ComponentType::TRANSPORT; }
};

}
