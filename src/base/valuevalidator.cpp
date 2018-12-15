#include "valuevalidator.h"


quint32 ValueValidator::getCorrectValue(const quint32 &in, const quint32 &maxValue)
{
    if(in < 1)
        return 1;
    if(in > maxValue)
        return (qint32)maxValue;

    return (qint32)in;
}



QString ValueValidator::validFullTableName(const QString &tableName, const quint8 &code)
{
    int aaa = 0;
    if(tableName.left(4).toInt() < 4){
        if(tableName.mid(4,4).toInt() < 4)
            return "";
        aaa = 4;
    }
    return QString("%1_%2").arg(validTableCode(code)).arg(tableName.mid(aaa));
}



QStringList ValueValidator::validFullTableNames(const QStringList &tableNames, const quint8 &code)
{
    QStringList l;
    for(int i = 0, imax = tableNames.size(); i < imax; i++)
        l.append(validFullTableName(tableNames.at(i), code));
    return l;
}



QString ValueValidator::validFullTableNameMeterLogs(const QDateTime &dt, const quint8 &pollCode)
{
    //POLL_CODE_READ_METER_LOGBOOK
        return QString("%1_%2_00_00").arg(validTableCode(pollCode)).arg(QDateTime(dt.toUTC().date(), QTime(0,0,0,0)).toString("yyyy_MM_dd"));

}



QString ValueValidator::validTableCode(const quint8 &code)
{
    QString codeStr = QString::number(code);
    codeStr = codeStr.rightJustified(3, '0');
    return codeStr;
}

quint32 ValueValidator::validateIntegerRange(const QString &key, const QVariantMap &map, const QVariantMap &defValues, const quint32 &min, const quint32 &max)
{
    bool ok;
    const quint32 value = map.value(key).toUInt(&ok);
    if(!ok || !map.contains(key))
        return defValues.value(key).toUInt();

    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}

bool ValueValidator::validateBoolValue(const QString &key, const QVariantMap &map, const QVariantMap &defValues)
{
    const bool value = map.value(key).toBool();
    if(!map.contains(key))
        return defValues.value(key).toBool();

    return value;
}
