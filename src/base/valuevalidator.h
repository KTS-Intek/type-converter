#ifndef VALUEVALIDATOR_H
#define VALUEVALIDATOR_H

#include <QStringList>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantList>
#include <QTime>

class ValueValidator
{

public:

    static quint32 getCorrectValue(const quint32 &in, const quint32 &maxValue);


    static QString validFullTableName(const QString &tableName, const quint8 &code);

    static QStringList validFullTableNames(const QStringList &tableNames, const quint8 &code);


    static QString validFullTableNameMeterLogs(const QDateTime &dt, const quint8 &pollCode);

    static QString validTableCode(const quint8 &code);



    static quint32 validateIntegerRange(const QString &key, const QVariantMap &map, const QVariantMap &defValues, const quint32 &min, const quint32 &max);

    static bool validateBoolValue(const QString &key, const QVariantMap &map, const QVariantMap &defValues);


    static QString validateCoordinates(const QString &instr, bool &ok);


    static int calcTMsecCheck(int tMSec, bool &tMSecCheck);


    static QVariantList getMetersPowerCenters(const QList<QVariantHash> &meters);

    static QTime checkTimeIsGood(const QTime &t, const QTime &deftime, bool &afterCorrection);

    static int getIntValFromList(const QStringList &list, const QString &key, const int &defRetVal);


};

#endif // VALUEVALIDATOR_H
