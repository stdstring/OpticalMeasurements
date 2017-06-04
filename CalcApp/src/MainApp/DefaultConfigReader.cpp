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
    ActionChainDef generatorTotalTransformTotalConsumerChain("Generator - Total transform - Total consumer chain",
                                                             {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                              ActionDef("TestTotalDataTransformAction", "Transform", "Generator Transform"),
                                                              ActionDef("TestTotalDataConsumerAction", "Consumer", "Transform GeneratorTotalTransformTotalConsumer.dat")});
    ActionChainDef generatorTotalTransformPartConsumerChain("Generator - Total transform - Part consumer chain",
                                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                             ActionDef("TestTotalDataTransformAction", "Transform", "Generator Transform"),
                                                             ActionDef("TestPartDataConsumerAction", "Consumer", "Transform GeneratorTotalTransformPartConsumer.dat")});
    ActionChainDef generatorPartTransformTotalConsumerChain("Generator - Part transform - Total consumer chain",
                                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                             ActionDef("TestPartDataTransformAction", "Transform", "Generator Transform"),
                                                             ActionDef("TestTotalDataConsumerAction", "Consumer", "Transform GeneratorPartTransformTotalConsumer.dat")});
    ActionChainDef generatorPartTransformPartConsumerChain("Generator - Part transform - Part consumer chain",
                                                           {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                            ActionDef("TestPartDataTransformAction", "Transform", "Generator Transform"),
                                                            ActionDef("TestPartDataConsumerAction", "Consumer", "Transform GeneratorPartTransformPartConsumer.dat")});
    ActionChainDef generatorTwoConsumersChain("Generator - Two consumers chain",
                                              {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                               ActionDef("TestTotalDataConsumerAction", "Total consumer", "Generator GeneratorTotalCosumer.dat"),
                                               ActionDef("TestPartDataConsumerAction", "Part consumer", "Generator GeneratorPartCosumer.dat")});
    ActionChainDef generatorTwoTransformsTotalConsumerChain("Generator - Two transforms - Total consumer chain",
                                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                             ActionDef("TestTotalDataTransformAction", "Total transform", "Generator FirstTransform"),
                                                             ActionDef("TestPartDataTransformAction", "Part transform", "FirstTransform SecondTransform"),
                                                             ActionDef("TestTotalDataConsumerAction", "Consumer", "SecondTransform GeneratorTwoTransformsTotalConsumer.dat")});
    ActionChainDef generatorTwoTransformsPartConsumerChain("Generator - Two transforms - Part consumer chain",
                                                           {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                            ActionDef("TestTotalDataTransformAction", "Total transform", "Generator FirstTransform"),
                                                            ActionDef("TestPartDataTransformAction", "Part transform", "FirstTransform SecondTransform"),
                                                            ActionDef("TestPartDataConsumerAction", "Consumer", "SecondTransform GeneratorTwoTransformsPartConsumer.dat")});
    ActionChainDef generatorTwoTransformConsumerBranchesChain("Generator - Two transform consumer branches chain",
                                                              {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                                               ActionDef("TestTotalDataTransformAction", "Total transform", "Generator FirstTransform"),
                                                               ActionDef("TestPartDataTransformAction", "Part transform", "Generator SecondTransform"),
                                                               ActionDef("TestTotalDataConsumerAction", "Total consumer", "FirstTransform GeneratorTotalBranchChain.dat"),
                                                               ActionDef("TestPartDataConsumerAction", "Part consumer", "SecondTransform GeneratorPartBranchChain.dat")});
    ActionChainDef complexChain("Complex chain",
                                {ActionDef("TestDataGeneratorAction", "Generator1", "Generator1 1000 10"),
                                 ActionDef("TestDataGeneratorAction", "Generator2", "Generator2 2000 15"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer1", "Generator1 Complex_Consumer1.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer2", "Generator1 Complex_Consumer2.dat"),
                                 ActionDef("TestTotalDataTransformAction", "Transform1", "Generator1 Transform1"),
                                 ActionDef("TestPartDataTransformAction", "Transform2", "Generator1 Transform2"),
                                 ActionDef("TestTotalDataTransformAction", "Transform3", "Transform1 Transform3"),
                                 ActionDef("TestPartDataTransformAction", "Transform4", "Transform1 Transform4"),
                                 ActionDef("TestTotalDataTransformAction", "Transform5", "Transform2 Transform5"),
                                 ActionDef("TestPartDataTransformAction", "Transform6", "Transform2 Transform6"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer3", "Transform1 Complex_Consumer3.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer4", "Transform1 Complex_Consumer4.dat"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer5", "Transform2 Complex_Consumer5.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer6", "Transform2 Complex_Consumer6.dat"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer7", "Transform3 Complex_Consumer7.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer8", "Transform3 Complex_Consumer8.dat"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer9", "Transform4 Complex_Consumer9.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer10", "Transform4 Complex_Consumer10.dat"),
                                 ActionDef("TestTotalDataConsumerAction", "Consumer11", "Generator2 Complex_Consumer11.dat"),
                                 ActionDef("TestPartDataConsumerAction", "Consumer12", "Generator2 Complex_Consumer12.dat")});
    ActionChainDef generatorTotalFailedChain("Generator - Total failed - Total consumer chain",
                                             {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                              ActionDef("TestTotalDataFailedAction", "FailedAction", "Generator Dest 3"),
                                              ActionDef("TestTotalDataConsumerAction", "Consumer", "Dest GeneratorTotalFailed.dat")});
    ActionChainDef generatorPartFailedChain("Generator - Part failed - Part consumer chain",
                                            {ActionDef("TestDataGeneratorAction", "Generator", "Generator 1000 10"),
                                             ActionDef("TestPartDataFailedAction", "FailedAction", "Generator Dest 3"),
                                             ActionDef("TestPartDataConsumerAction", "Consumer", "Dest GeneratorPartFailed.dat")});
    ActionChainDef complexFailedChain("Complex failed chain",
                                      {ActionDef("TestDataGeneratorAction", "Generator1", "Generator1 1000 10"),
                                       ActionDef("TestDataGeneratorAction", "Generator2", "Generator2 1000 10"),
                                       ActionDef("TestDataGeneratorAction", "Generator3", "Generator3 2000 20"),
                                       ActionDef("TestTotalDataFailedAction", "FailedAction1", "Generator1 Dest1 3"),
                                       ActionDef("TestTotalDataConsumerAction", "Consumer1", "Dest1 Complex_GeneratorTotalFailed.dat"),
                                       ActionDef("TestPartDataFailedAction", "FailedAction2", "Generator2 Dest2 3"),
                                       ActionDef("TestPartDataConsumerAction", "Consumer2", "Dest2 Complex_GeneratorPartFailed.dat"),
                                       ActionDef("TestPartDataConsumerAction", "Consumer3", "Generator3 Complex_GeneratorPartCosumer.dat")});
    ActionsConfig actionsConfig({generatorTotalConsumerChain,
                                 generatorPartConsumerChain,
                                 generatorTotalTransformTotalConsumerChain,
                                 generatorTotalTransformPartConsumerChain,
                                 generatorPartTransformTotalConsumerChain,
                                 generatorPartTransformPartConsumerChain,
                                 generatorTwoConsumersChain,
                                 generatorTwoTransformsTotalConsumerChain,
                                 generatorTwoTransformsPartConsumerChain,
                                 generatorTwoTransformConsumerBranchesChain,
                                 complexChain,
                                 generatorTotalFailedChain,
                                 generatorPartFailedChain,
                                 complexFailedChain});
    QString pluginsCommonDir = ".";
    return MainConfig(pluginsCommonDir, actionsConfig, transportConfig);
}

}
