#ifndef PRETTYVALUES_H
#define PRETTYVALUES_H

#include <QObject>
#include <QString>

class PrettyValues
{

public:

    static QString prettyTimeValue(QString &f, qint64 mynulo);


    static QString tablenameEnd4pollCode(const quint8 &pollCode);


    static QDateTime tableName2DateTime(const QString &tableName, const qint32 addDays = 0, const bool useLocal = false);


    static QString getTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode);

    static QString getFullTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode);

    static QDateTime getDateTime4poll(const QDateTime &dtPoll, const quint8 &pollCode);

};

#endif // PRETTYVALUES_H
