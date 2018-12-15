#ifndef CONVERTATYPE_H
#define CONVERTATYPE_H

#include <QVariantHash>
#include <QVariantMap>
#include <QDateTime>

class ConvertAtype
{

public:
    static QVariantHash intHash2varhash(const QHash<quint8, qint64> &hash);

    static QVariantHash intMap2varhash(const QMap<quint8, qint64> &map);


    static QHash<quint8, qint64> strVarHash2inthash(const QVariantHash &hash);

    static QMap<quint8, qint64> strVarHash2intmap(const QVariantHash &hash);


    static QVariantHash dateHash2varhash(const QHash<quint8,QDateTime> &hash);

    static QVariantHash dateMap2varhash(const QMap<quint8,QDateTime> &map);


    static QHash<quint8,QDateTime> strVarHash2datehash(const QVariantHash &hash);

    static QMap<quint8,QDateTime> strVarHash2datemap(const QVariantHash &hash);



    static QHash<QString,QString> varHash2strHash(const QVariantHash &h);

    static QHash<QString, QByteArray> varHash2arrHash(const QVariantHash &h);

    static QVariantHash strHash2varHash(const QHash<QString,QString> &h);

    static QVariantHash arrHash2varHash(const QHash<QString,QByteArray> &h);






};

#endif // CONVERTATYPE_H
