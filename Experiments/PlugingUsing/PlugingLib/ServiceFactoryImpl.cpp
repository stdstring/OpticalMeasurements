#include <QObject>

#include "IService.h"
#include "IServiceFactory.h"
#include "ServiceImpl.h"
#include "ServiceFactoryImpl.h"

namespace PlugingUsing
{

ServiceFactoryImpl::ServiceFactoryImpl(QObject *parent) : IServiceFactory(parent)
{
}

IService* ServiceFactoryImpl::Create()
{
    return new ServiceImpl(this);
}

}

