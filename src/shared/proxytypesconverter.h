#ifndef PROXYTYPESCONVERTER_H
#define PROXYTYPESCONVERTER_H

#include <QObject>
#include <QNetworkProxy>
#include <QVariantMap>
#include <QVariantHash>
#include <QVariantList>

#include "proxytypesconvertertypes.h"

class ProxyTypesConverter : public QObject
{
    Q_OBJECT
public:
    explicit ProxyTypesConverter(QObject *parent = nullptr);

    static QVariantMap getVarMapFromProxySett(const ProxySettStruct &sett);


    static ProxySettStruct getProxySettFromVarMap(const QVariantMap &map);

    static GlobalProxySettStruct getGlobalProxySettFromVarHash(const QVariantHash &hash);


    static QNetworkProxy getProxySettForThisHost(const QString &host, const QString &routen, const GlobalProxySettStruct &gsett);

    static QNetworkProxy getProxySettForThisHost(const QString &host, const QString &routen, const HostProxySetts &mapsett, const ProxySettStruct &defsett);


    static QNetworkProxy getAppProxySett(const GlobalProxySettStruct &gsett);


    static QNetworkProxy getProxySett(const ProxySettStruct &sett);

    static QNetworkProxy getProxySettExt(const ProxySettStruct &sett, const QNetworkProxy::ProxyType &proxyDisabledRetVal);




signals:

public slots:
};

#endif // PROXYTYPESCOVNERTER_H
