#include <QObject>
#include <QTextStream>

#include "IService.h"
#include "ServiceImpl.h"

namespace PlugingUsing
{

ServiceImpl::ServiceImpl(QObject *parent) : IService(parent)
{
}

void ServiceImpl::DoIt()
{
    QTextStream(stdout) << "IDDQD" << endl << "IDKFA" << endl << "IDCLIP" << endl;
}

}

