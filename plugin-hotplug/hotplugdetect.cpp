#include "hotplugdetect.h"
#include <QSocketNotifier>
#ifndef WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#endif
#include <QDebug>
#include <QTime>
#include <service/event/ctkEventAdmin.h>

HotplugDetect::HotplugDetect(QObject *)
{
    socket_fd = -1;
    keep_run  = false;
#ifndef WIN32
    const int buffersize = 2048;
    int ret;

    struct sockaddr_nl snl;
    bzero(&snl, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;

    socket_fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (socket_fd == -1)
    {
        perror("socket");
    }
    setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

    ret = bind(socket_fd, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (ret < 0)
    {
        perror("bind");
        close(socket_fd);
    }else{
        qDebug() << "raw sock bind success.";
    }
#endif
}

void HotplugDetect::StartDetect(ctkPluginContext *contex)
{
    this->pcontex  = contex;
    this->keep_run = true;
    this->start();
}

void HotplugDetect::StopDetect()
{
    this->keep_run = false;
}

void HotplugDetect::run()
{
    ctkServiceReference csref = pcontex->getServiceReference<ctkEventAdmin>();
    ctkEventAdmin *eventAdmin;
    if(!csref){
        qDebug() << "无法获取ctkEventAdmin服务，hotplug插件将停止运行!!!";
        keep_run = false;
        return;
    }

#ifndef WIN32
    int recvLen;
    QString recvStr;
    char buf[5000] = {0};
    QString last_type = "", now_type = "";
    QTime   last_time = QTime::currentTime(), now_time;

    while(keep_run){
        recvLen = recv(socket_fd, &buf, sizeof(buf), 0);
        if(recvLen > 0){
            recvStr.sprintf("%s", buf);

            now_type = recvStr.left(10);
            if(now_type == last_type){
                if(now_time.hour() == last_time.hour() &&
                        now_time.minute() == last_time.minute()){
                    // 过滤200ms内的同一类型事件
                    if((now_time.msec()+now_time.second()*1000) - (last_time.msec()+last_time.second()*1000) < 200){
                        continue;
                    }
                }
            }

            last_type = now_type;
            last_time = now_time;

            eventAdmin = pcontex->getService<ctkEventAdmin>(csref);
            ctkDictionary cdiry;
            cdiry.insert("plug_info", QString("[%1]%2").arg(QTime::currentTime().toString("mm:ss.zzz")).arg(recvStr));

            ctkEvent event("testsop/hotplug", cdiry);
            eventAdmin->postEvent(event);
        }
    }
#else
    int counts = 0;
    while (keep_run) {
        msleep(1000);
        counts++;

        if(counts > 10)
            break;

        eventAdmin = pcontex->getService<ctkEventAdmin>(csref);
        ctkDictionary cdiry;
        cdiry.insert("plug_info", QString("windows平台下不支持hotplug detect[%1]").arg(counts));

        ctkEvent event("testsop/hotplug", cdiry);
        eventAdmin->postEvent(event);
    }
#endif

}
