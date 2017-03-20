#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/ActionsConfig.h"
#include "Common/IConfigReader.h"
#include "Common/MainConfig.h"
#include "Common/TransportConfig.h"
#include "DefaultConfigReader.h"

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
    ActionChainDef shortChain("Short command chain", {ActionDef("TestActionA", "ActionA", "3000"),
                                                      ActionDef("TestActionB", "ActionB", "5000")});
    ActionChainDef longChain("Long command chain", {ActionDef("TestActionA", "First ActionA", "2000"),
                                                     ActionDef("TestActionB", "First ActionB", "3000"),
                                                     ActionDef("TestActionA", "Second ActionA", "5000"),
                                                     ActionDef("TestActionB", "Second ActionB", "6000"),
                                                     ActionDef("TestActionA", "Final ActionA", "10000"),
                                                     ActionDef("TestActionB", "Final ActionB", "12000")});
    ActionsConfig actionsConfig({shortChain, longChain});
    QString pluginsCommonDir = ".";
    return MainConfig(pluginsCommonDir, actionsConfig, transportConfig);
}

}
