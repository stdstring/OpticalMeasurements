#include <QCommandLineParser>
#include <QString>

#include "CommandLineDefs.h"

namespace CalcApp
{

const QString CommandLineDefs::ConfigOptionName = "config";
const QString CommandLineDefs::DefaultConfigFilename = "MainApp.conf";

void CommandLineDefs::CreateDefs(QCommandLineParser *parser)
{
    parser->addHelpOption();
    parser->addOption({ConfigOptionName, "location of config file <filename>", "filename", DefaultConfigFilename});
}

}
