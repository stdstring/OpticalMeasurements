#include <QCommandLineParser>
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

MainConfig DefaultConfigReader::Read(QCommandLineParser *parser)
{
    Q_UNUSED(parser);
    TransportConfig transportConfig(MaxDelayedCount, ServerAddress, TcpPortNumber, UdpPortNumber);
    ActionChainDef generatorTotalConsumerChain("Generator - Total consumer chain",
                                               {ActionDef("Generator",
                                                          "TestDataGeneratorAction",
                                                          {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                ActionDef("Consumer",
                                                          "TestTotalDataConsumerAction",
                                                          {{"key", "Generator"}, {"filename", "GeneratorTotalCosumer.dat"}})});
    ActionChainDef generatorPartConsumerChain("Generator - Part consumer chain",
                                              {ActionDef("Generator",
                                                         "TestDataGeneratorAction",
                                                         {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                               ActionDef("Consumer",
                                                         "TestPartDataConsumerAction",
                                                         {{"key", "Generator"}, {"filename", "GeneratorPartCosumer.dat"}})});
    ActionChainDef generatorTotalTransformTotalConsumerChain("Generator - Total transform - Total consumer chain",
                                                             {ActionDef("Generator",
                                                                        "TestDataGeneratorAction",
                                                                        {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                              ActionDef("Transform",
                                                                        "TestTotalDataTransformAction",
                                                                        {{"source_key", "Generator"}, {"dest_key", "Transform"}}),
                                                              ActionDef("Consumer",
                                                                        "TestTotalDataConsumerAction",
                                                                        {{"key", "Transform"}, {"filename", "GeneratorTotalTransformTotalConsumer.dat"}})});
    ActionChainDef generatorTotalTransformPartConsumerChain("Generator - Total transform - Part consumer chain",
                                                            {ActionDef("Generator",
                                                                       "TestDataGeneratorAction",
                                                                       {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                             ActionDef("Transform",
                                                                       "TestTotalDataTransformAction",
                                                                       {{"source_key", "Generator"}, {"dest_key", "Transform"}}),
                                                             ActionDef("Consumer",
                                                                       "TestPartDataConsumerAction",
                                                                       {{"key", "Transform"}, {"filename", "GeneratorTotalTransformPartConsumer.dat"}})});
    ActionChainDef generatorPartTransformTotalConsumerChain("Generator - Part transform - Total consumer chain",
                                                            {ActionDef("Generator",
                                                                       "TestDataGeneratorAction",
                                                                       {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                             ActionDef("Transform",
                                                                       "TestPartDataTransformAction",
                                                                       {{"source_key", "Generator"}, {"dest_key", "Transform"}}),
                                                             ActionDef("Consumer",
                                                                       "TestTotalDataConsumerAction",
                                                                       {{"key", "Transform"}, {"filename", "GeneratorPartTransformTotalConsumer.dat"}})});
    ActionChainDef generatorPartTransformPartConsumerChain("Generator - Part transform - Part consumer chain",
                                                           {ActionDef("Generator",
                                                                      "TestDataGeneratorAction",
                                                                      {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                            ActionDef("Transform",
                                                                      "TestPartDataTransformAction",
                                                                      {{"source_key", "Generator"}, {"dest_key", "Transform"}}),
                                                            ActionDef("Consumer",
                                                                      "TestPartDataConsumerAction",
                                                                      {{"key", "Transform"}, {"filename", "GeneratorPartTransformPartConsumer.dat"}})});
    ActionChainDef generatorTwoConsumersChain("Generator - Two consumers chain",
                                              {ActionDef("Generator",
                                                         "TestDataGeneratorAction",
                                                         {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                               ActionDef("Total consumer",
                                                         "TestTotalDataConsumerAction",
                                                         {{"key", "Generator"}, {"filename", "GeneratorTotalCosumer.dat"}}),
                                               ActionDef("Part consumer",
                                                         "TestPartDataConsumerAction",
                                                         {{"key", "Generator"}, {"filename", "GeneratorPartCosumer.dat"}})});
    ActionChainDef generatorTwoTransformsTotalConsumerChain("Generator - Two transforms - Total consumer chain",
                                                            {ActionDef("Generator",
                                                                       "TestDataGeneratorAction",
                                                                       {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                             ActionDef("Total transform",
                                                                       "TestTotalDataTransformAction",
                                                                       {{"source_key", "Generator"}, {"dest_key", "FirstTransform"}}),
                                                             ActionDef("Part transform",
                                                                       "TestPartDataTransformAction",
                                                                       {{"source_key", "FirstTransform"}, {"dest_key", "SecondTransform"}}),
                                                             ActionDef("Consumer",
                                                                       "TestTotalDataConsumerAction",
                                                                       {{"key", "SecondTransform"}, {"filename", "GeneratorTwoTransformsTotalConsumer.dat"}})});
    ActionChainDef generatorTwoTransformsPartConsumerChain("Generator - Two transforms - Part consumer chain",
                                                           {ActionDef("Generator",
                                                                      "TestDataGeneratorAction",
                                                                      {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                            ActionDef("Total transform",
                                                                      "TestTotalDataTransformAction",
                                                                      {{"source_key", "Generator"}, {"dest_key", "FirstTransform"}}),
                                                            ActionDef("Part transform",
                                                                      "TestPartDataTransformAction",
                                                                      {{"source_key", "FirstTransform"}, {"dest_key", "SecondTransform"}}),
                                                            ActionDef("Consumer",
                                                                      "TestPartDataConsumerAction",
                                                                      {{"key", "SecondTransform"}, {"filename", "GeneratorTwoTransformsPartConsumer.dat"}})});
    ActionChainDef generatorTwoTransformConsumerBranchesChain("Generator - Two transform consumer branches chain",
                                                              {ActionDef("Generator",
                                                                         "TestDataGeneratorAction",
                                                                         {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                                               ActionDef("Total transform",
                                                                         "TestTotalDataTransformAction",
                                                                         {{"source_key", "Generator"}, {"dest_key", "FirstTransform"}}),
                                                               ActionDef("Part transform",
                                                                         "TestPartDataTransformAction",
                                                                         {{"source_key", "Generator"}, {"dest_key", "SecondTransform"}}),
                                                               ActionDef("Total consumer",
                                                                         "TestTotalDataConsumerAction",
                                                                         {{"key", "FirstTransform"}, {"filename", "GeneratorTotalBranchChain.dat"}}),
                                                               ActionDef("Part consumer",
                                                                         "TestPartDataConsumerAction",
                                                                         {{"key", "SecondTransform"}, {"filename", "GeneratorPartBranchChain.dat"}})});
    ActionChainDef complexChain("Complex chain",
                                {ActionDef("Generator1",
                                           "TestDataGeneratorAction",
                                           {{"key", "Generator1"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                 ActionDef("Generator2",
                                           "TestDataGeneratorAction",
                                           {{"key", "Generator2"}, {"sleep_time", "2000"}, {"data_count", "15"}}),
                                 ActionDef("Consumer1",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Generator1"}, {"filename", "Complex_Consumer1.dat"}}),
                                 ActionDef("Consumer2",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Generator1"}, {"filename", "Complex_Consumer2.dat"}}),
                                 ActionDef("Transform1",
                                           "TestTotalDataTransformAction",
                                           {{"source_key", "Generator1"}, {"dest_key", "Transform1"}}),
                                 ActionDef("Transform2",
                                           "TestPartDataTransformAction",
                                           {{"source_key", "Generator1"}, {"dest_key", "Transform2"}}),
                                 ActionDef("Transform3",
                                           "TestTotalDataTransformAction",
                                           {{"source_key", "Transform1"}, {"dest_key", "Transform3"}}),
                                 ActionDef("Transform4",
                                           "TestPartDataTransformAction",
                                           {{"source_key", "Transform1"}, {"dest_key", "Transform4"}}),
                                 ActionDef("Transform5",
                                           "TestTotalDataTransformAction",
                                           {{"source_key", "Transform2"}, {"dest_key", "Transform5"}}),
                                 ActionDef("Transform6",
                                           "TestPartDataTransformAction",
                                           {{"source_key", "Transform2"}, {"dest_key", "Transform6"}}),
                                 ActionDef("Consumer3",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Transform1"}, {"filename", "Complex_Consumer3.dat"}}),
                                 ActionDef("Consumer4",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Transform1"}, {"filename", "Complex_Consumer4.dat"}}),
                                 ActionDef("Consumer5",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Transform2"}, {"filename", "Complex_Consumer5.dat"}}),
                                 ActionDef("Consumer6",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Transform2"}, {"filename", "Complex_Consumer6.dat"}}),
                                 ActionDef("Consumer7",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Transform3"}, {"filename", "Complex_Consumer7.dat"}}),
                                 ActionDef("Consumer8",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Transform3"}, {"filename", "Complex_Consumer8.dat"}}),
                                 ActionDef("Consumer9",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Transform4"}, {"filename", "Complex_Consumer9.dat"}}),
                                 ActionDef("Consumer10",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Transform4"}, {"filename", "Complex_Consumer10.dat"}}),
                                 ActionDef("Consumer11",
                                           "TestTotalDataConsumerAction",
                                           {{"key", "Generator2"}, {"filename", "Complex_Consumer11.dat"}}),
                                 ActionDef("Consumer12",
                                           "TestPartDataConsumerAction",
                                           {{"key", "Generator2"}, {"filename", "Complex_Consumer12.dat"}})});
    ActionChainDef generatorTotalFailedChain("Generator - Total failed - Total consumer chain",
                                             {ActionDef("Generator",
                                                        "TestDataGeneratorAction",
                                                        {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                              ActionDef("FailedAction",
                                                        "TestTotalDataFailedAction",
                                                        {{"source_key", "Generator"}, {"dest_key", "Dest"}, {"failed_iteration", "3"}}),
                                              ActionDef("Consumer",
                                                        "TestTotalDataConsumerAction",
                                                        {{"key", "Dest"}, {"filename", "GeneratorTotalFailed.dat"}})});
    ActionChainDef generatorPartFailedChain("Generator - Part failed - Part consumer chain",
                                            {ActionDef("Generator",
                                                       "TestDataGeneratorAction",
                                                       {{"key", "Generator"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                             ActionDef("FailedAction",
                                                       "TestPartDataFailedAction",
                                                       {{"source_key", "Generator"}, {"dest_key", "Dest"}, {"failed_iteration", "3"}}),
                                             ActionDef("Consumer",
                                                       "TestPartDataConsumerAction",
                                                       {{"key", "Dest"}, {"filename", "GeneratorPartFailed.dat"}})});
    ActionChainDef complexFailedChain("Complex failed chain",
                                      {ActionDef("Generator1",
                                                 "TestDataGeneratorAction",
                                                 {{"key", "Generator1"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                       ActionDef("Generator2",
                                                 "TestDataGeneratorAction",
                                                 {{"key", "Generator2"}, {"sleep_time", "1000"}, {"data_count", "10"}}),
                                       ActionDef("Generator3",
                                                 "TestDataGeneratorAction",
                                                 {{"key", "Generator3"}, {"sleep_time", "2000"}, {"data_count", "20"}}),
                                       ActionDef("FailedAction1",
                                                 "TestTotalDataFailedAction",
                                                 {{"source_key", "Generator1"}, {"dest_key", "Dest1"}, {"failed_iteration", "3"}}),
                                       ActionDef("Consumer1",
                                                 "TestTotalDataConsumerAction",
                                                 {{"key", "Dest1"}, {"filename", "Complex_GeneratorTotalFailed.dat"}}),
                                       ActionDef("FailedAction2",
                                                 "TestPartDataFailedAction",
                                                 {{"source_key", "Generator2"}, {"dest_key", "Dest2"}, {"failed_iteration", "3"}}),
                                       ActionDef("Consumer2",
                                                 "TestPartDataConsumerAction",
                                                 {{"key", "Dest2"}, {"filename", "Complex_GeneratorPartFailed.dat"}}),
                                       ActionDef("Consumer3",
                                                 "TestPartDataConsumerAction",
                                                 {{"key", "Generator3"}, {"filename", "Complex_GeneratorPartCosumer.dat"}})});
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
