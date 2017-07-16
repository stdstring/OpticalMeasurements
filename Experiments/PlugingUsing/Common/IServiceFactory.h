#include <QObject>
#include <QtPlugin>

#include "IService.h"

#pragma once

namespace PlugingUsing
{

class IServiceFactory : public QObject
{
    Q_OBJECT
public:
    explicit IServiceFactory(QObject *parent = nullptr) : QObject(parent) {}
    virtual IService* Create() = 0;
};

}

Q_DECLARE_INTERFACE(PlugingUsing::IServiceFactory, "com.stdstring.PlugingUsing.IServiceFactory")
