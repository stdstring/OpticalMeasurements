#include <QDialog>
#include <QMessageBox>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Logger/ILogger.h"
#include "Common/ActionsConfig.h"
#include "Common/MainConfig.h"
#include "ChooseResultDialog.h"
#include "ResultProcessor.h"

namespace CalcApp
{

namespace
{

void ShowViewer(ResultDef const &result, ViewersConfig const &viewers, LoggerPtr logger)
{
    QList<ViewerDef>::const_iterator iterator = std::find_if(viewers.Viewers.cbegin(),
                                                             viewers.Viewers.cend(),
                                                             [&result](ViewerDef const &viewer){ return viewer.Name == result.ViewerName; });
    if (viewers.Viewers.cend() == iterator)
    {
        logger.get()->WriteError(LoggerCategory("ResultViewer"), QString("Unknown viewer named \"%1\"").arg(result.ViewerName));
        throw std::logic_error("viewer");
    }
    ViewerDef const &viewer = *iterator;
    QProcess::execute(viewer.Args.isEmpty() ?
                      QString("%1 --header=\"%2\" %3").arg(viewer.Filename).arg(result.Descriptor).arg(result.DataFilename) :
                      QString("%1 %2 --header=\"%3\" %4").arg(viewer.Filename).arg(viewer.Args).arg(result.Descriptor).arg(result.DataFilename));
}

}

ResultProcessor::ResultProcessor(MainConfigPtr config, LoggerPtr logger, QObject *parent) :
    QObject(parent),
    _config(config),
    _logger(logger)
{
}

void ResultProcessor::ShowResult(ActionChainDefPtr chain)
{
    // TODO (std_string) : use more functional approach
    // TODO (std_string) : separate on several methods
    if (chain.get()->Results.size() == 0)
    {
        QMessageBox resultInfo;
        resultInfo.setText("This chain doesn't contain any defined results for view.");
        resultInfo.exec();
    }
    else if (chain.get()->Results.size() == 1)
    {
        ShowViewer(chain.get()->Results[0], _config.get()->Viewers, _logger);
    }
    else
    {
        QStringList resultItemsList;
        std::transform(chain.get()->Results.cbegin(),
                       chain.get()->Results.cend(),
                       std::back_inserter(resultItemsList),
                       [](ResultDef const &result){ return result.Descriptor; });
        ChooseResultDialog chooseResultDialog(resultItemsList);
        if (QDialog::Accepted == chooseResultDialog.exec())
        {
            int selectedResultIndex = chooseResultDialog.GetChosenItemIndex();
            ShowViewer(chain.get()->Results.at(selectedResultIndex), _config.get()->Viewers, _logger);
        }
    }
}

}
