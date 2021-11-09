#include "macaddresshelper.h"
#include <QNetworkInterface>

#include "src/shared/networkconverthelper.h"
#include "ifacemanagerhelper.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

//--------------------------------------------------------------------------------------------

bool MacAddressHelper::isMacGood(const QString &mac)
{
#ifdef Q_OS_ANDROID
    return (!mac.startsWith("00:00:00:00") && !mac.toLower().startsWith("ff:ff:ff:ff") );
#else
    return (!mac.isEmpty() && !mac.startsWith("00:00:00:00") && !mac.toLower().startsWith("ff:ff:ff:ff") && mac.length() >= 10);
#endif
}
//--------------------------------------------------------------------------------------------

QStringList MacAddressHelper::getMacList()
{
    QStringList lmacs;

     const QList<QNetworkInterface> listIface = QNetworkInterface::allInterfaces();
     for(int i = 0, iMax = listIface.size(); i < iMax; i++){

         if(listIface.at(i).isValid()){

#ifdef Q_OS_LINUX
             if(listIface.at(i).humanReadableName().startsWith("tap") ||  listIface.at(i).humanReadableName().startsWith("tun"))
                 continue;
#endif
             const QString mac = listIface.at(i).hardwareAddress();
             if(isMacGood(mac) && !mac.isEmpty())
                 lmacs.append(mac);

         }
     }

     if(lmacs.size() > 2){//I need only 2
         QStringList lout;

         QMap<QString, QStringList> map;
         QStringList lk;


         for(int i = 0, imax = lmacs.size(); i < imax; i++){
             QString key = lmacs.at(i);
             key.chop(1);
             QStringList l = map.value(key);
             l.append(lmacs.at(i));
             map.insert(key, l);
             if(!lk.contains(key))
                 lk.append(key);
         }

         for(int i = 0, imax = lk.size(); i < imax; i++){
             const QStringList l = map.value(lk.at(i));
             if(l.size() > lout.size())
                 lout = l;
         }
         lmacs = lout.mid(0,2);
     }

 #ifdef Q_OS_ANDROID
//#ifndef SIMPLEMATILDA
     if(lmacs.isEmpty() || lmacs.join("").isEmpty()){
         const QAndroidJniObject s = QAndroidJniObject::callStaticObjectMethod<jstring>
                 (QString("ua/ktsintek/%1/CustomStorageInfo").arg(NAME4JAVA).toUtf8().data(), QByteArray("getMacAddress").data());

         if(s.toString().isEmpty() || s.toString().startsWith("00:00:00:")){
             //generate custom
             qsrand(qrand());
             QStringList l;
             l.append("FF");
             for(int i = 0; i < 9; i++)
                 l.append( QString::number((qrand() % ((0xFF + 1) - 1) + 1), 16).toUpper().rightJustified(2, '0') );
             lmacs.append(l.join(":"));
         }else{
             lmacs.append(s.toString().toUpper());
         }

         qDebug() << "mac java = " << s.toString() << lmacs;


     }
//#endif
 #endif
     if(!lmacs.isEmpty()){
         lmacs.removeDuplicates();
         std::sort(lmacs.begin(), lmacs.end());
     }
     return lmacs;
}

//--------------------------------------------------------------------------------------------

QString MacAddressHelper::getIfaceNameFromIP(const QHostAddress &ip)
{
    const QList<QNetworkInterface> listIface = QNetworkInterface::allInterfaces();
    for(int i = 0, iMax = listIface.size(); i < iMax ; i++){
        const QList<QNetworkAddressEntry> l = listIface.at(i).addressEntries();

        for(int j = 0, jMax = l.size(); j < jMax; j++){
            if( l.at(j).ip() == ip)
                return listIface.at(i).name();
        }
    }
    return QString();
}

//--------------------------------------------------------------------------------------------

QStringList MacAddressHelper::ifconfigOut()
{
    QStringList listIfaceStr;
    QStringList listIfaceName;

    const QList<QNetworkInterface> netIface = QNetworkInterface::allInterfaces();
    for(int i = 0, iMax = netIface.size(); i < iMax; i++){

        if(isMacGood(netIface.at(i).hardwareAddress())){
            listIfaceName.append(netIface.at(i).name());

            const QList<QNetworkAddressEntry> listIp = netIface.at(i).addressEntries();
            QStringList listIpstr4, listIpstr6;
            for(int j = 0, jMax = listIp.size(); j < jMax; j++){
                if(listIp.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol)
                    listIpstr4.append(listIp.at(j).ip().toString());
                else
                    listIpstr6.append(listIp.at(j).ip().toString());
            }

            listIfaceStr.append(QString("%1\tHWaddr %2\n"
                                        "IsRunning: %3\n"
                                        "IPv4: %4\n"
                                        "IPv6: %5\n")
                                .arg(netIface.at(i).humanReadableName())
                                .arg(netIface.at(i).hardwareAddress())
                                .arg( (netIface.at(i).flags() & QNetworkInterface::IsRunning) ? QString("yes") : QString("no") )
                                .arg( listIpstr4.join(" "))
                                .arg( listIpstr6.join(" "))
                                );

        }

    }

    int maxLen = 0;
    for(int i = 0, iMax = listIfaceName.size(); i < iMax; i++){
        if(listIfaceName.at(i).length() > maxLen)
            maxLen = listIfaceName.at(i).length() ;
    }

    QStringList listOut;
    for(int i = 0, iMax = listIfaceName.size(); i < iMax; i++){
        QString str = listIfaceName.at(i).leftJustified(maxLen, ' ') + "\t";
        const QStringList list = listIfaceStr.at(i).split("\n");
        str.append(list.first());
        for(int j = 1, jMax = list.size(); j < jMax; j++)
            str.append(QString().leftJustified(maxLen, ' ') + " " + list.at(j) + "\n");


        listOut.append( str );
    }
    return listOut;

}

//--------------------------------------------------------------------------------------------

bool MacAddressHelper::hasActiveOutConn(const bool &verboseMode)
{
//    const bool verboseMode = false;
    const QList<QNetworkInterface> listIface = QNetworkInterface::allInterfaces();

    for(int i = 0, iMax = listIface.size(); i < iMax ; i++){

        if(listIface.at(i).isValid() && (listIface.at(i).flags() & QNetworkInterface::IsRunning) ){
            if(listIface.at(i).flags() & QNetworkInterface::IsLoopBack )
                continue;

#ifdef Q_OS_LINUX
            if(IfaceManagerHelper::isPppName(listIface.at(i).name()))
                continue;
#endif

            if(!listIface.at(i).hardwareAddress().startsWith("00:00:00") && (!listIface.at(i).hardwareAddress().isEmpty() || (listIface.at(i).flags() & QNetworkInterface::IsPointToPoint))){

                const QList<QNetworkAddressEntry> l = listIface.at(i).addressEntries();



                for(int j = 0, jMax = l.size(); j < jMax; j++){


                    if(IfaceManagerHelper::ignoreThisIface( listIface.at(i).name(), l.at(j).ip(),l.at(j).netmask() ))
                        continue;


                    if(l.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol){
                        if(verboseMode) qDebug() << "ip4" << j << listIface.at(i).name() << l.at(j).netmask() << l.at(j).ip();

                        const quint32 ip4 = l.at(j).ip().toIPv4Address();
                        const quint32 mask4 =  l.at(j).netmask().toIPv4Address();
                        quint32 firstIp = ip4 & mask4;
                        firstIp++;
                        QHostAddress firstIpHa(firstIp);

                        if(firstIp == ip4){
                            if(verboseMode) qDebug() << "sharing over " << ip4 << firstIp << firstIpHa;
                            j += jMax;
                        }else{
                            if(verboseMode) qDebug() << "active connection " <<  ip4 << firstIp << firstIpHa;
                            return true;
                        }

                    }else{
                        if(l.at(j).ip().protocol() == QAbstractSocket::IPv6Protocol){

                            if(verboseMode) qDebug() << "ip6" << j << listIface.at(i).name() << l.at(j).netmask() << l.at(j).ip();

                            const Q_IPV6ADDR ip6 = l.at(j).ip().toIPv6Address();
                            const Q_IPV6ADDR mask6 = l.at(j).netmask().toIPv6Address();
                            Q_IPV6ADDR firstIp;
                            for(int i = 0; i < 16; i++)
                                firstIp[i] = ip6[i] & mask6[i];

                            firstIp[15] = (quint8)1;

                            QHostAddress firstIpHa(firstIp);
                            if(QHostAddress(ip6) == firstIpHa){
                                if(verboseMode) qDebug() << "sharing over " << QHostAddress(ip6) <<QHostAddress( firstIp) << firstIpHa;
                                 j += jMax;
                            }else{
                                if(verboseMode) qDebug() << "active connection " <<  QHostAddress(ip6) << QHostAddress(firstIp) << firstIpHa << l.at(j).netmask();
                                return true;
                            }
                        }
                    }
                }


            }
        }


    }

    return false;
}

//--------------------------------------------------------------------------------------------

IPadd2ifaceName MacAddressHelper::ipAddrVsIfaceName()
{
    QStringList listIp, listIfaceName;

    const QList<QNetworkInterface> listIface = QNetworkInterface::allInterfaces();
    for(int i = 0, iMax = listIface.size(); i < iMax ; i++){

//        qDebug() << "listIface.at=" << i << listIface.at(i).isValid() << listIface.at(i).flags();
        if(listIface.at(i).isValid() && (listIface.at(i).flags() & QNetworkInterface::IsRunning) ){
            if(listIface.at(i).flags() & QNetworkInterface::IsLoopBack )
                continue;

            if(isMacGood(listIface.at(i).hardwareAddress()) && (!listIface.at(i).hardwareAddress().isEmpty() || (listIface.at(i).flags() & QNetworkInterface::IsPointToPoint))){

                const QList<QNetworkAddressEntry> l = listIface.at(i).addressEntries();



                for(int j = 0, jMax = l.size(); j < jMax; j++){

                    listIp.append(NetworkConvertHelper::showNormalIP(l.at(j).ip()));
                    listIfaceName.append(listIface.at(i).name());

                    if(l.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol){
                        const quint32 ip4 = l.at(j).ip().toIPv4Address();
                        const quint32 mask4 =  l.at(j).netmask().toIPv4Address();
                        quint32 firstIp = ip4 & mask4;
                        firstIp++;
                        const QHostAddress firstIpHa(firstIp);

                        if(firstIp != ip4){
                            listIp.append(NetworkConvertHelper::showNormalIP(firstIpHa));
                            listIfaceName.append(listIface.at(i).name());
                        }
                    }else{
                        if(l.at(j).ip().protocol() == QAbstractSocket::IPv6Protocol){

                            const Q_IPV6ADDR ip6 = l.at(j).ip().toIPv6Address();
                            const Q_IPV6ADDR mask6 = l.at(j).netmask().toIPv6Address();
                            Q_IPV6ADDR firstIp;
                            for(int i = 0; i < 16; i++)
                                firstIp[i] = ip6[i] & mask6[i];

                            firstIp[15] = (quint8)1;

                            const QHostAddress firstIpHa(firstIp);
                            if(QHostAddress(ip6) != firstIpHa){
                                listIp.append(firstIpHa.toString());
                                listIfaceName.append( listIface.at(i).name());
                            }
                        }
                    }
                }


            }
        }


    }

    return IPadd2ifaceName(listIp,listIfaceName);
}

//--------------------------------------------------------------------------------------------

QStringList MacAddressHelper::getTcpMacIP()
{
    QStringList listIpMac;

    const QList<QNetworkInterface> netIface = QNetworkInterface::allInterfaces();
    for(int i = 0, iMax = netIface.size(); i < iMax; i++){

        if(isMacGood(netIface.at(i).hardwareAddress())){

            const QList<QNetworkAddressEntry> listIp = netIface.at(i).addressEntries();
            for(int j = 0, jMax = listIp.size(); j < jMax; j++){
                const QString ip = listIp.at(j).ip().toString();
                listIpMac.append( QString("%1|%2").arg(netIface.at(i).hardwareAddress()).arg( ip.contains("%") ? ip.mid(0, ip.indexOf("%")) : ip) );
            }
        }
    }
    return listIpMac;
}

//--------------------------------------------------------------------------------------------

QStringList MacAddressHelper::getIpList(const bool &ignoreLoopBack)
{
    QStringList listIp;

    const QList<QNetworkInterface> listIface = QNetworkInterface::allInterfaces();
    for(int i = 0, iMax = listIface.size(); i < iMax ; i++){

        if(listIface.at(i).isValid() && (listIface.at(i).flags() & QNetworkInterface::IsRunning) ){
            if(ignoreLoopBack && (listIface.at(i).flags() & QNetworkInterface::IsLoopBack ))
                continue;

            const QList<QNetworkAddressEntry> l = listIface.at(i).addressEntries();

            for(int j = 0, jMax = l.size(); j < jMax; j++)
                listIp.append(NetworkConvertHelper::showNormalIP(l.at(j).ip()));

        }
    }
    return listIp;
}


//--------------------------------------------------------------------------------------------
