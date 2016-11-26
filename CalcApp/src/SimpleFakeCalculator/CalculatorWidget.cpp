#include <QByteArray>
#include <QObject>
#include <QString>
#include <QWidget>

#include "../CommonLib/ITransport.h"
#include "../CommonLib/Message.h"
#include "../CommonLib/MessageType.h"
#include "CalculatorWidget.h"
#include "ui_CalculatorWidget.h"

const char *CalibrationRequest = "CALIBRATION-REQUEST";
const char *RunRequest = "RUN-REQUEST";

CalculatorWidget::CalculatorWidget(CalcApp::ITransport *transport, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorWidget),
    _transport(transport)
{
    QObject::connect(ui->RunButton, &QPushButton::clicked, this, &CalculatorWidget::RunHandler);
    ui->setupUi(this);
}

CalculatorWidget::~CalculatorWidget()
{
    delete ui;
}

void CalculatorWidget::RunHandler()
{
    ui->InfoWidget->clear();
    ui->RunButton->setEnabled(false);
    ui->InfoWidget->addItem(QString::asprintf("Request = %s", CalibrationRequest));
    CalcApp::Message calibrationResponse = _transport->ProcessControlCmd(CalcApp::Message(CalcApp::MessageType::REQUEST, QByteArray(CalibrationRequest)));
    ui->InfoWidget->addItem(QString::asprintf("Response = %s", calibrationResponse.GetData().toStdString().c_str()));
    ui->InfoWidget->addItem(QString::asprintf("Request = %s", RunRequest));
    CalcApp::Message runResponse = _transport->ProcessControlCmd(CalcApp::Message(CalcApp::MessageType::REQUEST, QByteArray(RunRequest)));
    ui->InfoWidget->addItem(QString::asprintf("Response = %s", runResponse.GetData().toStdString().c_str()));
    while (_transport->HasInput())
        ui->InfoWidget->addItem(QString::asprintf("Input = %s", _transport->RetrieveInput().GetData().toStdString().c_str()));
    ui->RunButton->setEnabled(true);
}
