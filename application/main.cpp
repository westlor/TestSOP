#include <QCoreApplication>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include <ctkPluginFrameworkLauncher.h>
#include <QtDebug>
#include <QUrl>
#include "subscriber.h"

QString getPluginFilePath(QString plugin_name){
#ifdef WIN32
    #ifdef QT_NO_DEBUG
        return QString("../plugin-%1/release/plugin-%1.dll").arg(plugin_name);
    #else
        return QString("../plugin-%1/debug/plugin-%1.dll").arg(plugin_name);
    #endif
#else
    #ifdef __linux__
        return QString("../plugin-%1/libplugin-%1.so").arg(plugin_name);
    #endif
#endif
}

#define MACRO2STR(R)  #R
#define STR_MACRO(R)  MACRO2STR(R)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 初始化并启动插件框架
    try {
        QString ctkPluginLibsPath = QString(STR_MACRO(CTK_PLUGIN_LIBS));
        qDebug() << QString("add search path: %1").arg(ctkPluginLibsPath);
        ctkPluginFrameworkLauncher::addSearchPath(ctkPluginLibsPath, false);       // 添加services插件目录
        ctkPluginFrameworkLauncher::start("org.commontk.eventadmin");              // 启动插件框架，使能eventadmin service
        qDebug() << "CTK plugin framework start...";
    } catch (const ctkPluginException &e) {
        qDebug() << "CTK plugin framework init err: " << e.what();
        return -1;
    }

    // 获取插件服务的contex
    ctkPluginContext* pluginContext = ctkPluginFrameworkLauncher::getPluginContext();

    // 注册服务，用于接收事件通知
    Subscriber subr(pluginContext);
    subr.registerServece();

    // 加载并启动所需插件
    QStringList pluginLists = {"hotplug", "sysinfo"};
    foreach (QString pluginName, pluginLists) {
        try {
            // 安装插件
            QSharedPointer<ctkPlugin> plugin = pluginContext->installPlugin(QUrl::fromLocalFile(getPluginFilePath(pluginName)));
            qDebug() << QString("Plugin[%1_%2] installed...").arg(plugin->getSymbolicName()).arg(plugin->getVersion().toString());
            // 启动插件
            plugin->start(ctkPlugin::START_TRANSIENT);
        } catch (const ctkPluginException &e) {
            qDebug() << QString("Failed install or run plugin[%1]: ").arg(getPluginFilePath(pluginName)) << e.what();
            return -2;
        }
    }

    return a.exec();
}
