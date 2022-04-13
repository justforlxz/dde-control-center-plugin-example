#include <interface/moduleinterface.h>
#include <QObject>
#include <QString>

using namespace DCC_NAMESPACE;

class Module : public QObject, public ModuleInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.plugins.test" FILE "metadata.json")
public:
    Module() = default;
    Module(FrameProxyInterface *frameProxy);
    ~Module() override;
 
    virtual void          preInitialize(bool sync = false, FrameProxyInterface::PushType = FrameProxyInterface::PushType::Normal);
    virtual void          initialize() override;
    virtual const QString name() const override;
    virtual const QString displayName() const override;
    virtual QWidget      *moduleWidget() override;
    virtual void          active() override;
    virtual void          deactive() override;
};
