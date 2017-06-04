#include <QCoreApplication>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QString>

#include <iostream>
#include <stdexcept>

QString config = "<config>\r\n"
                 "    <common>\r\n"
                 "        <plugins_dir>.</plugins_dir>\r\n"
                 "    </common>\r\n"
                 "    <transport>\r\n"
                 "        <server_address>127.0.0.1</server_address>\r\n"
                 "        <tcp_port>6666</tcp_port>\r\n"
                 "        <udp_port>7777</udp_port>\r\n"
                 "        <max_delayed_count>2</max_delayed_count>\r\n"
                 "    </transport>\r\n"
                 "    <actions>\r\n"
                 "        <chain name=\"Chain1\">\r\n"
                 "            <action name=\"Chain1 Action1\" type=\"SomeTestAction\">\r\n"
                 "                <arg name=\"Data\">SomeValue</arg>\r\n"
                 "                <arg name=\"Data\">SomeOtherValue</arg>\r\n"
                 "                <arg name=\"Info\">SomeInfo</arg>\r\n"
                 "                <arg name=\"OtherData\">IDCLIP</arg>\r\n"
                 "            </action>\r\n"
                 "            <action name=\"Chain1 Action2\" type=\"SomeOtherTestAction\" />\r\n"
                 "            <action name=\"Chain1 Action3\" type=\"SomeAnotherTestAction\" />\r\n"
                 "        </chain>\r\n"
                 "        <chain name=\"Chain2\">\r\n"
                 "            <action name=\"Chain2 Action1\" type=\"OtherTestAction\" />\r\n"
                 "            <action name=\"Chain2 Action2\" type=\"AnotherTestAction\">\r\n"
                 "                <arg name=\"IDDQD\">IDKFA</arg>\r\n"
                 "            </action>\r\n"
                 "        </chain>\r\n"
                 "    </actions>\r\n"
                 "</config>";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDomDocument document;
    if (!document.setContent(config, false))
        throw std::logic_error("bad content");
    QDomElement documentElement = document.documentElement();
    std::cout << "Document element : " << documentElement.nodeName().toStdString() << std::endl;
    QDomElement commonElement = documentElement.firstChildElement("common");
    std::cout << "Common element : " << commonElement.nodeName().toStdString() << std::endl;
    QDomElement transportElement = documentElement.firstChildElement("transport");
    std::cout << "Transport element : " << transportElement.nodeName().toStdString() << std::endl;
    std::cout << "Transport.ServerAddress element = " << transportElement.firstChildElement("server_address").firstChild().nodeValue().toStdString() << std::endl;
    std::cout << "Transport.TcpPort element = " << transportElement.firstChildElement("tcp_port").firstChild().nodeValue().toStdString() << std::endl;
    std::cout << "Transport.UdpPort element = " << transportElement.firstChildElement("udp_port").firstChild().nodeValue().toStdString() << std::endl;
    std::cout << "Transport.MaxDelayedCount element = " << transportElement.firstChildElement("max_delayed_count").firstChild().nodeValue().toStdString() << std::endl;
    QDomElement actionsElement = documentElement.firstChildElement("actions");
    std::cout << "Actions element : " << actionsElement.nodeName().toStdString() << std::endl;
    QDomNodeList chainNodes = actionsElement.childNodes();
    for (int chainIndex = 0; chainIndex < chainNodes.size(); ++chainIndex)
    {
        QDomNode node = chainNodes.at(chainIndex);
        if (node.nodeType() != QDomNode::ElementNode)
            continue;
        std::cout << "Chain element : name = " << node.attributes().namedItem("name").nodeValue().toStdString() << std::endl;
        QDomNodeList actionNodes = node.childNodes();
        for (int actionIndex = 0; actionIndex < actionNodes.size(); ++actionIndex)
        {
            QDomNode node = actionNodes.at(actionIndex);
            if (node.nodeType() != QDomNode::ElementNode)
                continue;
            std::cout << "Action element : name = "
                      << node.attributes().namedItem("name").nodeValue().toStdString()
                      << " type = "
                      << node.attributes().namedItem("type").nodeValue().toStdString()
                      << std::endl;
            QDomNodeList argNodes = node.childNodes();
            for (int argIndex = 0; argIndex < argNodes.size(); ++argIndex)
            {
                QDomNode node = argNodes.at(argIndex);
                if (node.nodeType() != QDomNode::ElementNode)
                    continue;
                std::cout << "Arg element : name = "
                          << node.attributes().namedItem("name").nodeValue().toStdString()
                          << " value = "
                          << node.firstChild().nodeValue().toStdString()
                          << std::endl;
            }
        }
    }
    return a.exec();
}
