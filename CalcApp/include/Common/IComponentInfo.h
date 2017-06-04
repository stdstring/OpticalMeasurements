#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

namespace CalcApp
{

enum ComponentCategory { ACTION, TRANSPORT };

class IComponentInfo : public QObject
{
    Q_OBJECT
public:
    explicit IComponentInfo(QObject *parent = nullptr) : QObject(parent) {}

    virtual QString GetType() = 0;
    virtual ComponentCategory GetComponentCategory() = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::IComponentInfo, "com.stdstring.CalcApp.IComponentInfo")
