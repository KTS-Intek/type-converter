#include "networkconverthelper.h"
#include <QUrl>
#include <QRegularExpression>


QString NetworkConvertHelper::showNormalIP(const QHostAddress &hAddr){ return showNormalIP(hAddr.toString()); }

QString NetworkConvertHelper::showNormalIP(const QString &ip){ return (ip.left(7).toLower() == "::ffff:" && ip.contains(".")) ? ip.mid(7) : ip; } //fucking Qt5 bug(


QStringList NetworkConvertHelper::removePortsFromListIpPort(const QStringList &inList)
{
    QStringList l;
    for(int i = 0, iMax = inList.size(); i < iMax; i++){
        QString host = inList.at(i);
        if((host.count(".") == 3 && host.count(":") == 1) || (host.contains("]:") && host.left(1) == "[")  ){
            const HostNamePort pair = getHostAndPortFromLine(host, 0);
            if(pair.port > 0 && !pair.hostName.isEmpty())
                host = pair.hostName;
        }
        if(l.contains(host))
            continue;
        l.append(host);
    }
    return l;
}
//-------------------------------------------------------------------------
QStringList NetworkConvertHelper::removePortsFromListHostPort(const QStringList &inList)
{
    QStringList l;
    for(int i = 0, iMax = inList.size(); i < iMax; i++){
        QString host = inList.at(i);
        if(host.contains(".") && host.contains(":")){
            const HostNamePort pair = getHostAndPortFromLine(host, 0);
            if(pair.port > 0 && !pair.hostName.isEmpty())
                host = pair.hostName;
        }
        if(l.contains(host))
            continue;
        l.append(host);
    }
    return l;
}

//-------------------------------------------------------------------------

HostNamePort NetworkConvertHelper::getHostAndPortFromLine(const QString &line, const quint16 &defPort)
{
    QString host = line;
    quint16 port = defPort;

    if(line.contains(":")){
        if(line.contains("]:")){
            if(!line.split("]:").last().isEmpty() && line.split("]:").last() != "0")
                port = line.split("]:").last().toUInt();

            host = line.split("]:").first();
            if(host.left(1) == "[")
                host = host.mid(1);
        }else{
            if(!line.split(":").last().isEmpty() && line.split(":").last() != "0")
                port = line.split(":").last().toUInt();

            host = line.split(":").first();
        }
    }

    return HostNamePort(host,port);
}

//-------------------------------------------------------------------------

QString NetworkConvertHelper::getHostsFromSvahaHash(const QVariantHash &svahaHash)
{
    const QList<QString> lk = svahaHash.keys();
    QStringList listIp;
    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        const QString host = getHostAndPortFromLine(lk.at(i), 1).hostName;
        if(!host.isEmpty() && !listIp.contains(host))
            listIp.append(host);
    }
    return listIp.join("\n");
}


//-------------------------------------------------------------------------


bool NetworkConvertHelper::isIpAddress(const QString &s)
{
#ifdef MTD_DISABLE_NETWORK
return true;
#else
    return (QHostAddress(s).protocol() == QAbstractSocket::IPv4Protocol || QHostAddress(s).protocol() == QAbstractSocket::IPv6Protocol);
#endif
}

//-------------------------------------------------------------------------

QStringList NetworkConvertHelper::removeNotAllowedHostAddr(const bool &hasDns, const QStringList &hostAddrList)
{
    QStringList l;
#ifndef MTD_DISABLE_NETWORK
    for(int i = 0, iMax = hostAddrList.size(); i < iMax; i++){
        if(isIpAddress(hostAddrList.at(i))){
            l.append(hostAddrList.at(i));
        }else{
            if(hasDns){
                const QUrl u(hostAddrList.at(i));
                if(u.isValid())
                    l.append(hostAddrList.at(i));
            }
        }
    }
#endif
    return l;
}

//-------------------------------------------------------------------------

bool NetworkConvertHelper::isIpGood(const QString &ip, const QStringList &whitelist)
{
    if(whitelist.isEmpty())
        return true;

    for(int i = 0, imax = whitelist.size(); i < imax; i++){

        const QRegularExpression rx(whitelist.at(i), QRegularExpression::ExtendedPatternSyntaxOption);

        if(rx.isValid()){
            if(rx.match(ip, 0, QRegularExpression::NormalMatch).hasMatch()){
                return true;
            }
        }else{
            if(ip == whitelist.at(i)){
                return true;
            }
        }


    }
    return false;
}


//-------------------------------------------------------------------------
