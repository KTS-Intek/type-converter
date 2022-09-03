#include "ifacehelper.h"
#include <QDateTime>
#include <QDebug>

IfaceHelper::IfaceHelper(const bool &disableCache, QObject *parent) : QObject(parent), disableCache(disableCache)
{

}

QString IfaceHelper::convertByteArr2asciiStr(const QByteArray &arr, const bool ommitRightDot)
{
    QString s;
    for(int i = 0, iMax = arr.length(); i < iMax; i++){
        QString a( QString(arr.at(i)).toLatin1() );
        if(a != " ")
            a = a.simplified().trimmed();

        if((qint8)arr.at(i) < 0x20 || (qint8)arr.at(i) == 0x7f || a.isEmpty() )
            s.append(".");
        else
            s.append(a);
    }
    while(ommitRightDot && !s.isEmpty() && s.right(1) == ".")
        s.chop(1);
    return s;
}

IfaceHelper::IffaceLogOut IfaceHelper::getIffaceLogOut(const QTime &time, const QByteArray &arr, const QString &ifaceName, const bool &isRead)
{
    IffaceLogOut iface;
    const QString currenttime = time.isValid() ? time.toString("hh:mm:ss.zzz") : "";

    const int emptySpace = currenttime.size() + 1;

    const QString mask = ifaceName + QString( isRead ? " > " : " < " );
    const QString emptyMask = QString("").rightJustified(mask.length() + emptySpace, ' ');

    const QString instr = convertByteArr2asciiStr(arr, false) ;

    for(int ff = 0, ffMax = arr.size(); ff < ffMax; ff += 16){

        QString hexStr = arr.mid(ff,16).toHex().leftJustified(32, ' ').toUpper();
        iface.ifaceLogArrLine.append(arr.mid(ff,16));

        for(int i = 30; i > 1; i -= 2)
            hexStr = hexStr.insert(i, " ");

        if(ff == 0)
            hexStr.prepend(mask + currenttime +" ");
        else
            hexStr.prepend(emptyMask);

        const QString s = QString("%1 %2").arg(hexStr).arg( convertByteArr2asciiStr(arr.mid(ff,16), false) ) ;
        iface.ifaceLogStr.append(s);
    }
    iface.ifaceLogArrAll = arr;
    if(!instr.isEmpty())
        iface.ifaceLogPrettyAll = QString("%1%2 %3").arg(mask).arg(currenttime).arg(instr);
    return iface;
}

void IfaceHelper::showHexDump(QByteArray arr, QString ifaceName, bool isRead)
{
    showHexDumpExt(QDateTime::currentDateTime(), arr, ifaceName, isRead);

}

void IfaceHelper::showHexDumpExt(QDateTime dt, QByteArray arr, QString ifaceName, bool isRead)
{
    const IffaceLogOut iface = getIffaceLogOut(dt.time(), arr, ifaceName, isRead);

    for(int i = 0, imax = iface.ifaceLogStr.size(); i < imax; i++){
        emit ifaceLogArrLine(iface.ifaceLogArrLine.at(i));
        emit ifaceLogNonBuf(iface.ifaceLogStr.at(i));

        if(disableCache)
            emit ifaceLogStr(iface.ifaceLogStr.at(i));
        else
            cache.append(iface.ifaceLogStr.at(i));
    }
    emit ifaceLogArrAll(iface.ifaceLogArrAll);
    if(!iface.ifaceLogPrettyAll.isEmpty())
        emit ifaceLogPrettyAll(iface.ifaceLogPrettyAll);
}

void IfaceHelper::giveMeYourCache()
{
    disableCache = true;
    emit ifaceLogStr(cache.join("\n"));


}
