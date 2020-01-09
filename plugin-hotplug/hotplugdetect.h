#ifndef HOTPLUGDETECT_H
#define HOTPLUGDETECT_H

#include <QObject>
#include <QThread>
#include <ctkPluginContext.h>

#ifndef nullptr
    #define nullptr NULL
#endif

class HotplugDetect : public QThread
{
    Q_OBJECT
public:
    explicit HotplugDetect(QObject *parent = nullptr);
    void StartDetect(ctkPluginContext *contex);
    void StopDetect();

signals:
    void usbPlugDetected(bool isInsert);
    void sataPlugDetected(bool isInsert);

public slots:

protected:
    void run();

private:
    int socket_fd;
    bool keep_run;
    ctkPluginContext* pcontex;
};

#endif // HOTPLUGDETECT_H
