#include "ifacemanagerhelper.h"


bool IfaceManagerHelper::isPppName(const QString &name){ return (name.contains("ppp") && (name == "ppp0" || name.mid(3).toInt() > 0) ); }


bool IfaceManagerHelper::ignoreThisIface(const QString &name, const QHostAddress &ip, const QHostAddress &mask)
{
    if(ip.protocol() == QAbstractSocket::IPv4Protocol){
        if(name == "usb0" && ip.toIPv4Address()  == QHostAddress("192.168.7.2").toIPv4Address() && mask.toIPv4Address() == QHostAddress("255.255.255.252").toIPv4Address())
            return true;
    }else{
        if(ip.protocol() == QAbstractSocket::IPv6Protocol){
            if(ip.toString().left(5).toLower() == "fe80:" && name == "usb0" && mask == QHostAddress("ffff:ffff:ffff:ffff::"))
                return true;
        }
    }
    return false;
}
