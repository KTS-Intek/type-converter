#include "prettyvalues.h"
#include "definedpollcodes.h"
#include <QDate>
#include <QTime>
#include "matildalimits.h"
#include "ifaceconnectiondefs.h"

//------------------------------------------------------------------------------------

QString PrettyValues::getBuildDateStr()
{
    //linux style
    /* date -u '+%H:%M:%S'
     *  14:28:31
     *
     * date -u '+%Y/%m/%d'
     * 2019/05/16
     *

 %date%
16.05.2019

 %time%
17:26:47,27
     */

    return
        #ifdef Q_OS_WIN
            QDate::fromString(QString::fromLocal8Bit(BUILDDATE), "dd.MM.yyyy").toString("yyyy/MM/dd")
        #else
            QString::fromLocal8Bit(BUILDDATE)
        #endif
            + " " +  QString::fromLocal8Bit(BUILDTIME).left(8);

    //    return QString::fromLocal8Bit(BUILDDATE) + " " + QString::fromLocal8Bit(BUILDTIME);
}

//------------------------------------------------------------------------------------

QDateTime PrettyValues::getBuildDate()
{
    const QString dtstr = getBuildDateStr();
    const QString separ = dtstr.contains("/") ? "/" : "-";
    const QDateTime dt = QDateTime(QDate::fromString(dtstr.left(10), QString("yyyy%1MM%1dd").arg(separ)),
                                   QTime::fromString(dtstr.right(8),QString("hh:mm:ss")), Qt::UTC);//  QDateTime::fromString(dtstr, QString("yyyy%1MM%1dd hh:mm:ss").arg(separ));
//    return dt.isValid() ? dt : QDateTime(QDate(2019,1,1), QTime(0,0,0,0));
    const int addHours =
#ifdef Q_OS_WIN
    -10
#else
     0
        #endif
    ;

    return dt.isValid() ? dt.addSecs(3600 * addHours) : QDateTime(QDate(2019,1,1), QTime(0,0,0,0));

}

QString PrettyValues::prettyTimeValueFromSecsWitAMask(const qint64 &secsmynulo)
{
    QString f;
    return QObject::tr("%1 [%2]").arg(prettyTimeValue(f, secsmynulo * 1000)).arg(f);
}

//------------------------------------------------------------------------------------

QString PrettyValues::prettyTimeValueFromSecs(const qint64 &secsmynulo)
{
    return prettyTimeValue(secsmynulo * 1000);
}

//------------------------------------------------------------------------------------

QString PrettyValues::prettyTimeValue(const qint64 &msecmynulo)
{
    QString f;
    return prettyTimeValue(f, msecmynulo);
}

QString PrettyValues::prettyTimeValueMsec(const qint64 &msecmynulo)
{
    QString f;
    return prettyTimeValueExt(true, f, msecmynulo);
}

//------------------------------------------------------------------------------------

QString PrettyValues::prettyTimeValue(QString &f, qint64 msecmynulo)
{
    return prettyTimeValueExt(false, f, msecmynulo);

}

QString PrettyValues::prettyTimeValueExt(const bool &addmsec, QString &f, qint64 msecmynulo)
{

    f = QObject::tr("hh:mm:ss");
    QString s = "";

    QString prependformat;
    if(msecmynulo >= 31557600000){ //1 year 126230400000){ //greater or equal 4 years
        prependformat.append(QObject::tr("y' "));
        s.append(QString::number( (msecmynulo/31557600000) ) + "' ");
        msecmynulo %= 31557600000;
    }

    if(msecmynulo >= 86400000){ //1 day
        prependformat.append(QObject::tr("d "));
        s.append(QString::number(msecmynulo/86400000) + " ");
        msecmynulo %= 86400000;
    }

    if(!prependformat.isEmpty())
        f.prepend(prependformat);

    s.append(QString::number(msecmynulo/3600000).rightJustified(2,'0') + ":");//hh
    if(msecmynulo >= 3600000)
        msecmynulo %= 3600000;


    s.append(QString::number(msecmynulo/60000).rightJustified(2,'0') + ":");//mm
    if(msecmynulo >= 60000)
        msecmynulo %= 60000;

    s.append(QString::number(msecmynulo/1000).rightJustified(2,'0'));//ss

    if(addmsec){
        msecmynulo %= 1000;
        f.append(".zzz");
        s.append("." + QString::number(msecmynulo).rightJustified(3,'0'));//msec
    }
    return s;
}

//------------------------------------------------------------------------------------

//QString PrettyValues::tablenameEnd4pollCode(const quint8 &pollCode)
//{
//    if(pollCode == POLL_CODE_READ_TOTAL || pollCode == POLL_CODE_READ_POWER || pollCode == POLL_CODE_READ_VOLTAGE || pollCode == POLL_CODE_READ_METER_LOGBOOK ||
//            pollCode == POLL_CODE_READ_METER_STATE ||
//            pollCode == POLL_CODE_WTR_TOTAL || pollCode == POLL_CODE_WTR_PERIOD || pollCode == POLL_CODE_WTR_INSTANT_VLS || pollCode == POLL_CODE_WTR_METER_LOGBOOK ||
//            pollCode == POLL_CODE_WTR_METER_STATE)
//        return "_00_000";//_ss_zzz

//    return "_59_999";
//}

//------------------------------------------------------------------------------------

QDateTime PrettyValues::tableName2DateTime(const QString &tableName, const qint32 addDays, const bool useLocal)
{
    if(tableName.mid(4,1) != "_")
        return QDateTime( QDate::fromString(tableName.mid(4, 10), "yyyy_MM_dd"), QTime::fromString(tableName.right(5), "hh_mm"), useLocal ? Qt::LocalTime : Qt::UTC ).addDays(addDays);

    return QDateTime( QDate::fromString(tableName.left(10), "yyyy_MM_dd"), QTime::fromString(tableName.right(5), "hh_mm"), useLocal ? Qt::LocalTime : Qt::UTC ).addDays(addDays);

}

//------------------------------------------------------------------------------------

QString PrettyValues::getTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode)
{
    QString tableName;
    switch(pollCode){
    case POLL_CODE_WTR_END_MONTH        :
    case POLL_CODE_READ_END_MONTH       : tableName = QString("%1_%2_23_59").arg(dtPoll.toString("yyyy_MM")).arg(QString::number(dtPoll.date().daysInMonth()).rightJustified(2,'0')); break;

    case POLL_CODE_WTR_END_DAY          :
    case POLL_CODE_READ_END_DAY         : tableName = QString("%1_23_59").arg(dtPoll.toString("yyyy_MM_dd")); break;

    case POLL_CODE_WTR_METER_LOGBOOK    :
    case POLL_CODE_READ_METER_LOGBOOK   : tableName = QString("%1_00_00").arg(dtPoll.addDays(1).toUTC().toString("yyyy_MM_dd")); break;


    case POLL_CODE_WTR_METER_STATE      :
    case POLL_CODE_WTR_PERIOD           :
    case POLL_CODE_WTR_INSTANT_VLS      :
    case POLL_CODE_WTR_TOTAL            :

    case POLL_CODE_READ_METER_STATE     :
    case POLL_CODE_READ_POWER           :
    case POLL_CODE_READ_VOLTAGE         :
    case POLL_CODE_READ_TOTAL           : tableName = dtPoll.toUTC().toString("yyyy_MM_dd_hh_mm"); break;




    default:{

        if(pollCode < POLL_CODE_READ_METER_LOGBOOK)
            tableName = QString("%1_00_00").arg(dtPoll.toUTC().toString("yyyy_MM_dd"));//the beginning of the day
        else
            tableName = dtPoll.toUTC().toString("yyyy_MM_dd_hh_mm");
        //        tableName.clear();
        break;}

    }
    return tableName;
}

//------------------------------------------------------------------------------------

QString PrettyValues::getFullTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode)
{
    return QString("%1_%2").arg(QString::number(pollCode).rightJustified(3, '0')).arg(getTableName4poll(dtPoll, pollCode));// dtPoll.toString("yyyy_MM_dd_hh_mm"));

}

//------------------------------------------------------------------------------------

QDateTime PrettyValues::getDateTime4poll(const QDateTime &dtPoll, const quint8 &pollCode)
{
    return tableName2DateTime(getTableName4poll(dtPoll, pollCode));

}


//--------------------------------------------------------------

QString PrettyValues::prettyNumber(const qreal &val, int mPrec)
{
    return prettyNumber(val, mPrec, MAX_PRECISION);
}

//--------------------------------------------------------------

QString PrettyValues::prettyNumber(const qreal &val, int mPrec, const int &maxPlgPrec)
{
    //    if(mPrec < 1 || mPrec > maxPlgPrec)
    //        return "";

    //    QString s = QString::number(val, 'f', mPrec);
    //    s = s.replace(",", ".");
    //    if(s.isEmpty())
    //        return s;
    //    while(s.right(1) == "0")
    //        s.chop(1);


    //    if(s == "0." || s.isEmpty())
    //        return "0";

    //    if(s.right(1) == ".")
    //        s.append("0");

    //    return s;


    mPrec = qMin(qMax(mPrec, 1), maxPlgPrec);

    QString s = QString::number(val, 'f', mPrec);
    s = s.replace(",", ".");
    if(s.isEmpty())
        return s;
    while(s.right(1) == "0")
        s.chop(1);

    if(s.right(1) == ".")
        s.chop(1);

    if(s == "0." || s.isEmpty())
        return "0";

    return s;
}

//--------------------------------------------------------------

QString PrettyValues::prettyLongNumber(const QString &s)
{
    bool ok;
    int val = s.toInt(&ok);

    return ok ? prettyLongNumber(val) : s;
}

//--------------------------------------------------------------

QString PrettyValues::prettyLongNumber(const int &v)
{
    QString ss = QString::number(v);
    QStringList l;
    for(int i = 0, iMax = ss.length(); i < iMax; i += 3){
        l.prepend(ss.right(3));
        ss.chop(3);
    }
    if(!ss.isEmpty())
        l.prepend(ss);
    return l.join(" ");
}

//--------------------------------------------------------------

QString PrettyValues::prettyBabloNumber(const QString &s)
{
    bool ok;
    s.toDouble(&ok);
    QString r = s;
    if(ok){
        r.clear();
        QString ss = s;
        int chopSize = 3;
        if(ss.contains("."))
            chopSize += ss.length() - ss.indexOf(".") ;
        else if(ss.contains(","))
            chopSize += ss.length() - ss.indexOf(",") ;

        QStringList l;
        for(int i = 0, iMax = ss.length(); i < iMax; i += chopSize, chopSize = 3){
            l.prepend(ss.right(chopSize));
            ss.chop(chopSize);
        }
        if(!ss.isEmpty())
            l.prepend(ss);
        r = l.join(" ");
    }
    return r;
}

QString PrettyValues::prettyHexDump(const QList<quint8> &list, const quint8 &command)
{
    QByteArray arr;
    for(int i = 0, iMax = list.size(); i < iMax; i++)
        arr.append(list.at(i));
    arr = arr.toHex();
    QString str;
    for(int i = 0, iMax = arr.size(); i < iMax; i += 2)
        str.append(arr.mid(i,2) + " ");

    if(!str.isEmpty())
        str.chop(1);
    //    if(str.isEmpty())
    //        return "";

    if(!str.isEmpty())
        str.prepend(", D:");

    str.prepend(", C:" + QString::number(command, 16).toUpper());
    return  str.toUpper();
}

QString PrettyValues::prettyHexDump(const QByteArray &messArrH, const QByteArray &commandH, const quint8 &errCode)
{
    QByteArray arr(messArrH);

    QString str;
    for(int i = 0, iMax = arr.size(); i < iMax; i += 2)
        str.append(arr.mid(i,2) + " ");

    if(!str.isEmpty())
        str.chop(1);


    if(!str.isEmpty())
        str.prepend(", D:");

    if(!commandH.isEmpty()){
        str.prepend(", C:" + commandH.toUpper());
        str.append(", E:" + QString::number(errCode, 16).toUpper());
    }
    return  str.toUpper();
}

//--------------------------------------------------------------

QString PrettyValues::prettyHexDump(QByteArray arr)
{
    arr = arr.toHex();
    QString str;
    for(int i = 0, iMax = arr.size(); i < iMax; i += 2)
        str.append(arr.mid(i,2) + " ");

    if(!str.isEmpty())
        str.chop(1);
    if(str.isEmpty())
        return "";
    str.prepend(", D:");

    return  str.toUpper();
}

//--------------------------------------------------------------

void PrettyValues::removeLineFromList(const QString &lPartOfline, QStringList &l)
{
    for(int i = 0, iMax = l.size(), left = lPartOfline.size(); i < iMax; i++){
        if(l.at(i).left(left) == lPartOfline){
            l.removeAt(i);
            i--;
            iMax--;
        }
    }
}

//--------------------------------------------------------------

QStringList PrettyValues::replaceLineFromList(const QString &lPartOfline, QStringList l, const QString &rPartOfLine)
{
    for(int i = 0, iMax = l.size(), left = lPartOfline.size(); i < iMax; i++){
        if(l.at(i).left(left) == lPartOfline){
            l.replace(i, lPartOfline + rPartOfLine);
            return l;
        }
    }
    l.append(lPartOfline + rPartOfLine);
    return l;
}

QString PrettyValues::humanByteView(QString str)
{
    QString retVal = str.right(3);
    str.chop(3);

    while(!str.isEmpty()){
        retVal.prepend(str.right(3) + " ");
        str.chop(3);
    }
    return retVal;
}

QString PrettyValues::humanByteView(const qint64 &val)
{
    return humanByteView(QString::number(val));

}

QString PrettyValues::addWithFontColorRed(const QString m)
{
    return QString("<font color=red>%1</font>").arg(m);

}

QString PrettyValues::byte2humanRead(const qint64 &bytes)
{
    if(bytes > 10000000)
        return QString::number(bytes / 1000000) + QObject::tr("M");

    if(bytes > 10000)
        return QString::number(bytes / 1000) + QObject::tr("K");

    return QString::number(bytes);


}

//--------------------------------------------------------------

QString PrettyValues::connectionsett2prettyHuman(const QString &ip, const quint16 &port, const QString &login, const QString &objname, const QString &optionalmac)
{
    QStringList l;
    l.append(QString("[%1]:%2").arg(ip.simplified().trimmed()).arg(int(port)));
    l.append(login);
    l.append(objname);
    if(!optionalmac.isEmpty())
        l.append(optionalmac);

    return l.join(", ");
}

QString PrettyValues::getPrettyIfaceName(const QVariantHash &h)
{
    QString s;
    switch(h.value("ifaceMode").toInt()){
    case IFACECONNTYPE_TCPCLNT  : s = QObject::tr("TCP/IP '%1'").arg(h.value("tcpHost").toString().remove("'")); break;
    case IFACECONNTYPE_M2MCLNT  : s = QObject::tr("M2M '%1'").arg(h.value("m2mProfile").toString().remove("'")); break;
    case IFACECONNTYPE_UART     : s = QObject::tr("Serial Port '%1'").arg(h.value(h.value("uartManual").toBool() ? "lastUart" : "defUart").toString() ); if(!h.value("uartManual").toBool()){ s.prepend("<b>"); s.append("</b>");} break;
    }
    return s;
}

QString PrettyValues::normalizeStr(const qreal &value, const int &decimalPosition, const bool &useDecimalPoint)
{
    const QString str = (decimalPosition >= 0) ?
                QString::number(value, 'f', decimalPosition) :
                QString::number(value);


    return checkDecimalSeparator(str, useDecimalPoint);
}

QString PrettyValues::checkDecimalSeparator(const QString &valuestr, const bool &useDecimalPoint)
{
    QString str = valuestr;
    if(useDecimalPoint){
        if(str.contains(","))
            str = str.replace(",", ".");
    }else{
        if(str.contains("."))
            str = str.replace(".", ",");
    }
    return str;
}

QString PrettyValues::prettyLongTextView(QString s)
{
    //former prettyTxtView
    s = s.remove(" ");
    QString r = s.right(4);
    s.chop(3);

    while(!s.isEmpty()){
        r.prepend(s.right(4) + " ");
        s.chop(4);
    }
    return r;
}


//--------------------------------------------------------------
