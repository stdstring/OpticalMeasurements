#include <QCommandLineParser>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QList>
#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/ActionsConfig.h"
#include "Common/IConfigReader.h"
#include "Common/MainConfig.h"
#include "Common/TransportConfig.h"
#include "CommandLineDefs.h"
#include "XmlConfigReader.h"

namespace CalcApp
{

namespace
{

QDomElement GetSingleChildElement(QDomNode const &parent, QString const &name)
{
    QDomElement parentElement = parent.toElement();
    if (parentElement.isNull())
        return QDomElement();
    QDomNodeList children = parentElement.elementsByTagName(name);
    if (children.size() != 1)
        return QDomElement();
    return children.at(0).toElement();
}

QString GetElementValue(QDomElement const &element)
{
    return element.firstChild().nodeValue();
}

QString GetAttributeValue(QDomNode const &node, QString const &name)
{
    return node.attributes().namedItem(name).nodeValue();
}

QMultiMap<QString, QString> ParseActionArgs(QDomNode const &actionNode)
{
    QMultiMap<QString, QString> args;
    QDomNodeList argNodes = actionNode.toElement().elementsByTagName("arg");
    for (int index = 0; index < argNodes.size(); ++index)
    {
        QDomNode argNode = argNodes.at(index);
        QString name = GetAttributeValue(argNode, "name");
        QString value = argNode.firstChild().nodeValue();
        args.insert(name, value);
    }
    return args;
}

QList<ActionDef> ParseChainActions(QDomNode const &chainNode)
{
    QList<ActionDef> actions;
    QDomElement actionsElement = GetSingleChildElement(chainNode, "actions");
    QDomNodeList actionNodes = actionsElement.elementsByTagName("action");
    for (int index = 0; index < actionNodes.size(); ++index)
    {
        QDomNode actionNode = actionNodes.at(index);
        QString name = GetAttributeValue(actionNode, "name");
        QString type = GetAttributeValue(actionNode, "type");
        QMultiMap<QString, QString> args(ParseActionArgs(actionNode));
        actions.append(ActionDef(name, type, args));
    }
    return actions;
}

QList<ResultDef> ParseResults(QDomElement const &resultsElement)
{
    QList<ResultDef> results;
    QDomNodeList resultNodes = resultsElement.elementsByTagName("result");
    for (int index = 0; index < resultNodes.size(); ++index)
    {
        QDomNode resultNode = resultNodes.at(index);
        QString data = GetAttributeValue(resultNode, "data");
        QString viewer = GetAttributeValue(resultNode, "viewer");
        QString descriptor = GetAttributeValue(resultNode, "descriptor");
        results.append(ResultDef(data, viewer, descriptor));
    }
    return results;
}

ActionsConfig ParseActionsConfig(QDomElement const &chainsElement)
{
    QList<ActionChainDef> chains;
    QDomNodeList chainNodes = chainsElement.elementsByTagName("chain");
    for (int index = 0; index < chainNodes.size(); ++index)
    {
        QDomNode chainNode = chainNodes.at(index);
        QString name = GetAttributeValue(chainNode, "name");
        QList<ActionDef> actions(ParseChainActions(chainNode));
        QList<ResultDef> results(ParseResults(GetSingleChildElement(chainNode, "results")));
        ActionChainDef chain(name, actions, results);
        chains.append(chain);
    }
    return ActionsConfig(chains);
}

CommonConfig ParseCommonConfig(QDomElement const &commonElement)
{
    QString pluginsDir = GetElementValue(GetSingleChildElement(commonElement, "plugins_dir"));
    return CommonConfig(pluginsDir);
}

TransportConfig ParseTransportConfig(QDomElement const &transportElement)
{
    bool ok;
    QString serverAddress = GetElementValue(GetSingleChildElement(transportElement, "server_address"));
    QString tcpPortValue = GetElementValue(GetSingleChildElement(transportElement, "tcp_port"));
    QString udpPortValue = GetElementValue(GetSingleChildElement(transportElement, "udp_port"));
    QString maxDelayedCountValue = GetElementValue(GetSingleChildElement(transportElement, "max_delayed_count"));
    int tcpPort = tcpPortValue.toInt(&ok);
    if (!ok)
        throw std::invalid_argument("tcp_port");
    int udpPort = udpPortValue.toInt(&ok);
    if (!ok)
        throw std::invalid_argument("udp_port");
    int maxDelayedCount = maxDelayedCountValue.toInt(&ok);
    if (!ok)
        throw std::invalid_argument("max_delayed_count");
    return TransportConfig(maxDelayedCount, serverAddress, tcpPort, udpPort);
}

ViewersConfig ParseViewersConfig(QDomElement const &viewersElement)
{
    QList<ViewerDef> viewers;
    QDomNodeList viewerNodes = viewersElement.elementsByTagName("viewer");
    for (int index = 0; index < viewerNodes.size(); ++index)
    {
        QDomNode viewerNode = viewerNodes.at(index);
        QString name = GetAttributeValue(viewerNode, "name");
        QString filename = GetAttributeValue(viewerNode, "filename");
        QString args = GetAttributeValue(viewerNode, "args");
        viewers.append(ViewerDef(name, filename, args));
    }
    return ViewersConfig(viewers);
}

}

XmlConfigReader::XmlConfigReader(QObject *parent) : IConfigReader(parent)
{
}

MainConfig XmlConfigReader::Read(QCommandLineParser *parser)
{
    QString configFilename(parser->value(CommandLineDefs::ConfigOptionName));
    QFile config(configFilename);
    if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::invalid_argument("missing config");
    QDomDocument document;
    if (!document.setContent(&config, false))
        throw std::logic_error("bad content");
    QDomElement rootElement = document.documentElement();
    CommonConfig commonConfig(ParseCommonConfig(GetSingleChildElement(rootElement, "common")));
    TransportConfig transportConfig(ParseTransportConfig(GetSingleChildElement(rootElement, "transport")));
    ViewersConfig viewersConfig(ParseViewersConfig(GetSingleChildElement(rootElement, "viewers")));
    ActionsConfig actionsConfig(ParseActionsConfig(GetSingleChildElement(rootElement, "chains")));
    return MainConfig(commonConfig, transportConfig, viewersConfig, actionsConfig);
}

}
