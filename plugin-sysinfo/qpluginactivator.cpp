#include "qpluginactivator.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSysInfo>

QPluginActivator::QPluginActivator()
{

}

void QPluginActivator::start(ctkPluginContext *)
{
    qDebug() << QString("I'm sysinfo plugin, now start.");
    qDebug() << "build CPU arch     : " << QSysInfo::buildCpuArchitecture();
    qDebug() << "current CPU arch   : " << QSysInfo::currentCpuArchitecture();
    qDebug() << "kernel type        : " << QSysInfo::kernelType();
    qDebug() << "kernel version     : " << QSysInfo::kernelVersion();
    qDebug() << "machineHostName    : " << QSysInfo::machineHostName();
    qDebug() << "prettyProductName  : " << QSysInfo::prettyProductName();
    qDebug() << "productType        : " << QSysInfo::productType();
}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("I'm sysinfo plugin, now stop.");
}
