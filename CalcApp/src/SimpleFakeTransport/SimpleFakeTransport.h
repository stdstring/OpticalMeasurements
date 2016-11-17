#pragma once

#include <QObject>

#include "../CommonLib/ITransport.h"

namespace CalcApp
{

class SimpleFakeTransport : public QObject, public ITransport
{
};

}
