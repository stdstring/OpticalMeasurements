#include <QObject>

#include "Common/IConfigReader.h"
#include "Common/MainConfig.h"

namespace CalcApp
{

class XmlConfigReader : public IConfigReader
{
public:
    explicit XmlConfigReader(QObject *parent = nullptr);
    virtual MainConfig Read(int argc, char *argv[]) override;
};

}
