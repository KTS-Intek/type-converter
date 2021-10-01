#ifndef NETWORKCONVERTHELPER_H
#define NETWORKCONVERTHELPER_H

#include <QHostAddress>
#include <QStringList>

struct HostNamePort
{
    QString hostName;
    quint16 port;
    HostNamePort() {}
    HostNamePort(const QString &hostName, const quint16 &port) : hostName(hostName), port(port) {}
};

class NetworkConvertHelper
{
public:
    static QString showNormalIP(const QHostAddress &hAddr);

    static QString showNormalIP(const QString &ip);

    static QStringList removePortsFromListIpPort(const QStringList &inList);

    static QStringList removePortsFromListHostPort(const QStringList &inList);

    static HostNamePort getHostAndPortFromLine(const QString &line, const quint16 &defPort);

    static QString getHostsFromSvahaHash(const QVariantHash &svahaHash);

    static bool isIpAddress(const QString &s);

    static QStringList removeNotAllowedHostAddr(const bool &hasDns, const QStringList &hostAddrList);//checkIpAndUrl

    static bool isIpGood(const QString &ip, const QStringList &allowlist);


};

#endif // NETWORKCONVERTHELPER_H
