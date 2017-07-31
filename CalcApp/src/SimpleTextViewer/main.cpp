#include <QApplication>
#include <QIODevice>
#include <QFile>
#include <QString>
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
    // TODO (std_string) : think about more smart approach
    if (argc < 2)
        return -1;
    // last arg is filename of data (must be nonnamed parameter)
    QString dataFilename(argv[argc - 1]);
    if (!QFile::exists(dataFilename))
        return -1;
    QApplication app(argc, argv);
    CalcApp::MainWindow w(readAllData(dataFilename));
    w.show();
    return app.exec();
}
