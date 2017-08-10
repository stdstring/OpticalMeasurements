#include <QApplication>
#include <QCommandLineParser>
#include <QIODevice>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "MainWindow.h"

QString readAllData(QString const &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    return stream.readAll();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // TODO (std_string) : move definitions into separate place
    const QString headerOptionName = "header";
    const QString dataOptionName = "data";
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption({headerOptionName, "Header", "header"});
    parser.addOption({dataOptionName, "path to data file", "filename"});
    parser.process(app);
    QString header = parser.value(headerOptionName);
    QString dataFilename = parser.value(dataOptionName);
    if (header.isEmpty() || dataFilename.isEmpty())
        return -1;
    if (!QFile::exists(dataFilename))
        return -1;
    CalcApp::MainWindow w(header, readAllData(dataFilename));
    w.show();
    return app.exec();
}
