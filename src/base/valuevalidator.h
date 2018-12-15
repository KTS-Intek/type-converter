#ifndef VALUEVALIDATOR_H
#define VALUEVALIDATOR_H

#include <QStringList>
#include <QDateTime>

class ValueValidator
{

public:

    static quint32 getCorrectValue(const quint32 &in, const quint32 &maxValue);


    static QString validFullTableName(const QString &tableName, const quint8 &code);

    static QStringList validFullTableNames(const QStringList &tableNames, const quint8 &code);


    static QString validFullTableNameMeterLogs(const QDateTime &dt, const quint8 &pollCode);

    static QString validTableCode(const quint8 &code);



};

#endif // VALUEVALIDATOR_H
