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
    /*ActionChainDef shortChain("Short command chain", {ActionDef("TestActionA", "ActionA", "3000"),
                                                      ActionDef("TestActionB", "ActionB", "5000")});
    ActionChainDef longChain("Long command chain", {ActionDef("TestActionA", "First ActionA", "2000"),
                                                     ActionDef("TestActionB", "First ActionB", "3000"),
                                                     ActionDef("TestActionA", "Second ActionA", "5000"),
                                                     ActionDef("TestActionB", "Second ActionB", "6000"),
                                                     ActionDef("TestActionA", "Final ActionA", "10000"),
                                                     ActionDef("TestActionB", "Final ActionB", "12000")});
    ActionChainDef failedChain("Failed chain", {ActionDef("TestActionA", "ActionA", "3000"),
                                                ActionDef("TestFailedAction", "FailedAction", "4000"),
                                                ActionDef("TestActionB", "ActionB", "5000")});
    ActionChainDef stage1DemoChain("Chain1 demo", {ActionDef("TestInteractionAction", "Server interaction action", "data"),
                                                   ActionDef("TestSaveDataAction", "Save data action", "data dest.data")});
    ActionsConfig actionsConfig({shortChain, longChain, failedChain, stage1DemoChain});*/
    ActionChainDef generatorTotalConsumerChain("Generator - Total consumer chain",
                                               {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                ActionDef("TestTotalDataConsumerAction", "Consumer", "Generator GeneratorTotalCosumer.dat")});
    ActionChainDef generatorPartConsumerChain("Generator - Part consumer chain",
                                              {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                               ActionDef("TestPartDataConsumerAction", "Consumer", "Generator GeneratorPartCosumer.dat")});
    ActionChainDef generatorTotalTransformTotalConsumerChain("Generator - TotalTransform - Total consumer chain",
                                                             {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                              ActionDef("TestTotalDataTransformAction", "Transform", "Generator Transform"),
                                                              ActionDef("TestTotalDataConsumerAction", "Consumer", "Transform GeneratorTotalTransformTotalConsumer.dat")});
    ActionChainDef generatorTotalTransformPartConsumerChain("Generator - TotalTransform - Part consumer chain",
                                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                             ActionDef("TestTotalDataTransformAction", "Transform", "Generator Transform"),
                                                             ActionDef("TestPartDataConsumerAction", "Consumer", "Transform GeneratorTotalTransformPartConsumer.dat")});
    ActionChainDef generatorPartTransformTotalConsumerChain("Generator - PartTransform - Total consumer chain",
                                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                             ActionDef("TestPartDataTransformAction", "Transform", "Generator Transform"),
                                                             ActionDef("TestTotalDataConsumerAction", "Consumer", "Transform GeneratorPartTransformTotalConsumer.dat")});
    ActionChainDef generatorPartTransformPartConsumerChain("Generator - PartTransform - Part consumer chain",
                                                           {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                            ActionDef("TestPartDataTransformAction", "Transform", "Generator Transform"),
                                                            ActionDef("TestPartDataConsumerAction", "Consumer", "Transform GeneratorPartTransformPartConsumer.dat")});
    ActionsConfig actionsConfig({generatorTotalConsumerChain,
                                 generatorPartConsumerChain,
                                 generatorTotalTransformTotalConsumerChain,
                                 generatorTotalTransformPartConsumerChain,
                                 generatorPartTransformTotalConsumerChain,
                                 generatorPartTransformPartConsumerChain});
    QString pluginsCommonDir = ".";
    return MainConfig(pluginsCommonDir, actionsConfig, transportConfig);
}

}
