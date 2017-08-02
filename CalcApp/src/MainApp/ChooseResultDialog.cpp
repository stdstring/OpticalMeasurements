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
    connect(_ui->ButtonBox, &QDialogButtonBox::accepted, this, &ChooseResultDialog::accept);
    connect(_ui->ButtonBox, &QDialogButtonBox::rejected, this, &ChooseResultDialog::reject);
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
