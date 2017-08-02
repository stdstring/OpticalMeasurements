#include <QDialog>
#include <QList>
#include <QStringList>

#include "ChooseResultDialog.h"
#include "ui_ChooseResultDialog.h"

namespace CalcApp
{

ChooseResultDialog::ChooseResultDialog(QStringList const &items, QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ChooseResultDialog)
{
    _ui->setupUi(this);
    _ui->ResultsListWidget->addItems(items);
}

int ChooseResultDialog::GetChosenItemIndex() const
{
    return _ui->ResultsListWidget->currentRow();
}

ChooseResultDialog::~ChooseResultDialog()
{
    delete _ui;
}

}
