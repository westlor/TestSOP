#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <service/event/ctkEventHandler.h>
#include <ctkPluginContext.h>

class Subscriber : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)
public:
    Subscriber(ctkPluginContext *context);
    // 将事件处理程序注册为服务
    void registerServece();
    // 处理事件
    void handleEvent(const ctkEvent& event) Q_DECL_OVERRIDE;

private:
    ctkPluginContext* pcontext;
};

#endif // SUBSCRIBER_H
