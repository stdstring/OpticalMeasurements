#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

namespace CalcApp
{

enum ComponentType { ACTION, TRANSPORT };

class IComponentInfo : public QObject
{
    Q_OBJECT
public:
    explicit IComponentInfo(QObject *parent = nullptr) : QObject(parent) {}

    virtual QString GetId() = 0;
    virtual ComponentType GetComponentType() = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::IComponentInfo, "com.stdstring.CalcApp.IComponentInfo")
