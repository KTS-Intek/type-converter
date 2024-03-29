#include "valuevalidator.h"
#include <QUrl>

//--------------------------------------------------------------

quint32 ValueValidator::getCorrectValue(const quint32 &in, const quint32 &maxValue)
{
    if(in < 1)
        return 1;
    if(in > maxValue)
        return maxValue;

    return in;
}

qint32 ValueValidator::getCorrectValueSigned(const qint32 &in, const qint32 &maxValue, const qint32 &minValue)
{
    if(in < minValue)
        return minValue;
    if(in > maxValue)
        return maxValue;
    return in;
}


//--------------------------------------------------------------


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


//--------------------------------------------------------------


QStringList ValueValidator::validFullTableNames(const QStringList &tableNames, const quint8 &code)
{
    QStringList l;
    for(int i = 0, imax = tableNames.size(); i < imax; i++)
        l.append(validFullTableName(tableNames.at(i), code));
    return l;
}


//--------------------------------------------------------------


QString ValueValidator::validFullTableNameMeterLogs(const QDateTime &dt, const quint8 &pollCode)
{
    //POLL_CODE_READ_METER_LOGBOOK
        return QString("%1_%2_00_00").arg(validTableCode(pollCode)).arg(QDateTime(dt.toUTC().date(), QTime(0,0,0,0)).toString("yyyy_MM_dd"));

}



//--------------------------------------------------------------

QString ValueValidator::validTableCode(const quint8 &code)
{
    QString codeStr = QString::number(code);
    codeStr = codeStr.rightJustified(3, '0');
    return codeStr;
}

quint32 ValueValidator::validateIntegerRange(const QString &key, const QVariantMap &map, const quint32 &defValue, const quint32 &min, const quint32 &max)
{
    bool ok;
    const quint32 value = map.value(key).toUInt(&ok);
    if(!ok || !map.contains(key))
        return validateIntegerRange(defValue, min, max);


    return validateIntegerRange(value, min, max);
}

//--------------------------------------------------------------

quint32 ValueValidator::validateIntegerRange(const QString &key, const QVariantMap &map, const QVariantMap &defValues, const quint32 &min, const quint32 &max)
{
    bool ok;
    const quint32 value = map.value(key).toUInt(&ok);
    if(!ok || !map.contains(key))
        return defValues.value(key).toUInt();

    return validateIntegerRange(value, min, max);

}
//--------------------------------------------------------------
quint32 ValueValidator::validateIntegerRange(const quint32 &value, const quint32 &min, const quint32 &max)
{
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}

//--------------------------------------------------------------

bool ValueValidator::validateBoolValue(const QString &key, const QVariantMap &map, const QVariantMap &defValues)
{
    const bool value = map.value(key).toBool();
    if(!map.contains(key))
        return defValues.value(key).toBool();

    return value;
}

//--------------------------------------------------------------

QString ValueValidator::validateCoordinates(const QString &instr, bool &ok)
{
    ok = false;
    QString s = instr.simplified().trimmed();

    if(s.isEmpty()){
        ok = true;
        return s;
    }
    const QStringList l = s.split(",",
                              #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                  Qt::SkipEmptyParts
                              #else
                                  QString::SkipEmptyParts
                              #endif
                                  );
    s.clear();
    if(l.size() == 2){
        bool oklat ,oklon;
        qreal lat = l.first().toFloat(&oklat);
        qreal lon = l.last().toFloat(&oklon);

        if(oklat && oklon && lat <= 90.0 && lat >= (-90.0)){
            quint32 cntr = 0, cntrMax = 0xFFFFFF;
            if(lon > 180.0){
                while(lon > 180.0 && cntr < cntrMax){
                    lon -= 360;
                    cntr++;
                }
            }else if(lon < -180.0){
                while(lon < -180.0 && cntr < cntrMax){
                    lon += 360;
                    cntr++;
                }
            }
            if(cntr < cntrMax){
                s = QString::number(lat, 'f', 6).replace(",", ".") + "," + QString::number(lon, 'f', 6).replace(",", ".");
                ok = true;
            }
        }
    }
    return s;
}

//--------------------------------------------------------------

int ValueValidator::calcTMsecCheck(int tMSec, bool &tMSecCheck)
{
    tMSecCheck = true;
    if(tMSec < 1){
        tMSec = 0xFFFFFFF;//268 435 455 ms   4 473,92425 sec
        tMSecCheck = false;
    }else{
        if(tMSec < 700)
            tMSec = 700;
    }
    return tMSec;
}

//--------------------------------------------------------------

QVariantList ValueValidator::getMetersPowerCenters(const QList<QVariantHash> &meters)
{
    //    const QList<QVariantHash> meters = getRelayVarianList();  getElectricityVarianList
        QVariantList l;
        for(int i = 0, imax = meters.size(); i < imax; i++){
            const QVariantHash h = meters.at(i);
            if(h.value("pwrn").toString() == "+" || h.value("pwrn").toString().startsWith("+ "))
                l.append(h);
        }
        return l;
}
//--------------------------------------------------------------


QTime ValueValidator::checkTimeIsGood(const QTime &t, const QTime &deftime, bool &afterCorrection)
{
    if(t.isValid())
        return t;
    afterCorrection = true;
    return deftime;
}

//--------------------------------------------------------------

int ValueValidator::getIntValFromList(const QStringList &list, const QString &key, const int &defRetVal)
{
   return getIntValFromListExt(list, key, defRetVal, -0xFFFF, 0xFFFF );
}
//--------------------------------------------------------------
int ValueValidator::getIntValFromListExt(const QStringList &list, const QString &key, const int &defRetVal, const int &minval, const int &maxval)
{
    for(int i = 0, iMax = list.size(), len = key.length(); i < iMax; i++){
        if(list.at(i).left(len) == key){
            bool ok;
            const int retVal = list.at(i).mid(len).toInt(&ok);
            if(ok){                
                return getCorrectValueSigned(retVal, maxval, minval);

            }

        }
    }
    return defRetVal;

}
//--------------------------------------------------------------
bool ValueValidator::urlIsValid(const QString &strUrl)
{
    const QUrl url(strUrl, QUrl::StrictMode);
    return (url.isValid() && !strUrl.contains(" ") && !strUrl.contains(">") && !strUrl.contains("{"));
}
//--------------------------------------------------------------
int ValueValidator::getPercents(const int &total, const int &done)
{
    if(total < 1)
        return 100;
    return ((qMin(0, done) * 100) / total);
}

//--------------------------------------------------------------
