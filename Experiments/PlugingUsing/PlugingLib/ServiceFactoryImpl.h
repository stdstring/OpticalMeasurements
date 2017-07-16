#include <QObject>
#include <QtPlugin>

#include "IService.h"
#include "IServiceFactory.h"

#pragma once

#if defined(PLUGING_LIB_LIBRARY)
#define PLUGING_LIB_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define PLUGING_LIB_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace PlugingUsing
{

class PLUGING_LIB_LIBRARY_DLLSPEC ServiceFactoryImpl : public IServiceFactory
{
    Q_OBJECT
    Q_INTERFACES(PlugingUsing::IServiceFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.PlugingUsing.IServiceFactory" FILE "PlugingLib.json")
public:
    explicit ServiceFactoryImpl(QObject *parent = nullptr);
    virtual IService *Create() override;
};

}
