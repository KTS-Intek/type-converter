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

void IfaceHelper::showHexDump(QByteArray arr, QString ifaceName, bool isRead)
{
    const QString mask = ifaceName + QString( isRead ? " > " : " < " );
    const QString emptyMask = QString("").rightJustified(mask.length() + 13, ' ');

    const QString currenttime = QTime::currentTime().toString("hh:mm:ss.zzz");
    const QString instr = convertByteArr2asciiStr(arr, false) ;

    for(int ff = 0, ffMax = arr.size(); ff < ffMax; ff += 16){

        QString hexStr = arr.mid(ff,16).toHex().leftJustified(32, ' ').toUpper();
        emit ifaceLogArrLine(arr.mid(ff,16));

        for(int i = 30; i > 1; i -= 2)
            hexStr = hexStr.insert(i, " ");

        if(ff == 0)
            hexStr.prepend(mask + currenttime +" ");
        else
            hexStr.prepend(emptyMask);

        const QString s = QString("%1 %2").arg(hexStr).arg( convertByteArr2asciiStr(arr.mid(ff,16), false) ) ;
        if(disableCache)
            emit ifaceLogStr(s);
        else
            cache.append(s);

        qDebug() << s;

    }
    emit ifaceLogArrAll(arr);
    if(!instr.isEmpty())
        emit ifaceLogPrettyAll(QString("%1%2 %3").arg(mask).arg(currenttime).arg(instr));
}

void IfaceHelper::giveMeYourCache()
{
    disableCache = true;
    emit ifaceLogStr(cache.join("\n"));


}
