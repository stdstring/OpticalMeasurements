#pragma once

#include <QCommandLineParser>
#include <QString>

namespace CalcApp
{

class CommandLineDefs
{
public:
    static void CreateDefs(QCommandLineParser *parser);

    static const QString ConfigOptionName;
    static const QString DefaultConfigFilename;

    CommandLineDefs() = delete;
    CommandLineDefs(CommandLineDefs const&) = delete;
    CommandLineDefs(CommandLineDefs&&) = delete;
    CommandLineDefs& operator=(CommandLineDefs const&) = delete;
    CommandLineDefs& operator=(CommandLineDefs&&) = delete;
};

}
