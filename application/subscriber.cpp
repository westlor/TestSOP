#include "subscriber.h"
#include <QDebug>
#include <service/event/ctkEventConstants.h>

Subscriber::Subscriber(ctkPluginContext *context)
{
    this->pcontext = context;
}

// 将事件处理程序注册为服务
void Subscriber::registerServece()
{
    ctkDictionary cdiry;
    cdiry.insert(ctkEventConstants::EVENT_TOPIC, "testsop/hotplug");
    pcontext->registerService<ctkEventHandler>(this, cdiry);
}

// 处理事件
void Subscriber::handleEvent(const ctkEvent &event)
{
    QString infostr = event.getProperty("plug_info").toString();

    qDebug() << QString("handleEvent_info: %1").arg(infostr);
}
