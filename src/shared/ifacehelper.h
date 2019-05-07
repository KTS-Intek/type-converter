#ifndef IFACEHELPER_H
#define IFACEHELPER_H

#include <QObject>
#include <QStringList>

class IfaceHelper : public QObject
{
    Q_OBJECT
public:
    explicit IfaceHelper(const bool &disableCache, QObject *parent = 0);

    static QString convertByteArr2asciiStr(const QByteArray &arr, const bool ommitRightDot = true);


    struct IffaceLogOut
    {
        QList<QByteArray> ifaceLogArrLine;
        QStringList ifaceLogStr;
        QByteArray ifaceLogArrAll;
        QString ifaceLogPrettyAll;

        IffaceLogOut() {}
        IffaceLogOut(const QList<QByteArray> &ifaceLogArrLine, const QStringList &ifaceLogStr, const QByteArray &ifaceLogArrAll, const QString &ifaceLogPrettyAll) :
            ifaceLogArrLine(ifaceLogArrLine), ifaceLogStr(ifaceLogStr), ifaceLogArrAll(ifaceLogArrAll), ifaceLogPrettyAll(ifaceLogPrettyAll) {}

    };


    static IffaceLogOut getIffaceLogOut(const QTime &time, const QByteArray &arr, const QString &ifaceName, const bool &isRead);


signals:
    void ifaceLogStr(QString line); //<iface name> <time> <hex><data>  line 16 bytes

    void ifaceLogNonBuf(QString line);

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
