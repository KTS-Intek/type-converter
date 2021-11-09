#ifndef PROXYTYPESCONVERTERTYPES_H
#define PROXYTYPESCONVERTERTYPES_H

#include <QNetworkProxy>
#include <QMap>

struct ProxySettStruct
{
    bool enableProxy;
    QNetworkProxy::ProxyType proxyType;
    QString host;
    quint16 port;

//#ifdef HASGUI4USR
    bool hasUserAndPassword;//only for apps with GUI
//#endif
    QString lastUser;
    QString lastPassword;

    ProxySettStruct() : enableProxy(false), proxyType(QNetworkProxy::DefaultProxy), port(0), hasUserAndPassword(false) {}

    ProxySettStruct(const bool &enableProxy, const QNetworkProxy::ProxyType &proxyType, const QString &host, const quint16 &port,
                    const bool &hasUserAndPassword, const QString &lastUser, const QString &lastPassword) :
    enableProxy(enableProxy), proxyType(proxyType), host(host), port(port), hasUserAndPassword(hasUserAndPassword), lastUser(lastUser), lastPassword(lastPassword){}
};

typedef QMap<QString, ProxySettStruct> HostProxySetts; //Host to sett, if not found use default


struct GlobalProxySettStruct
{
    bool useAppGlobalAsDefault;

    HostProxySetts mapSettsByHost;

    ProxySettStruct appGlobalSett;

    GlobalProxySettStruct() : useAppGlobalAsDefault(false) {}

    GlobalProxySettStruct(const bool &useAppGlobalAsDefault, const HostProxySetts &mapSettsByHost, const ProxySettStruct &appGlobalSett) :
        useAppGlobalAsDefault(useAppGlobalAsDefault), mapSettsByHost(mapSettsByHost), appGlobalSett(appGlobalSett) {}

};


#endif // PROXYTYPESCONVERTERTYPES_H
