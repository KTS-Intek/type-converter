#include "convertatype.h"


//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::intHash2varhash(const QHash<quint8, qint64> &hash)
{
    QVariantHash h;
    const QList<quint8> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert(QString::number(lk.at(i)), hash.value(lk.at(i)));
    return h;
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::intMap2varhash(const QMap<quint8, qint64> &map)
{
    QVariantHash h;
    const QList<quint8> lk = map.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert(QString::number(lk.at(i)), map.value(lk.at(i)));
    return h;
}

//-------------------------------------------------------------------------------

QHash<quint8, qint64> ConvertAtype::strVarHash2inthash(const QVariantHash &hash)
{
    QHash<quint8, qint64> h;
    const QList<QString> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert( lk.at(i).toUInt(), hash.value(lk.at(i)).toLongLong() );
    if(h.contains(0))
        h.remove(0);
    return h;
}

//-------------------------------------------------------------------------------

QMap<quint8, qint64> ConvertAtype::strVarHash2intmap(const QVariantHash &hash)
{
    QMap<quint8, qint64> h;
    const QList<QString> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert( lk.at(i).toUInt(), hash.value(lk.at(i)).toLongLong() );
    if(h.contains(0))
        h.remove(0);
    return h;
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::dateHash2varhash(const QHash<quint8, QDateTime> &hash)
{
    QVariantHash h;
    const QList<quint8> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert(QString::number(lk.at(i)), hash.value(lk.at(i)));
    return h;
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::dateMap2varhash(const QMap<quint8, QDateTime> &map)
{
    QVariantHash h;
    const QList<quint8> lk = map.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        h.insert(QString::number(lk.at(i)), map.value(lk.at(i)));
    return h;
}

//-------------------------------------------------------------------------------

QHash<quint8, QDateTime> ConvertAtype::strVarHash2datehash(const QVariantHash &hash)
{
    QHash<quint8, QDateTime> h;
    const QList<QString> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        bool ok;
        const quint8 key = lk.at(i).toUInt(&ok);
        const QDateTime dt = hash.value(lk.at(i)).toDateTime();
        if(ok && dt.isValid())
            h.insert( key, dt );
    }
    if(h.contains(0))
        h.remove(0);
    return h;
}

//-------------------------------------------------------------------------------

QMap<quint8, QDateTime> ConvertAtype::strVarHash2datemap(const QVariantHash &hash)
{
    QMap<quint8, QDateTime> h;
    const QList<QString> lk = hash.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        bool ok;
        const quint8 key = lk.at(i).toUInt(&ok);
        const QDateTime dt = hash.value(lk.at(i)).toDateTime();
        if(ok && dt.isValid())
            h.insert( key, dt );
    }
    if(h.contains(0))
        h.remove(0);
    return h;
}

//-------------------------------------------------------------------------------

QHash<QString, QString> ConvertAtype::varHash2strHash(const QVariantHash &h)
{
    const QList<QString> k = h.keys();
    QHash<QString,QString> s;
    for(int i = 0, iMax = k.size(); i < iMax; i++)
        s.insert(k.at(i), h.value(k.at(i)).toString());
    return s;
}

//-------------------------------------------------------------------------------

QHash<QString, QByteArray> ConvertAtype::varHash2arrHash(const QVariantHash &h)
{
    const QList<QString> k = h.keys();
    QHash<QString,QByteArray> s;
    for(int i = 0, iMax = k.size(); i < iMax; i++)
        s.insert(k.at(i), h.value(k.at(i)).toByteArray());
    return s;
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::strHash2varHash(const QHash<QString, QString> &h)
{
    const QList<QString> k = h.keys();
    QVariantHash s;
    for(int i = 0, iMax = k.size(); i < iMax; i++)
        s.insert(k.at(i), h.value(k.at(i)));
    return s;
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::arrHash2varHash(const QHash<QString, QByteArray> &h)
{
    const QList<QString> k = h.keys();
    QVariantHash s;
    for(int i = 0, iMax = k.size(); i < iMax; i++)
        s.insert(k.at(i), h.value(k.at(i)));
    return s;
}


//-------------------------------------------------------------------------------
