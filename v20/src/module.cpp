#include "module.h"

using namespace DCC_NAMESPACE;

Module::Module(FrameProxyInterface *frameProxy) : ModuleInterface(frameProxy) {}
Module::~Module() {}

void Module::preInitialize(bool sync, FrameProxyInterface::PushType type)
{
    Q_UNUSED(sync);
    Q_UNUSED(type);
}

void Module::initialize() {}

const QString Module::name() const
{
    return "Module";
}

const QString Module::displayName() const
{
    return tr("Module");
}

QWidget *Module::moduleWidget()
{
    return nullptr;
}

void Module::active() {}

void Module::deactive() {}
