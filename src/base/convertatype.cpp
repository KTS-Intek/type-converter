#include "convertatype.h"

#include <QJsonObject>
#include <QJsonDocument>

#include "matildalimits.h"
#include "valuevalidator.h"
#include "prettyvalues.h"

#include <QtMath>
#include <QDataStream>

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

QList<quint8> ConvertAtype::convert2uint8(const QStringList &l)
{
    QList<quint8> r;
    for(int i = 0, imax = l.size(); i < imax; i++){
        bool ok;
        const quint8 v = l.at(i).toUInt(&ok);
        if(ok)
            r.append(v);
    }
    return r;
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::convertFromUint8(const QList<quint8> &l)
{
    QStringList r;
    for(int i = 0, imax = l.size(); i < imax; i++)
        r.append(QString::number(l.at(i)));
    return r;
}

//-------------------------------------------------------------------------------

QList<QVariantHash> ConvertAtype::fromVarList(const QVariantList &indata)
{
    QList<QVariantHash> l;
    for(int i = 0, imax = indata.size(); i < imax; i++)
        l.append(indata.at(i).toHash());
    return l;
}

//-------------------------------------------------------------------------------

QVariantList ConvertAtype::fromListHash(const QList<QVariantHash> &indata)
{
    QVariantList l;
    for(int i = 0, imax = indata.size(); i < imax; i++)
        l.append(indata.at(i));
    return l;
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::dowFromString(const QString &s, bool &afterCorrection)
{
    return dowFromStringList(s.split(",",
                                 #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                     Qt::SkipEmptyParts
                                 #else
                                     QString::SkipEmptyParts
                                 #endif
                                     ), afterCorrection);

}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::dowFromStringList(const QStringList &l, bool &afterCorrection)
{
    if(!l.isEmpty()){
        bool ok = true;
        int lastval = 1;
        for(int i = 0, imax = l.size(); i < imax && ok && lastval > 0 && lastval < 8; i++)
            lastval = l.at(i).toInt(&ok);

        if(!ok || lastval < 1 || lastval > 7){
            afterCorrection = true;
            return QString("1,2,3,4,5,6,7").split(",");
        }
    }
    if(!l.isEmpty() )
        return l;

    afterCorrection = true;
    return QString("1,2,3,4,5,6,7").split(",");
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::domFromStringList(const QStringList &l, bool &afterCorrection)
{
    if(!l.isEmpty()){
        bool ok = true;
        int lastval = 1;
        for(int i = 0, imax = l.size(); i < imax && ok && lastval > 0 && lastval < 8; i++)
            lastval = l.at(i).toInt(&ok);

        if(!ok || lastval < 1 || lastval > 31){
            afterCorrection = true;
            return QStringList();//all days
        }
    }

    return l;
}

//-------------------------------------------------------------------------------

QTime ConvertAtype::timeFromString(const QString &s, const QTime &deftime, bool &afterCorrection)
{
    return ValueValidator::checkTimeIsGood(QTime::fromString(s + ":" + deftime.toString("ss.zzz"), "hh:mm:ss.zzz"), deftime, afterCorrection);

}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::line2hash(const QString &line, const QStringList &lk)
{
    QVariantHash h;
    const QStringList l = line.split(" ",
                                 #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                     Qt::SkipEmptyParts
                                 #else
                                     QString::SkipEmptyParts
                                 #endif
                                     );

    const int iMax = lk.size();
    const int iMax2 = l.size();

    for(int i = 0; i < iMax && i < iMax2; i++)
        h.insert(lk.at(i), l.at(i));
    return h;
}

//-------------------------------------------------------------------------------

QString ConvertAtype::hash2stringLine(const QVariantHash &h, const QStringList &lk)
{
    return hash2stringLine(h, lk, " ");
}

//-------------------------------------------------------------------------------

QString ConvertAtype::hash2stringLine(const QVariantHash &h, const QStringList &lk, const QString &separ)
{
    QStringList l;
    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        const QString s = h.value(lk.at(i)).toString();
        if(s.isEmpty())
            return "";
        l.append(s);
    }
    return l.join(separ);
}

//-------------------------------------------------------------------------------

QString ConvertAtype::hashReal2stringLine(const QVariantHash &h, const QStringList &lk)
{
    return hashReal2stringLine(h, lk, 3);
}

//-------------------------------------------------------------------------------

QString ConvertAtype::hashReal2stringLine(const QVariantHash &h, const QStringList &lk, const int &prec)
{
    return hashReal2stringLine(h, lk, prec, " ");
}

//-------------------------------------------------------------------------------

QString ConvertAtype::hashReal2stringLine(const QVariantHash &h, const QStringList &lk, const int &prec, const QString &separ)
{
    QStringList l;

    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        const QString s = PrettyValues::prettyNumber(h.value(lk.at(i)).toReal(), prec);
        if(s.isEmpty())
            return "";
        l.append(s);
    }
    return l.join(separ);
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::listNiFromLine(const QString &aLine)
{
    return listNiFromLine(aLine, false);
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::listNiFromLine(const QString &aLine, const bool &ignoreLimit)
{
    return listNiFromLine(aLine, ",", ignoreLimit);
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::listNiFromLine(const QString &aLine, const QString &splitSymbol, const bool &ignoreLimit)
{
    //the default split symbol was ','
    //ZigBeeGlobal::listNiFromLine
    QStringList listNI;
    if(!aLine.isEmpty()){

        const QStringList listComma = aLine.split(splitSymbol);

        int niCounter = 0;
        const int niLimit = ignoreLimit ? MAX_METER_COUNT : MAX_REQUEST_NI_IN_LINE;
        for(int iii = 0, iiiMax = listComma.size(); iii < iiiMax; iii++){//        foreach(QString strComma, listComma){
            const QString strComma = listComma.at(iii);

            if(strComma.indexOf('-') >= 0){
                const QStringList listDefis = strComma.split("-");

                if(listDefis.size() > 1){
                    bool ok;
                    quint64 poch = listDefis.first().toInt(&ok, 10);

                    if(ok){
                        const quint64 endNI=listDefis.last().toInt(&ok, 10);
                        if(ok){
                            if(poch <= endNI){
                                for( ; poch <= endNI && niCounter < niLimit; poch++){
                                    listNI.append(QString::number(poch));
                                    niCounter++;
                                }
                            }else{
                                for( ; endNI <= poch && niCounter < niLimit; poch--){
                                    listNI.append(QString::number(poch));
                                    niCounter++;
                                }
                            }

                            if(niCounter >= niLimit)
                                break;

                        }else{
                            listNI.append(listDefis.first());
                            listNI.append(listDefis.last());
                            niCounter++;
                            niCounter++;
                        }
                    }else{
                        listNI.append(listDefis.first());
                        niCounter++;
                    }


                }else{
                    listNI.append(strComma);
                    niCounter++;
                }

            }else{
                listNI.append(strComma);
                niCounter++;
            }

            if(niCounter >= niLimit)
                break;

        }
        listNI.removeDuplicates();



        for(int i = 0, iMax = listNI.size(); i < iMax; i++){
            if(listNI.at(i).isEmpty()){
                listNI.removeAt(i);
                i--;
                iMax--;
            }
        }

        //            listNI = listNI.mid(0,300);


    }
    return listNI;
}

//-------------------------------------------------------------------------------

QList<int> ConvertAtype::strList2intList(const QStringList &sl){
    bool ok;
    return strList2intList(sl, ok);
}

//-------------------------------------------------------------------------------

QList<int> ConvertAtype::strList2intList(const QStringList &sl, bool &ok){

    return strList2intListExt(sl, false, ok);
}

//-------------------------------------------------------------------------------

QList<int> ConvertAtype::strList2intListExt(const QStringList &sl, const bool &ignoreerrors, bool &ok)
{

    ok = true;
    QList<int> l;
    for(int i = 0, iMax = sl.size(); ok && i < iMax; i++)
        l.append(sl.at(i).toInt(&ok));
    if(!ignoreerrors && !ok && !l.isEmpty())
        l.removeLast();
    return l;
}

//-------------------------------------------------------------------------------

QList<quint32> ConvertAtype::strList2uint32list(const QStringList &sl, bool &ok, const int &base){
    ok = true;
    QList<quint32> l;
    for(int i = 0, iMax = sl.size(); ok && i < iMax; i++)
        l.append(sl.at(i).toUInt(&ok, base));
    if(!ok && !l.isEmpty())
        l.removeLast();
    return l;
}

//-------------------------------------------------------------------------------

QList<quint8> ConvertAtype::strList2uint8list(const QStringList &sl, bool &ok){
    ok = true;
    QList<quint8> l;
    for(int i = 0, iMax = sl.size(); ok && i < iMax; i++)
        l.append(sl.at(i).toUInt(&ok));
    if(!ok && !l.isEmpty())
        l.removeLast();
    return l;
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::varList2strList(const QVariantList &list){
    QStringList l;
    for(int i = 0, iMax = list.size(); i < iMax; i++)
        l.append(list.at(i).toString());
    return l;
}

//-------------------------------------------------------------------------------

QVariantList ConvertAtype::strList2VarList(const QStringList &list){
    QVariantList l;
    for(int i = 0, iMax = list.size(); i < iMax; i++)
        l.append(list.at(i));
    return l;
}

//-------------------------------------------------------------------------------

QVariant ConvertAtype::strList2Var(const QStringList &list){
    QVariantList l;
    for(int i = 0, iMax = list.size(); i < iMax; i++)
        l.append(list.at(i));
    return QVariant(l);
}

QStringList ConvertAtype::intList2strList(const QList<int> &l  ){
    QStringList sl;
    for(int i = 0, iMax = l.size(); i < iMax; i++)
        sl.append(QString::number(l.at(i)));
    return sl;
}

//-------------------------------------------------------------------------------

QDateTime ConvertAtype::dateTimeFromStr(const QString &str){
    //ISO8601 strings ("YYYY-MM-DD HH:MM:SS").  "2018-03-05 10:17:00\"
        return QDateTime( QDate::fromString(str.left(10), "yyyy-MM-dd"), QTime::fromString(str.right(8), "hh:mm:ss"), Qt::UTC );
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::varMap2varHash(const QVariantMap &map){
    return  varMap2varHash(map, false);
}

//-------------------------------------------------------------------------------

QVariantHash ConvertAtype::varMap2varHash(const QVariantMap &map, const bool &isJsonMode){
    QVariantHash h;
    const QList<QString> lk = map.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++){

        if(isJsonMode && map.value(lk.at(i)).type() == QVariant::List && !map.value(lk.at(i)).toStringList().isEmpty()){
            h.insert(lk.at(i), map.value(lk.at(i)).toStringList());
            continue;

        }else{
            if(map.value(lk.at(i)).type() == QVariant::Map){
                h.insert(lk.at(i), varMap2varHash(map.value(lk.at(i)).toMap(), isJsonMode));// Hash());
                continue;
            }
        }

        h.insert(lk.at(i), map.value(lk.at(i)));
    }
    return h;
}

//-------------------------------------------------------------------------------

QVariantMap ConvertAtype::varHash2varMap(const QVariantHash &h){


    QVariantMap map;
    const QList<QString> lk = h.keys();
    for(int i = 0, iMax = lk.size(); i < iMax; i++){


            if(h.value(lk.at(i)).type() == QVariant::Hash){
                map.insert(lk.at(i), varHash2varMap(h.value(lk.at(i)).toHash()));// Hash());
                continue;
            }


        map.insert(lk.at(i), h.value(lk.at(i)));
    }
    return map;


}

//-------------------------------------------------------------------------------

QBitArray ConvertAtype::uint8ToBitArray(const quint8 &value)
{
    QByteArray byteArr;
    byteArr.append(value);
    QBitArray bitArr(8);

    for(int i = 0, iMax = 1; i < iMax; ++i){
        for(int b = 0; b < 8; ++b)
            bitArr.setBit(i * 8 + b, byteArr.at(i) & (1 << b));
    }

    return bitArr;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::bitArrToByteArr(const QBitArray &bitArr, const bool &toHex)
{
    QByteArray byteArr(bitArr.count() / 8, 0x0);
    int rightJustif = byteArr.size() * 2;

    for(int b = 0, bMax = bitArr.count(); b < bMax; b++)
        byteArr[(bMax - b - 1)/8] = (byteArr.at((bMax - b - 1)/8) | ((bitArr[b] ? 1 : 0) << (b%8)));

    if(toHex)
        return byteArr.toHex().rightJustified(rightJustif, '0');

    return byteArr;
}

//-------------------------------------------------------------------------------

quint8 ConvertAtype::bitArrToUint8(const QBitArray &bitArr)
{
    return quint8(bitArrToByteArr(bitArr, false).at(0));
}

//-------------------------------------------------------------------------------

QBitArray ConvertAtype::byteArrayToBitArray(const QByteArray &byteArr)
{
    const int iMax = byteArr.size();
    QBitArray bitArr(8 * iMax);

    for(int i = 0; i < iMax; ++i){
        for(int b = 0; b < 8; ++b)
            bitArr.setBit(i * 8 + b, byteArr.at(iMax - i - 1) & (1 << b));
    }
    return bitArr;
}

//-------------------------------------------------------------------------------

QBitArray ConvertAtype::int32ToBitArray(const qint32 &value)
{
    return byteArrayToBitArray(QByteArray::fromHex(QByteArray::number(value, 16)));

}

//-------------------------------------------------------------------------------

QDateTime ConvertAtype::tableName2DateTimeUTC(const QString &tableName, const qint32 addDays)
{
    if(tableName.mid(4,1) != "_")
        return QDateTime( QDate::fromString(tableName.mid(4, 10), "yyyy_MM_dd"), QTime::fromString(tableName.right(5), "hh_mm"), Qt::UTC ).addDays(addDays);
    else
        return QDateTime( QDate::fromString(tableName.left(10), "yyyy_MM_dd"), QTime::fromString(tableName.right(5), "hh_mm"), Qt::UTC ).addDays(addDays);
}

//-------------------------------------------------------------------------------

QList<quint8> ConvertAtype::strList2uint8ListOmmit(const QStringList &l, const bool ommitBadData)
{
    QList<quint8> list;
    for(int i = 0, iMax = l.size(); i < iMax; i++){
        bool ok;
        const quint8 v = quint8(l.at(i).toUInt(&ok));
        if(ommitBadData && !ok)
            continue;
        list.append(v);
    }
    return list;
}

//-------------------------------------------------------------------------------

int ConvertAtype::uint8list2int(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    int retVal = 0;
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        QByteArray arr;
       for(int iMax = len + startIndx ; startIndx < meterMessageListS && startIndx < iMax; startIndx++)
            arr.append( QByteArray::number(meterMessageList.at(startIndx), 16).rightJustified(2, '0') );

        retVal = int(arr.toUInt(nullptr, 16));
    }
    return retVal;
}

//-------------------------------------------------------------------------------

quint32 ConvertAtype::uint8list2uint32littleEndian(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    quint32 retVal = 0;
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        QByteArray arr;
       for(int iMax = len + startIndx ; startIndx < meterMessageListS && startIndx < iMax; startIndx++)
            arr.prepend( QByteArray::number(meterMessageList.at(startIndx), 16).rightJustified(2, '0') );

        retVal = int(arr.toUInt(nullptr, 16));
    }
    return retVal;
}

//-------------------------------------------------------------------------------

QString ConvertAtype::uint8list2line(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    QByteArray retVal;
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        for(int iMax = len + startIndx ; startIndx < meterMessageListS && startIndx < iMax; startIndx++)
            retVal.append(meterMessageList.at(startIndx));
    }
    return QString(retVal);
}

//-------------------------------------------------------------------------------

QString ConvertAtype::uint8list2str(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    QString retVal;
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        QByteArray arr;
        for(int iMax = len + startIndx , bytes = 0; startIndx < meterMessageListS && startIndx < iMax && bytes < 8; startIndx++, bytes++)
            arr.append( QByteArray::number(meterMessageList.at(startIndx), 16).rightJustified(2, '0') );

        retVal = QString::number(arr.toULongLong(nullptr, 16));//8 bytes is the maximum
    }
    return retVal;
}

QString ConvertAtype::uint8list2strViceVersa(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    QString retVal;
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        QByteArray arr;
        for(int iMax = len + startIndx , bytes = 0; startIndx < meterMessageListS && startIndx < iMax && bytes < 8; startIndx++, bytes++)
            arr.prepend(QByteArray::number(meterMessageList.at(startIndx), 16).rightJustified(2, '0') );

        retVal = QString::number(arr.toULongLong(nullptr, 16));//8 bytes is the maximum
    }
    return retVal;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::uint8list2strH(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    const int meterMessageListS = meterMessageList.size();
    if(meterMessageListS > startIndx){
        QByteArray arr;
        for(int iMax = len + startIndx ; startIndx < meterMessageListS && startIndx < iMax; startIndx++)
            arr.append( QByteArray::number(meterMessageList.at(startIndx), 16).rightJustified(2, '0') );

        return arr;
    }
    return QByteArray();
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::convertData7ToData8(const QByteArray &readArr)
{
    const int iMax = readArr.size();
    QByteArray arr(iMax, 0x0);

    for(int i = 0; i < iMax; i++){
        QBitArray bitArr(8);
        for(int b = 0; b < 8; ++b)
            bitArr.setBit(b, readArr.at(i) & (1 << b));

        bitArr.setBit( 7, false);

        for(int b = 0; b < 8; b++){
            arr[i] = arr.at(i) | ((bitArr.at(b) ? 1 : 0) << (b%8));
        }

    }
    return arr;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::convertData8ToData7(const QByteArray &writeArr)
{
    const int iMax = writeArr.size();
    QByteArray arr(iMax, 0x0);

    for(int i = 0; i < iMax; i++){
        QBitArray bitArr(8);
        int counter = 0;
        for(int b = 0; b < 8; ++b){
            bitArr.setBit(b, writeArr.at(i) & (1 << b));
            if(bitArr.at(b) && b < 7)
                counter++;
        }

        bool falseVal = true;
        if(counter%2 == 0)
            falseVal = false;

        bitArr.setBit( 7, falseVal);

        for(int b = 0; b < 8; b++){
          arr[i] = arr.at(i) | ((bitArr.at(b) ? 1 : 0) << (b%8));
        }
    }
    return arr;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::listUint8mid2arr(const QList<quint8> &meterMessageList, const int &startPos, const int &len)
{
    return QByteArray::number(listUint8mid2arrMessage(meterMessageList, startPos, len).toHex().toULongLong(0, 16)) ;

}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::listUint8mid2arrMessage(const QList<quint8> &meterMessageList, const int &startPos, const int &len)
{
    QByteArray arr;
    for(int i = startPos, iMax = meterMessageList.size(), l = 0; i < iMax && l != len; i++, l++)
        arr.append(meterMessageList.at(i));
    return arr;
}

//-------------------------------------------------------------------------------

qreal ConvertAtype::listUint8mid2real(const QList<quint8> &meterMessageList, const int &startPos, const int &len, const int &dotPos, const int isUnsigned, bool &ok)
{
    qreal dilnyk = 1.0;
    for(int i = 0; i < dotPos; i++)
        dilnyk *= 10;

    bool ok1, ok2;

//    QByteArray arrh = uint8list2strH(meterMessageList, startPos, len);


    qint64 valInteger = listUint8mid2arr(meterMessageList, startPos, len).toLongLong(&ok1);
    quint32 valUnsignedInteger = listUint8mid2arr(meterMessageList, startPos, len).toUInt(&ok2);

    if(valInteger > 2147483647){
//        qint64 v = 0xFFFFFFFF;
        valInteger -= (qint64)0xFFFFFFFF;
        valInteger--;
    }

    qreal val = 0;//
    if(isUnsigned){
        val = (qreal)valUnsignedInteger;
    }else{
        val = (qreal)valInteger;
    }
    val /= dilnyk;
//    (qreal)( (isUnsigned != 0) ? valUnsignedInteger : valInteger) / dilnyk;//  (listUint8mid2arr(meterMessageList, startPos, len).toDouble(&ok) / dilnyk);
    ok = isUnsigned ? ok2 : ok1;
    return val;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::intVal2arrH(const int &val, const int &rightJustif)
{
    return QByteArray::number(val, 16).rightJustified(rightJustif, '0');

}

//-------------------------------------------------------------------------------

QString ConvertAtype::intVal2strH(const int &val, const int &rightJustif)
{
    return QString::number(val, 16).rightJustified(rightJustif, '0');

}

//-------------------------------------------------------------------------------

float ConvertAtype::hexstr2float(const QByteArray &arrh, bool &ok)
{
    union{
        quint32 i;
        float f;
    } value;
    value.i = arrh.toUInt(&ok, 16);// std::stoll(arrh.toStdString(), nullptr, 16);
    return value.f;
}

//-------------------------------------------------------------------------------

double ConvertAtype::hexstr2double(const QByteArray &arrh, bool &ok)
{
    union{
        quint64 i;
        double d;
    } value;
    value.i = arrh.toULongLong(&ok, 16);// std::stoll(arrh.toStdString(), nullptr, 16);
    return value.d;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::hexArrFromNumber(const int &inVal, const int &byteCount, const int base)
{
    return QByteArray::number(inVal,base).rightJustified(byteCount * 2, '0');

}

//-------------------------------------------------------------------------------

QString ConvertAtype::varHash2str(const QVariantHash &h, const bool ignoreEmpty)
{
    QList<QString> lk = h.keys();
    std::sort(lk.begin(), lk.end());
    QStringList l;
    for(int i = 0, iMax = lk.size(); i < iMax; i++){
        if(h.value(lk.at(i)).toString().isEmpty()){
            if(ignoreEmpty || h.value(lk.at(i)).isNull())
                continue;


            QByteArray arr;
            if(true){
                QDataStream stream(&arr, QIODevice::WriteOnly);
                stream << h.value(lk.at(i));
            }
            l.append(QString("%1=%2,len=%3").arg(lk.at(i)).arg(QString(h.value(lk.at(i)).typeName())).arg(arr.length()));

            continue;


        }

        l.append(QString("%1=%2").arg(lk.at(i)).arg(h.value(lk.at(i)).toString()));
    }
    return l.join("\n");
}

//-------------------------------------------------------------------------------

QVariantMap ConvertAtype::getPower2groups(const QMap<int, int> &groupId2power)
{    
    return getPower2groupsExt(groupId2power, true);
}
//-------------------------------------------------------------------------------
QVariantMap ConvertAtype::getPower2groupsExt(const QMap<int, int> &groupId2power, const bool &isPowerInPercents)
{
    const QList<int> lk = groupId2power.keys();
    QVariantMap map;

    const int multiplier = isPowerInPercents ? 254 : 100;

    for(int i = 0, imax = lk.size(); i < imax; i++){

        const QString grp = QString::number(lk.at(i));
        const QString pwr = QString::number( groupId2power.value(lk.at(i)) * multiplier / 100) ;//convert percents to 0-0xFE

        QStringList l = map.value(pwr).toStringList();
        l.append(grp);
        map.insert(pwr, l);
    }
    return map;
}

//-------------------------------------------------------------------------------

QString ConvertAtype::map2jsonLine(const QVariantMap &map)
{
    return QJsonDocument(QJsonObject::fromVariantMap(map)).toJson(QJsonDocument::Compact);
}

//-------------------------------------------------------------------------------

int ConvertAtype::percent2lampPowerValue(const int &percent)
{
    const int lampPower = percent*254/100;
    if(percent != lampPowerValue2percent(lampPower)){

        for(int i = 1, j = percent; i < 100 && j < 101; i++, j++){
             if(percent == lampPowerValue2percent(lampPower + i))
                 return (lampPower + i);
        }
    }
    return lampPower;
}

//-------------------------------------------------------------------------------

int ConvertAtype::lampPowerValue2percent(const int &lampPowerValue)
{
    return qRound((qreal(lampPowerValue) * 100.0)/254.0);
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::qslFromHash(const QHash<QString, QString> &h, const QString &separ, QList<QString> lk)
{
    if(lk.isEmpty()){
        lk = h.keys();
        std::sort(lk.begin(), lk.end());
    }

    QStringList l;
    for(int i = 0, iMax = lk.size(); i < iMax; i++)
        l.append(lk.at(i) + separ + h.value(lk.at(i)));
    return l;
}

//-------------------------------------------------------------------------------

QHash<QString, QString> ConvertAtype::machine2human(const QStringList &machineList, const QStringList &human)
{
    QHash<QString, QString> h;
    for(int i = 0, iMax = machineList.size(), iMax2 = human.size(); i < iMax && i < iMax2; i++)
        h.insert(machineList.at(i), human.at(i));
    return h;
}
//-------------------------------------------------------------------------------


QHash<QString, QString> ConvertAtype::strHashFromQslSmpl(const QStringList &l, const QString &separ)
{
    QList<QString> lk;
    return strHashFromQsl(l, separ, lk, 0, 1, true);
}

//-------------------------------------------------------------------------------


QHash<QString, QString> ConvertAtype::strHashFromQsl(const QStringList &l, const QString &separ, QList<QString> &lk, const int key, const int val, const bool oneMode)
{
    //key - key pos
    //val - value pos in the list

    QHash<QString,QString> h;
    lk.clear();
    for(int i = 0, iMax = l.size(); i < iMax; i++){
        const QStringList ll = l.at(i).split(separ);
        if(ll.isEmpty())
            continue;
        const int s = ll.size();
        if(s <= key || s <= val)
            continue;

        h.insert(ll.at(key), oneMode ? ll.at(val) : ll.mid(val).join(separ));

    }
    return h;
}

//-------------------------------------------------------------------------------

QPointF ConvertAtype::coordinateFromStr(const QString &s, bool &ok)
{
    return coordinateFromStrExt(s, QPointF(46.6860,32.5060), ok );//chornobajivka 0,0);  46.686000,32.506000

}

//-------------------------------------------------------------------------------

QPointF ConvertAtype::coordinateFromStrExt(const QString &s, const QPointF &defPoint, bool &ok)
{
    QStringList l = s.split(",",
                        #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                            Qt::SkipEmptyParts
                        #else
                            QString::SkipEmptyParts
                        #endif
                            );
    qreal defLong, defLatitude;
    bool okX = false, okY = false;

    if(l.size() == 2){
        defLong = QString(l.first()).toDouble(&okX);
        defLatitude = QString(l.last()).toDouble(&okY);
    }

    if(okX && okY){
        ok = true;
        return QPointF(defLong, defLatitude);
    }
    ok = false;
    return defPoint;
}

QString ConvertAtype::coordinateToStrExt(const QPointF &coordinate, const QPointF &defPoint)
{
    const QString s = coordinateToStr(coordinate);
    if(s.isEmpty())
        return coordinateToStr(defPoint);
    return s;
}

//-------------------------------------------------------------------------------

QString ConvertAtype::coordinateToStr(const QPointF &coordinate)
{
    if(coordinate.isNull())
        return QString();
    //MyGeoConvertHelper::getStrCoordinates(const QGeoCoordinate &c)
    //    return QString("%1,%2").arg(QString::number(c.latitude(),'f', COORDINATEPRECISION)).arg(QString::number(c.longitude(),'f', COORDINATEPRECISION));

    return QString("%1,%2")
            .arg(QString::number(coordinate.x(), 'f', 6))
            .arg(QString::number(coordinate.y(), 'f', 6));
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::replaceKeyInList(const QStringList &listIp, const QString &key, const QString &addIp)
{
    if(addIp.isEmpty() || key.isEmpty())
        return listIp;

    QString s = listIp.join("\n");

    if(listIp.contains(key)){
        s = s.replace(key, addIp);
    }else{
        s.prepend(addIp + "\n");
    }
    return s.split("\n",
               #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                   Qt::SkipEmptyParts
               #else
                   QString::SkipEmptyParts
               #endif
                   );
}

//-------------------------------------------------------------------------------

QStringList ConvertAtype::replaceKeyInList(const QStringList &listIpSource, const QString &key, const QStringList &addList)
{
    return replaceKeyInList(listIpSource, key, addList.join("\n"));

}

//-------------------------------------------------------------------------------

int ConvertAtype::daliPwr2linearPercents(const int &daliPwrPercents)
{
    if(daliPwrPercents < 1)
        return 0;

    const qreal refpower = 100.0;

    for(int i = 1; i < 101; i++){
        const int linearPwrPercents = i;
        const int calcdalipwr = linearPwr2daliPwrInt(percent2lampPowerValue(linearPwrPercents), refpower);
        if(calcdalipwr >= daliPwrPercents)
            return linearPwrPercents;
    }

    return 0;

}

//-------------------------------------------------------------------------------

qreal ConvertAtype::linearPwr2daliPwr(const int &linearPower, const qreal &refpower)
{

    if(linearPower < 1)
        return 0.0;


    const qreal pwrvalue = qreal(linearPower);
//X(n)=((B32-1)/(253/3)) + (254-B32)/150 + POW( ((254-B32)/400);2)
//=POW(10;H50)*78/1000
    const qreal xn = ((pwrvalue - 1.0) / (253.0/3.0)) + (254.0 - pwrvalue)/150.0 + qPow(((254.0 - pwrvalue)/400), 2);
    const qreal powerWt = qPow(10, xn) * refpower * 0.001;


    return powerWt;

}

//-------------------------------------------------------------------------------

int ConvertAtype::linearPwr2daliPwrInt(const int &linearPower, const qreal &refpower)
{
    return qRound(linearPwr2daliPwr(linearPower, refpower));
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::uint8list2array(const QList<quint8> &meterMessageList, int startIndx, const int &len)
{
    const int meterMessageListS = meterMessageList.size();
    QByteArray arr;

    if(meterMessageListS > startIndx){
        for(int iMax = len + startIndx ; startIndx < meterMessageListS && startIndx < iMax; startIndx++)
            arr.append(meterMessageList.at(startIndx));
    }
    return arr;
}

//-------------------------------------------------------------------------------

QList<quint8> ConvertAtype::convertArray2uint8list(const QByteArray &arr)
{
    QList<quint8> l;
    for(int i = 0, imax = arr.length(); i < imax; i++)
        l.append(arr.at(i));
    return l;
}

//-------------------------------------------------------------------------------

QList<quint8> ConvertAtype::convertNumber2uint8list(const quint64 &number, const int &byteslen)
{
    QByteArray arr;
    arr.setNum(number, 16);
    arr = arr.rightJustified(byteslen * 2, '0');

    arr = QByteArray::fromHex(arr);
    return convertArray2uint8list(arr);
}

//-------------------------------------------------------------------------------

QString ConvertAtype::getTextFromHash(const QVariantHash &h)
{
    auto lk = h.keys();
    std::sort(lk.begin(), lk.end());

    QStringList out;

    for(int i = 0, imax = lk.size(); i < imax; i++){
        out.append(QString("%1 : %2").arg(lk.at(i)).arg(getTextByType(h.value(lk.at(i)))));
    }

    return out.join("\n");
}

//-------------------------------------------------------------------------------

QString ConvertAtype::getTextFromMap(const QVariantMap &map)
{
    auto lk = map.keys();
    std::sort(lk.begin(), lk.end());

    QStringList out;

    for(int i = 0, imax = lk.size(); i < imax; i++){
        out.append(QString("%1 : %2").arg(lk.at(i)).arg(getTextByType(map.value(lk.at(i)))));
    }

    return out.join("\n");
}

//-------------------------------------------------------------------------------

QString ConvertAtype::getTextFromList(const QVariantList &l)
{
    QStringList out;

    for(int i = 0, imax = l.size(); i < imax; i++){
        const QString line = getTextByType(l.at(i));
        if(line.isEmpty())
            continue;
        out.append(line);
    }
    return out.join("\n");
}

//-------------------------------------------------------------------------------

QString ConvertAtype::getTextByType(const QVariant &v)
{
    if(v.type() == QVariant::Hash){
        return getTextFromHash(v.toHash());
    }

    if(v.type() == QVariant::List ){
        return getTextFromList(v.toList());

    }

    if(v.type() == QVariant::ByteArray){
        return v.toString();

    }

    if(v.type() == QVariant::Map){
        return getTextFromMap(v.toMap());
    }

    if(v.type() == QVariant::StringList){
        return v.toStringList().join("\n");
    }

    if(v.type() == QVariant::String){
        return v.toString();
    }

    return QString("Unknown data type %1, data %2").arg(int(v.type())).arg(v.toString());
}

//-------------------------------------------------------------------------------
