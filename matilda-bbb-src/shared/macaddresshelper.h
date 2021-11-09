#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QStringList>
#include <QHostAddress>
#include <QPair>

struct IPadd2ifaceName
{
    QStringList listIp;
    QStringList listIfaceName;
    IPadd2ifaceName() {}
    IPadd2ifaceName(const QStringList &listIp, const QStringList &listIfaceName) : listIp(listIp), listIfaceName(listIfaceName) {}
};

class MacAddressHelper
{
public:
    static bool isMacGood(const QString &mac);

    static QStringList getMacList();

    static QString getIfaceNameFromIP(const QHostAddress &ip);

    static QStringList ifconfigOut();

    static bool hasActiveOutConn(const bool &verboseMode);


    static IPadd2ifaceName ipAddrVsIfaceName();

    static QStringList getTcpMacIP();

    static QStringList getIpList(const bool &ignoreLoopBack);


};

#endif // MACADDRESS_H
