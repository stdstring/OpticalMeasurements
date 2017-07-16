#include <QCoreApplication>

#include "IService.h"
#include "IServiceFactory.h"
#include "ServiceFactoryImpl.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    PlugingUsing::IServiceFactory *factory = new PlugingUsing::ServiceFactoryImpl(&app);
    PlugingUsing::IService *service = factory->Create();
    service->DoIt();
    return app.exec();
}
