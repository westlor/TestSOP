#include "qpluginactivator.h"
#include <QDebug>
#include <service/event/ctkEventAdmin.h>
#include "hotplugdetect.h"

QPluginActivator::QPluginActivator()
{

}

void QPluginActivator::start(ctkPluginContext *contex)
{
    qDebug() << QString("I'm hotplug plugin, now start.");
    this->pcontex = contex;

    hotplugDetect = new HotplugDetect;
    hotplugDetect->StartDetect(contex);
}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("I'm hotplug plugin, now stop.");
    hotplugDetect->StopDetect();
}
