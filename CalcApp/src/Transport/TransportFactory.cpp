#include <QObject>

#include "ITransport.h"
#include "TransportFactory.h"

namespace CalcApp
{

TransportFactory::TransportFactory(QObject *parent) : QObject(parent)
{
}

ITransport* TransportFactory::Create(QObject *parent)
{
}

}
