#include "proxytypesconverter.h"

ProxyTypesConverter::ProxyTypesConverter(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------

QVariantMap ProxyTypesConverter::getVarMapFromProxySett(const ProxySettStruct &sett)
{
    QVariantMap map;
    map.insert("enableProxy", sett.enableProxy);
    map.insert("proxyType", sett.proxyType);
    map.insert("host", sett.host);
    map.insert("port", sett.port);
    map.insert("hasUserAndPassword", sett.hasUserAndPassword);
    map.insert("lastUser", sett.lastUser);
    map.insert("lastPassword", sett.lastPassword);

    return map;
}

//------------------------------------------------------------------

ProxySettStruct ProxyTypesConverter::getProxySettFromVarMap(const QVariantMap &map)
{
//    bool enableProxy;
//    QNetworkProxy::ProxyType proxyType;
//    QString host;
//    quint16 port;

////#ifdef HASGUI4USR
//    bool hasUserAndPassword;//only for apps with GUI
////#endif
//    QString lastUser;
//    QString lastPassword;

    ProxySettStruct sett;
    sett.enableProxy        = map.value("enableProxy", false).toBool();
    sett.proxyType          = static_cast<QNetworkProxy::ProxyType>(map.value("proxyType", QNetworkProxy::DefaultProxy).toInt());
    sett.host               = map.value("host").toString();
    sett.port               = map.value("port").toUInt();
    sett.hasUserAndPassword = map.value("hasUserAndPassword", true).toBool();
    sett.lastUser           = map.value("lastUser").toString();
    sett.lastPassword       = map.value("lastPassword").toString();
    return sett;


}

//------------------------------------------------------------------

GlobalProxySettStruct ProxyTypesConverter::getGlobalProxySettFromVarHash(const QVariantHash &hash)
{
    GlobalProxySettStruct gsett;
    const QVariantMap hostm = hash.value("hostm").toMap();
    const QList<QString> lk = hostm.keys();


    for(int i = 0, imax = lk.size(); i < imax; i++)
       gsett.mapSettsByHost.insert(lk.at(i), getProxySettFromVarMap(hostm.value(lk.at(i)).toMap()));

    gsett.appGlobalSett = getProxySettFromVarMap(hash.value("appg").toMap());
    gsett.useAppGlobalAsDefault = hash.value("appgd", false).toBool();
    return gsett;
}

//------------------------------------------------------------------

QNetworkProxy ProxyTypesConverter::getProxySettForThisHost(const QString &host, const QString &routen, const GlobalProxySettStruct &gsett)
{
    return getProxySettForThisHost(host, routen, gsett.mapSettsByHost, gsett.useAppGlobalAsDefault ? gsett.appGlobalSett : ProxySettStruct());
}

//------------------------------------------------------------------

QNetworkProxy ProxyTypesConverter::getProxySettForThisHost(const QString &host, const QString &routen, const HostProxySetts &mapsett, const ProxySettStruct &defsett)
{
    Q_UNUSED(routen);
    /*

Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         0.0.0.0         0.0.0.0         U     0      0        0 ppp0
80.78.35.1      192.168.88.1    255.255.255.255 UGH   0      0        0 eth0
80.78.51.193    192.168.88.1    255.255.255.255 UGH   0      0        0 eth0
192.168.7.0     0.0.0.0         255.255.255.252 U     0      0        0 usb0
192.168.88.0    0.0.0.0         255.255.255.0   U     0      0        0 eth0
192.168.88.1    0.0.0.0         255.255.255.255 UH    0      0        0 eth0
192.200.1.21    0.0.0.0         255.255.255.255 UH    0      0        0 ppp0


*/
//    if(!mapsett.isEmpty()){

//        QStringList destinationips;
//        QMap<QString,QString> ip2iface;

//        if(true){
//            const QStringList routenl = routen.split("\n", QString::SkipEmptyParts);
//            for(int i = 2, imax = routenl.size(); i < imax; i++){
//                const QStringList oner = routenl.at(i).split(" ", QString::SkipEmptyParts);
//                if(oner.isEmpty())
//                    continue;
//                ip2iface.insert(oner.first(), oner.last());
//                destinationips.append(oner.first());
//            }

//        }

//        QString activeRouteDestIp = "0.0.0.0";//);//default route

//        QString activeIface = ip2iface.value(activeRouteDestIp);
//        if(true){//find the route
//            if(ip2iface.contains(host)){
//                activeRouteDestIp = host;
//                activeIface = ip2iface.value(activeRouteDestIp);
//            }else{

//            }

//        }



//        QStringList ifaceips;

//        QString thePrimaryIface;

//        if(!sett.iface2use.isEmpty() && !destaddr.isEmpty() && !routen.isEmpty()){


//        }

//    }

    return getProxySett(mapsett.contains(host) ? mapsett.value(host) : defsett);//I think it is better to use default app sett
}

//------------------------------------------------------------------

QNetworkProxy ProxyTypesConverter::getAppProxySett(const GlobalProxySettStruct &gsett)
{
    return getProxySettExt(gsett.appGlobalSett, QNetworkProxy::NoProxy);
}
//------------------------------------------------------------------

QNetworkProxy ProxyTypesConverter::getProxySett(const ProxySettStruct &sett)
{
    return getProxySettExt(sett, QNetworkProxy::DefaultProxy);
}

//------------------------------------------------------------------

QNetworkProxy ProxyTypesConverter::getProxySettExt(const ProxySettStruct &sett, const QNetworkProxy::ProxyType &proxyDisabledRetVal)
{
    if(!sett.enableProxy)
        return proxyDisabledRetVal;

    QNetworkProxy proxy;
    proxy.setType(sett.proxyType);
    proxy.setHostName(sett.host);
    proxy.setPort(sett.port);
    proxy.setUser(sett.lastUser);
    proxy.setPassword(sett.lastPassword);



    return proxy;
}

//------------------------------------------------------------------
