#include <QObject>
#include <QString>
#include <QtGlobal>

#include "ActionsConfig.h"
#include "DefaultConfigReader.h"
#include "IConfigReader.h"
#include "MainConfig.h"
#include "TransportConfig.h"

namespace CalcApp
{

namespace
{

const quint16 TcpPortNumber = 6666;
const quint16 UdpPortNumber = 7777;
const QString ServerAddress = "127.0.0.1";
const quint32 MaxDelayedCount = 2;

}

DefaultConfigReader::DefaultConfigReader(QObject *parent) : IConfigReader(parent)
{
}

MainConfig DefaultConfigReader::Read(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    TransportConfig transportConfig(MaxDelayedCount, ServerAddress, TcpPortNumber, UdpPortNumber);
    ActionsConfig actionsConfig({});
    QString pluginsCommonDir = "";
    return MainConfig(pluginsCommonDir, actionsConfig, transportConfig);
}

}
