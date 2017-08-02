#pragma once

#include <QDialog>
#include <QStringList>
#include <QWidget>

namespace Ui
{
class ChooseResultDialog;
}

namespace CalcApp
{

class ChooseResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseResultDialog(QStringList const &items, QWidget *parent = 0);
    int GetChosenItemIndex() const;
    ~ChooseResultDialog();

private:
    Ui::ChooseResultDialog *_ui;
};

}
