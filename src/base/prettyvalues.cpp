#include "prettyvalues.h"
#include "definedpollcodes.h"
#include <QDate>
#include <QTime>

//------------------------------------------------------------------------------------

QString PrettyValues::prettyTimeValue(QString &f, qint64 mynulo)
{

    f = "hh:mm:ss";
    QString s = "";
    if(mynulo >= 86400000){ //1 day
        f.prepend("d ");
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
    default: tableName.clear(); break;
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

//------------------------------------------------------------------------------------
