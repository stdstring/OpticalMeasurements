#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

struct Vertex3D
{
public:
    Vertex3D(double x, double y, double z);

    double X;
    double Y;
    double Z;
};

class SaveVertexDataAction : public IAction
{
public:
    SaveVertexDataAction(QString const &actionName, QString const &key, QString const &filename, ContextPtr context, ExecutionStatePtr state);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;
    virtual void CleanupNonFinished() override;

private:
    void ProcessData();
    void FinishProcessData();
    void ProcessDataImpl();

private:
    QString _actionName;
    QString _key;
    QString _filename;
    // TODO (std_string) : probably move into separate state object
    int _index;
};

}
