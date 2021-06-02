#ifndef FLIPPERZERO_H
#define FLIPPERZERO_H

#include <QObject>

#include "usbdeviceparams.h"

class QIODevice;

namespace Flipper {

class Zero : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString model READ model CONSTANT)
    Q_PROPERTY(QString target READ target NOTIFY targetChanged)
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
    Q_PROPERTY(double progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(bool isDFU READ isDFU NOTIFY isDFUChanged)

public:
    Zero(const USBDeviceParams &parameters, QObject *parent = nullptr);

    bool detach();
    bool download(QIODevice *file);

    const QString &name() const;
    const QString &model() const;
    const QString &target() const;
    const QString &version() const;
    const QString &statusMessage() const;
    double progress() const;

    bool isDFU() const;

    void setName(const QString &name);
    void setTarget(const QString &target);
    void setVersion(const QString &version);
    void setStatusMessage(const QString &message);
    void setProgress(double progress);

    void *uniqueID() const;

signals:
    void nameChanged(const QString&);
    void targetChanged(const QString&);
    void versionChanged(const QString&);
    void statusMessageChanged(const QString&);
    void progressChanged(double);

    void isDFUChanged(bool);

private:
    void fetchInfoNormalMode();
    void fetchInfoDFUMode();

    // TODO: move this into USBDevice
    // And create a member instance of DFuseDevice
    USBDeviceParams m_parameters;

    QString m_name;
    QString m_target;
    QString m_version;
    QString m_statusMessage;

    double m_progress;
};

}

#endif // FLIPPERZERO_H
