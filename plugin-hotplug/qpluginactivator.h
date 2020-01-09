#ifndef QPLUGINACTIVATOR_H
#define QPLUGINACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"

class HotplugDetect;
class QPluginActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "appinfo")
    Q_INTERFACES(ctkPluginActivator)
public:
    QPluginActivator();
    void start(ctkPluginContext *context);
    void stop(ctkPluginContext *context);

private:
    ctkPluginContext *pcontex;
    HotplugDetect *hotplugDetect;
};

#endif // QPLUGINACTIVATOR_H
