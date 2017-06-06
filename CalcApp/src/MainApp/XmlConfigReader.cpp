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
#include "XmlConfigReader.h"

namespace CalcApp
{

namespace
{

QMultiMap<QString, QString> ParseActionArgs(QDomNode actionNode)
{
    QMultiMap<QString, QString> args;
    QDomNodeList childNodes = actionNode.childNodes();
    for (int index = 0; index < childNodes.size(); ++index)
    {
        QDomNode node = childNodes.at(index);
        if (node.nodeType() != QDomNode::ElementNode)
            continue;
        if (node.nodeName() != "arg")
            continue;
        QString name = node.attributes().namedItem("name").nodeValue();
        QString value = node.firstChild().nodeValue();
        args.insert(name, value);
    }
    return args;
}

QList<ActionDef> ParseChainActions(QDomNode chainNode)
{
    QList<ActionDef> actions;
    QDomNodeList childNodes = chainNode.childNodes();
    for (int index = 0; index < childNodes.size(); ++index)
    {
        QDomNode node = childNodes.at(index);
        if (node.nodeType() != QDomNode::ElementNode)
            continue;
        if (node.nodeName() != "action")
            continue;
        QString name = node.attributes().namedItem("name").nodeValue();
        QString type = node.attributes().namedItem("type").nodeValue();
        QMultiMap<QString, QString> args(ParseActionArgs(node));
        actions.append(ActionDef(name, type, args));
    }
    return actions;
}

ActionsConfig ParseActionsConfig(QDomElement const &actionsElement)
{
    QList<ActionChainDef> chains;
    QDomNodeList childNodes = actionsElement.childNodes();
    for (int index = 0; index < childNodes.size(); ++index)
    {
        QDomNode node = childNodes.at(index);
        if (node.nodeType() != QDomNode::ElementNode)
            continue;
        if (node.nodeName() != "chain")
            continue;
        QString name = node.attributes().namedItem("name").nodeValue();
        QList<ActionDef> actions(ParseChainActions(node));
        ActionChainDef chain(name, actions);
        chains.append(chain);
    }
    return ActionsConfig(chains);
}


CommonConfig ParseCommonConfig(QDomElement const &commonElement)
{
    QString pluginsDir = commonElement.firstChildElement("plugins_dir").firstChild().nodeValue();
    return CommonConfig(pluginsDir);
}

TransportConfig ParseTransportConfig(QDomElement const &transportElement)
{
    bool ok;
    QString serverAddress = transportElement.firstChildElement("server_address").firstChild().nodeValue();
    QString tcpPortValue = transportElement.firstChildElement("tcp_port").firstChild().nodeValue();
    QString udpPortValue = transportElement.firstChildElement("udp_port").firstChild().nodeValue();
    QString maxDelayedCountValue = transportElement.firstChildElement("max_delayed_count").firstChild().nodeValue();
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

}

XmlConfigReader::XmlConfigReader(QObject *parent) : IConfigReader(parent)
{
}

MainConfig XmlConfigReader::Read(/*int argc, char *argv[]*/QCommandLineParser *parser)
{
    // TODO (std_string) : think about location
    QString configFilename(parser->value("config"));
    QFile config(configFilename);
    if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::invalid_argument("missing config");
    QDomDocument document;
    if (!document.setContent(&config, false))
        throw std::logic_error("bad content");
    QDomElement rootElement = document.documentElement();
    CommonConfig commonConfig(ParseCommonConfig(rootElement.firstChildElement("common")));
    TransportConfig transportConfig(ParseTransportConfig(rootElement.firstChildElement("transport")));
    ActionsConfig actionsConfig(ParseActionsConfig(rootElement.firstChildElement("actions")));
    return MainConfig(commonConfig.PluginsCommonDir, actionsConfig, transportConfig);
}

}
