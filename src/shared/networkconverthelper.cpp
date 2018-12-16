#include "networkconverthelper.h"


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
