#include "prettyvalues.h"
#include "definedpollcodes.h"
#include <QDate>
#include <QTime>
#include "matildalimits.h"

//------------------------------------------------------------------------------------

QString PrettyValues::getBuildDateStr()
{
    return QString::fromLocal8Bit(BUILDDATE) + " " + QString::fromLocal8Bit(BUILDTIME);
}

//------------------------------------------------------------------------------------

QDateTime PrettyValues::getBuildDate()
{
    const QDateTime dt = QDateTime::fromString(getBuildDateStr(), "yyyy-MM-dd hh:mm:ss");
    return dt.isValid() ? dt : QDateTime(QDate(2017,1,1), QTime(0,0,0,0));
}

//------------------------------------------------------------------------------------

QString PrettyValues::prettyTimeValue(QString &f, qint64 mynulo)
{

    f = QObject::tr("hh:mm:ss");
    QString s = "";
    if(mynulo >= 86400000){ //1 day
        f.prepend(QObject::tr("d "));
        s = QString::number(mynulo/86400000) + " ";
        mynulo %= 86400000;
    }

    s.append(QString::number(mynulo/3600000).rightJustified(2,'0') + ":");//hh
    if(mynulo >= 3600000)
        mynulo %= 3600000;


    s.append(QString::number(mynulo/60000).rightJustified(2,'0') + ":");//mm
    if(mynulo >= 60000)
        mynulo %= 60000;

    s.append(QString::number(mynulo/1000).rightJustified(2,'0'));//ss
    return s;

}

//------------------------------------------------------------------------------------

QString PrettyValues::tablenameEnd4pollCode(const quint8 &pollCode)
{
    if(pollCode == POLL_CODE_READ_TOTAL || pollCode == POLL_CODE_READ_POWER || pollCode == POLL_CODE_READ_VOLTAGE || pollCode == POLL_CODE_READ_METER_LOGBOOK ||
            pollCode == POLL_CODE_READ_METER_STATE ||
            pollCode == POLL_CODE_WTR_TOTAL || pollCode == POLL_CODE_WTR_PERIOD || pollCode == POLL_CODE_WTR_INSTANT_VLS || pollCode == POLL_CODE_WTR_METER_LOGBOOK ||
            pollCode == POLL_CODE_WTR_METER_STATE)
        return "_00_000";//_ss_zzz

    return "_59_999";
}

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
