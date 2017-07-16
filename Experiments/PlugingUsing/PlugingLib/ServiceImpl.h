#include <QObject>

#include "IService.h"

#pragma once

#if defined(PLUGING_LIB_LIBRARY)
#define PLUGING_LIB_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define PLUGING_LIB_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace PlugingUsing
{

class PLUGING_LIB_LIBRARY_DLLSPEC ServiceImpl : public IService
{
public:
    explicit ServiceImpl(QObject *parent = nullptr);
    virtual void DoIt() override;
};

}
