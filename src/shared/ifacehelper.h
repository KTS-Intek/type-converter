#ifndef IFACEHELPER_H
#define IFACEHELPER_H

#include <QObject>
#include <QStringList>

class IfaceHelper : public QObject
{
    Q_OBJECT
public:
    explicit IfaceHelper(const bool &disableCache, QObject *parent = 0);

    QString convertByteArr2asciiStr(const QByteArray &arr, const bool ommitRightDot = true);



signals:
    void ifaceLogStr(QString line); //<iface name> <time> <hex><data>  line 16 bytes

    void ifaceLogArrLine(QByteArray arrAll);//line 16 bytes

    void ifaceLogArrAll(QByteArray arrAll);

    void ifaceLogPrettyAll(QString strall);//<iface name> <time> <hex><all data >

public slots:
    void showHexDump(QByteArray arr, QString ifaceName, bool isRead);

    void giveMeYourCache();

private:
    QStringList cache;
    bool disableCache;

};

#endif // IFACEHELPER_H
