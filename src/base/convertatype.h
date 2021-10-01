#ifndef CONVERTATYPE_H
#define CONVERTATYPE_H

#include <QVariantHash>
#include <QVariantMap>
#include <QDateTime>
#include <QStringList>
#include <QVariantList>
#include <QTime>
#include <QBitArray>
#include <QByteArray>
#include <QPointF>

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


    static QList<quint8> convert2uint8(const QStringList &l);

    static QStringList convertFromUint8(const QList<quint8> &l);


    static QList<QVariantHash> fromVarList(const QVariantList &indata);

    static QVariantList fromListHash(const QList<QVariantHash> &indata);




    static QStringList dowFromString(const QString &s, bool &afterCorrection);

    static QStringList dowFromStringList(const QStringList &l, bool &afterCorrection);

    static QStringList domFromStringList(const QStringList &l, bool &afterCorrection);


    static QTime timeFromString(const QString &s, const QTime &deftime, bool &afterCorrection);


    //meterstatehelper.h
    static QVariantHash line2hash(const QString &line, const QStringList &lk);

    static QString hash2stringLine(const QVariantHash &h, const QStringList &lk);

    static QString hash2stringLine(const QVariantHash &h, const QStringList &lk, const QString &separ);

    static QString hashReal2stringLine(const QVariantHash &h, const QStringList &lk);
    static QString hashReal2stringLine(const QVariantHash &h, const QStringList &lk, const int &prec);
    static QString hashReal2stringLine(const QVariantHash &h, const QStringList &lk, const int &prec, const QString &separ);

    static QStringList listNiFromLine(const QString &aLine) ;
    static QStringList listNiFromLine(const QString &aLine, const bool &ignoreLimit) ;

    static QStringList listNiFromLine(const QString &aLine, const QString &splitSymbol, const bool &ignoreLimit) ;

    // mtypeconversion.h
    static QList<int> strList2intList(const QStringList &sl);

    static QList<int> strList2intList(const QStringList &sl, bool &ok);
    static QList<int> strList2intListExt(const QStringList &sl, const bool &ignoreerrors, bool &ok);

    static QList<quint32> strList2uint32list(const QStringList &sl, bool &ok, const int &base);

    static QList<quint8> strList2uint8list(const QStringList &sl, bool &ok);

    static QStringList varList2strList(const QVariantList &list);

    static QVariantList strList2VarList(const QStringList &list);

    static QVariant strList2Var(const QStringList &list);

    static QStringList intList2strList(const QList<int> &l  );

    static QDateTime dateTimeFromStr(const QString &str);

    static QVariantHash varMap2varHash(const QVariantMap &map);

    static QVariantHash varMap2varHash(const QVariantMap &map, const bool &isJsonMode);

    static QVariantMap varHash2varMap(const QVariantHash &h);

//meterpluginhelper.h
    static QBitArray uint8ToBitArray(const quint8 &value);

    static QByteArray bitArrToByteArr(const QBitArray &bitArr, const bool &toHex);

    static quint8 bitArrToUint8(const QBitArray &bitArr);

    static  QBitArray byteArrayToBitArray(const QByteArray &byteArr);
    static  QBitArray int32ToBitArray(const qint32 &value);

    static QDateTime tableName2DateTimeUTC(const QString &tableName, const qint32 addDays = 0) ;


    static QList<quint8> strList2uint8ListOmmit(const QStringList &l, const bool ommitBadData = true);

    static int uint8list2int(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static quint32 uint8list2uint32littleEndian(const QList<quint8> &meterMessageList, int startIndx, const int &len);



    static QString uint8list2line(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static QString uint8list2str(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static QString uint8list2strViceVersa(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static QByteArray uint8list2strH(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static QByteArray convertData7ToData8(const QByteArray &readArr);

    static QByteArray convertData8ToData7(const QByteArray &writeArr);

    static QByteArray listUint8mid2arr(const QList<quint8> &meterMessageList, const int &startPos, const int &len);

    static QByteArray listUint8mid2arrMessage(const QList<quint8> &meterMessageList, const int &startPos, const int &len);


    static qreal listUint8mid2real(const QList<quint8> &meterMessageList, const int &startPos, const int &len, const int &dotPos, const int isUnsigned, bool &ok);


    static QByteArray intVal2arrH(const int &val, const int &rightJustif);

    static QString intVal2strH(const int &val, const int &rightJustif);

    static float hexstr2float(const QByteArray &arrh, bool &ok);

    static double hexstr2double(const QByteArray &arrh, bool &ok);

    static QByteArray hexArrFromNumber(const int &inVal, const int &byteCount, const int base = 10);


    //DbgAboutSourceType
    static QString varHash2str(const QVariantHash &h, const bool ignoreEmpty = true);

    static QVariantMap getPower2groups(const QMap<int, int> &groupId2power);
    static QVariantMap getPower2groupsExt(const QMap<int, int> &groupId2power, const bool &isPowerInPercents);

    static QString map2jsonLine(const QVariantMap &map);

    static int percent2lampPowerValue(const int &percent);

    static int lampPowerValue2percent(const int &lampPowerValue);

    //globalhelper
    static QStringList qslFromHash(const QHash<QString,QString> &h, const QString &separ, QList<QString> lk = QList<QString>());

    static QHash<QString,QString> machine2human(const QStringList &machineList, const QStringList &human);


    static QHash<QString,QString> strHashFromQslSmpl(const QStringList &l, const QString &separ);

    static QHash<QString,QString> strHashFromQsl(const QStringList &l, const QString &separ, QList<QString> &lk, const int key = 0, const int val = 1, const bool oneMode = true);

    //fireflyhelper.h
    static QPointF coordinateFromStr(const QString &s, bool &ok);

    static QString coordinateToStr(const QPointF &coordinate);


//stringlisthelper
    static QStringList replaceKeyInList(const QStringList &listIp, const QString &key, const QString &addIp);

    static QStringList replaceKeyInList(const QStringList &listIpSource, const QString &key, const QStringList &addList);

    static int daliPwr2linearPercents(const int &daliPwrPercents);

    static qreal linearPwr2daliPwr(const int &linearPower, const qreal &refpower);

    static int linearPwr2daliPwrInt(const int &linearPower, const qreal &refpower);


    static QByteArray uint8list2array(const QList<quint8> &meterMessageList, int startIndx, const int &len);

    static QList<quint8> convertArray2uint8list(const QByteArray &arr);

    static QList<quint8> convertNumber2uint8list(const quint64 &number, const int &byteslen);


};

#endif // CONVERTATYPE_H
