#include "convertatype.h"

#include "matildalimits.h"
#include "valuevalidator.h"
#include "prettyvalues.h"

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
    return dowFromStringList(s.split(",", QString::SkipEmptyParts), afterCorrection);

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
    const QStringList l = line.split(" ", QString::SkipEmptyParts);

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
    //ZigBeeGlobal::listNiFromLine
    QStringList listNI;
    if(!aLine.isEmpty()){

        QStringList listComma ;
        // QStringList listNI;

        listComma = aLine.split(",");

        int niCounter = 0;
        foreach(QString strComma, listComma){

            if(strComma.indexOf('-') >= 0){
                QStringList listDefis = strComma.split("-");

                if(listDefis.size() > 1){
                    bool ok;
                    quint64 poch = listDefis.first().toInt(&ok, 10);

                    if(ok){
                        quint64 endNI=listDefis.last().toInt(&ok, 10);
                        if(ok){
                            if(poch <= endNI){
                                for( ; poch <= endNI; poch++){
                                    listNI.append(QString::number(poch));
                                    niCounter++;
                                }
                            }else{
                                for( ; endNI <= poch; poch--){
                                    listNI.append(QString::number(poch));
                                    niCounter++;
                                }
                            }

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
            if(niCounter > MAX_REQUEST_NI_IN_LINE)
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
    ok = true;
    QList<int> l;
    for(int i = 0, iMax = sl.size(); ok && i < iMax; i++)
        l.append(sl.at(i).toInt(&ok));
    if(!ok && !l.isEmpty())
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

int ConvertAtype::uint8list2int(const QList<quint8> &meterMess, int startIndx, const int &len)
{
    int retVal = 0;
    const int meterMessS = meterMess.size();
    if(meterMessS > startIndx){
        QByteArray arr;
       for(int iMax = len + startIndx ; startIndx < meterMessS && startIndx < iMax; startIndx++)
            arr.append( QByteArray::number(meterMess.at(startIndx), 16).rightJustified(2, '0') );

        retVal = int(arr.toUInt(nullptr, 16));
    }
    return retVal;
}

//-------------------------------------------------------------------------------

QString ConvertAtype::uint8list2line(const QList<quint8> &meterMess, int startIndx, const int &len)
{
    QByteArray retVal;
    const int meterMessS = meterMess.size();
    if(meterMessS > startIndx){
        for(int iMax = len + startIndx ; startIndx < meterMessS && startIndx < iMax; startIndx++)
            retVal.append(meterMess.at(startIndx));
    }
    return QString(retVal);
}

//-------------------------------------------------------------------------------

QString ConvertAtype::uint8list2str(const QList<quint8> &meterMess, int startIndx, const int &len)
{
    QString retVal;
    const int meterMessS = meterMess.size();
    if(meterMessS > startIndx){
        QByteArray arr;
        for(int iMax = len + startIndx ; startIndx < meterMessS && startIndx < iMax; startIndx++)
            arr.append( QByteArray::number(meterMess.at(startIndx), 16).rightJustified(2, '0') );

        retVal = QString::number(arr.toULongLong(nullptr, 16));//8 bytes is the maximum
    }
    return retVal;
}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::uint8list2strH(const QList<quint8> &meterMess, int startIndx, const int &len)
{
    const int meterMessS = meterMess.size();
    if(meterMessS > startIndx){
        QByteArray arr;
        for(int iMax = len + startIndx ; startIndx < meterMessS && startIndx < iMax; startIndx++)
            arr.append( QByteArray::number(meterMess.at(startIndx), 16).rightJustified(2, '0') );

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

QByteArray ConvertAtype::listUint8mid2arr(const QList<quint8> &meterMess, const int &startPos, const int &len)
{
    return QByteArray::number(listUint8mid2arrMess(meterMess, startPos, len).toHex().toULongLong(0, 16)) ;

}

//-------------------------------------------------------------------------------

QByteArray ConvertAtype::listUint8mid2arrMess(const QList<quint8> &meterMess, const int &startPos, const int &len)
{
    QByteArray arr;
    for(int i = startPos, iMax = meterMess.size(), l = 0; i < iMax && l != len; i++, l++)
        arr.append(meterMess.at(i));
    return arr;
}

//-------------------------------------------------------------------------------

qreal ConvertAtype::listUint8mid2real(const QList<quint8> &meterMess, const int &startPos, const int &len, const int &dotPos, const int isUnsigned, bool &ok)
{
    qreal dilnyk = 1.0;
    for(int i = 0; i < dotPos; i++)
        dilnyk *= 10;

    bool ok1, ok2;

//    QByteArray arrh = uint8list2strH(meterMess, startPos, len);


    qint64 valInteger = listUint8mid2arr(meterMess, startPos, len).toLongLong(&ok1);
    quint32 valUnsignedInteger = listUint8mid2arr(meterMess, startPos, len).toUInt(&ok2);

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
//    (qreal)( (isUnsigned != 0) ? valUnsignedInteger : valInteger) / dilnyk;//  (listUint8mid2arr(meterMess, startPos, len).toDouble(&ok) / dilnyk);
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
