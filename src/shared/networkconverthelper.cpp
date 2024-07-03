#include "networkconverthelper.h"
#include <QUrl>
#include <QRegularExpression>
#include <QDateTime>
#include <QSysInfo>


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

bool NetworkConvertHelper::isIpGood(const QString &ip, const QStringList &allowlist)
{
    if(allowlist.isEmpty())
        return true;

    for(int i = 0, imax = allowlist.size(); i < imax; i++){

        const QRegularExpression rx(allowlist.at(i), QRegularExpression::ExtendedPatternSyntaxOption);

        if(rx.isValid()){
            if(rx.match(ip, 0, QRegularExpression::NormalMatch).hasMatch()){
                return true;
            }
        }else{
            if(ip == allowlist.at(i)){
                return true;
            }
        }


    }
    return false;
}

//-------------------------------------------------------------------------

QStringList NetworkConvertHelper::fromETSFile(const QString &lines)
{
    // 0x - hex, or dec
//    DESCRIPTION Sniffer__Fri_Aug_2_2013_10_17_29
//    CHANNEL_FINAL 0x18
//    ID_FINAL 0x80B
//    KEY_FINAL f
    const QStringList l =  QString(lines).replace("\r\n", "\n").replace("\r", "\n").split("\n",
                                                                                      #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                                                                          Qt::SkipEmptyParts
                                                                                      #else
                                                                                          QString::SkipEmptyParts
                                                                                      #endif
                                                                                          );

    QStringList params;

    if(l.size() > 3 && l.at(0).startsWith("DESCRIPTION ")
            && l.at(1).startsWith("CHANNEL_FINAL ")
            && l.at(2).startsWith("ID_FINAL ")
            && (l.at(3).startsWith("KEY_FINAL ") )){ //|| l.at(3).startsWith("KEY_CRYPTO "))){

        QString ch, id, ky;


        QStringList ll = l.at(1).split(" ",
                               #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                   Qt::SkipEmptyParts
                               #else
                                   QString::SkipEmptyParts
                               #endif
                                   );
        if(ll.size() > 1)
            ch = ll.at(1).simplified().trimmed();

        ll = l.at(2).split(" ",
                   #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                       Qt::SkipEmptyParts
                   #else
                       QString::SkipEmptyParts
                   #endif
                       );
        if(ll.size() > 1)
            id = ll.at(1).simplified().trimmed();


        ll = l.at(3).split(" ",
                   #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                       Qt::SkipEmptyParts
                   #else
                       QString::SkipEmptyParts
                   #endif
                       );
        if(ll.size() > 1)
            ky = ll.at(1).simplified().trimmed();

        //        if(l.at(3).startsWith("KEY_CRYPTO ")){
        //            ky = cryptoF(ky,0,1);
        //            if(ky == "ERROR")
        //                ky.clear();
        //        }


        bool okCh, okId;
        int channel = ch.toInt(&okCh);
        int netid = id.toInt(&okId);

        if(!okCh)
            channel = ch.toInt(&okCh,16);
        if(!okId)
            netid = id.toInt(&okId, 16);

        if(channel > 10 && channel < 27 && netid >= 0 && netid <= 0x3FFF && okCh && okId){
            params.append(QString::number(channel));
            params.append(QString::number(netid));
            params.append(ky);


        }

    }

    return params;
}

//-------------------------------------------------------------------------

QString NetworkConvertHelper::toETSFile(const QStringList &params, const QString &description)
{
//    out.append(QString::number(v.channel));
//    out.append(QString::number(v.id));
//    out.append(v.key);



    if(params.size() < 3)
        return QString();

    QStringList list;

    list.append(QString("DESCRIPTION %1 %2 %3 %4")
                .arg(description)
                .arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"))
                .arg(QSysInfo::machineHostName())
                .arg(QSysInfo::prettyProductName()).simplified().trimmed());

    list.append(QString("CHANNEL_FINAL 0x%1").arg(QString::number(params.at(0).toInt(), 16).toUpper()));
    list.append(QString("ID_FINAL 0x%1").arg(QString::number(params.at(1).toInt(), 16).toUpper() ));
    list.append(QString("KEY_FINAL %1").arg(QString(params.at(2)).simplified().trimmed()));

    return list.join("\r\n");
}


//-------------------------------------------------------------------------
