#include "prettygsmhl8518values.h"

PrettyGsmHL8518values::PrettyGsmHL8518values(QObject *parent) : QObject(parent)
{
    verboseMode = false;
}

QString PrettyGsmHL8518values::convert2gsmString(const QString &utfstr)
{
    const QByteArray arr = utfstr.toLocal8Bit();
    QString s;
    for(int i = 0, iMax = arr.length(); i < iMax; i++){
        QString a( QString(arr.at(i)).toLatin1() );
        if(a != " ")
            a = a.simplified().trimmed();

        if((qint8)arr.at(i) < 0x20 || (qint8)arr.at(i) >= 0x7f || a.isEmpty() )
            s.append(".");
        else
            s.append(a);
    }
    //    while(ommitRightDot && !s.isEmpty() && s.right(1) == ".")
    //        s.chop(1);
    return s;
}

//------------------------------------------------------------------------------------

QString PrettyGsmHL8518values::getBandName(const quint32 &kbnd)
{
    QString bandName;
    switch(kbnd){
    case GSM_BAND_NOT_AVAILABLE : bandName = "Not available"            ; break;
    case GSM_BAND_GSM_850       : bandName = "GSM 850 MHz"              ; break;
    case GSM_BAND_GSM_900       : bandName = "GSM 900 MHz and E-GSM"    ; break;
    case GSM_BAND_DCS_1800      : bandName = "DCS 1800 MHz"             ; break;
    case GSM_BAND_PCS_1900      : bandName = "PCS 1900 MHz"             ; break;
    case GSM_BAND_UMTS_1        : bandName = "UMTS Band 1 (2100 MHz)"   ; break;
    case GSM_BAND_UMTS_2        : bandName = "UMTS Band 2 (1900 MHz)"   ; break;
    case GSM_BAND_UMTS_5        : bandName = "UMTS Band 5 (850 MHz)"    ; break;
    case GSM_BAND_UMTS_6        : bandName = "UMTS Band 6 (800 MHz)"    ; break;
    case GSM_BAND_UMTS_8        : bandName = "UMTS Band 8 (900 MHz)"    ; break;
    case GSM_BAND_UMTS_9        : bandName = "UMTS Band 9 (800 MHz)"    ; break;


case GSM_BAND_LTE_X    : bandName = "LTE"; break;//      0xFFFE //
case GSM_BAND_CDMA_X   : bandName = "CDMA"; break;//      0xFFFD //

        //    default: bandName = readStr.simplified().trimmed(); break;
    }
    return bandName;
}

QString PrettyGsmHL8518values::getCregState(const int &val)
{
    QString regState;
    switch(val){
    case 0: regState = "Not registered"; break;
    case 1: regState = "Registered, home network"; break;
    case 2: regState = "Not registered, but ME is currently searching a new operator to register to"; break;
    case 3: regState = "Registration denied"; break;
    case 4: regState = "Unknown"; break;
    case 5: regState = "Registered, roaming"; break;
    }
    return regState;
}

QString PrettyGsmHL8518values::getCregName(const int &val)
{
    QString bandName;
    switch(val){
    case 0: bandName = "GSM"; break;
    case 1: bandName = "Compact GSM"; break;
    case 2: bandName = "UTRAN"; break;
    case 3: bandName = "GSM with EGPRS"; break;
    case 4: bandName = "UTRAN with HSDPA"; break;
    case 5: bandName = "UTRAN with HSUPA"; break;
    case 6: bandName = "UTRAN with HSDPA and HSUPA"; break;
    }
    return bandName;
}

//------------------------------------------------------------------------------------

QString PrettyGsmHL8518values::getHumanReadableRssi(const int &csqrssi)
{
    return (csqrssi == 99 || csqrssi == 0) ? "-" : QString("%1 dBm").arg((csqrssi * 2) - 113 );
}

//------------------------------------------------------------------------------------

QString PrettyGsmHL8518values::getHumanReadableBer(const int &csqber)
{
    return (csqber == 99) ? "-" : QString("%1 %").arg( ((csqber * 100) / 7) );
}

QStringList PrettyGsmHL8518values::getPinPossibleAnswers()
{
    return QString("READY;"
                   "SIM PIN;SIM PUK;"
                   "SIM PIN2;SIM PUK2;"
                   "PH-NET PIN;PH-NET PUK;"
                   "PH-NETSUB PIN;PH-NETSUB PUK;"
                   "PH-SP PIN;PH-SP PUK;"
                   "PH-CORP PIN;PH-CORP PUK").split(";");
}

QString PrettyGsmHL8518values::getPIN1stateMessage(const PrettyGsmHL8518values::SIM_STATE &simstate)
{
    QString statestr;
    switch(simstate){
    case SIM_STATE::READY           : statestr = tr("Modem is not pending for any password)")                                           ; break;

    case SIM_STATE::SIM_PIN         : statestr = tr("Modem is waiting for %1 to be given!").arg("SIM PIN")                              ; break;
    case SIM_STATE::SIM_PUK         : statestr = tr("Modem is waiting for %1 to be given!").arg("SIM PUK")                              ; break;

    case SIM_STATE::SIM_PIN2        : statestr = tr("Modem is waiting for %1 to be given!").arg("SIM PIN2")                             ; break;
    case SIM_STATE::SIM_PUK2        : statestr = tr("Modem is waiting for %1 to be given!").arg("SIM PUK2")                             ; break;

    case SIM_STATE::PH_NET_PIN      : statestr = tr("Modem is waiting for the network personalization password to be given!")           ; break;
    case SIM_STATE::PH_NET_PUK      : statestr = tr("Modem is waiting network personalization unblocking password to be given!")        ; break;

    case SIM_STATE::PH_NETSUB_PIN   : statestr = tr("Modem is waiting network subset personalization password to be given!")            ; break;
    case SIM_STATE::PH_NETSUB_PUK   : statestr = tr("Modem is waiting network subset personalization unblocking password to be given!") ; break;

    case SIM_STATE::PH_SP_PIN       : statestr = tr("Modem is waiting service provider personalization password to be given!")          ; break;
    case SIM_STATE::PH_SP_PUK       : statestr = tr("Modem is waiting service provider personalization unblocking password to be given!"); break;

    case SIM_STATE::PH_CORP_PIN     : statestr = tr("Modem is waiting corporate personalization password to be given!")                 ; break;
    case SIM_STATE::PH_CORP_PUK     : statestr = tr("Modem is waiting corporate personalization unblocking password to be given!")      ; break;

    default     : statestr = tr("Modem is in unknown state!"); break;

    }

//    if(verboseMode)
//        qDebug() << "getPIN1stateMessage " << statestr << int(simstate);
    return statestr;
}

//------------------------------------------------------------------------------------

bool PrettyGsmHL8518values::decodeKbnd(const QString &readStr, QString &bandName)
{
    //+KBND: 0010
    bool ok;
    const quint32 kbnd = readStr.mid(7).simplified().trimmed().toUShort(&ok, 16);

    ok = (ok && !readStr.mid(7).simplified().trimmed().isEmpty() && readStr.left(7) == "+KBND: ");

    if(ok){
        bandName = getBandName(kbnd);
        if(bandName.isEmpty())
            bandName = readStr.simplified().trimmed();
    }

    return ok;
}

AT_COPS PrettyGsmHL8518values::decodeCops(const QString &readStr, const bool &ignoreCopsCheck)
{
    //+COPS: 0,0,"00550041002D004B0059004900560053005400410052",2
    //+COPS: 0,0,"UA-KYIVSTAR" OK

    AT_COPS result;

    if(verboseMode)
        qDebug() << "decodeCops a " << readStr << readStr.toLocal8Bit().toHex() ;
    if(readStr.left(7) != "+COPS: ")
        return result;

    QStringList l = readStr.mid(7).simplified().trimmed().split(",",
                                                            #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                                                Qt::SkipEmptyParts
                                                            #else
                                                                QString::SkipEmptyParts
                                                            #endif
                                                                );
    if(l.size() > 2){
        if(!ignoreCopsCheck && l.at(1).toInt() > 0)
            return AT_COPS(true);

        QString s = l.at(2);
        s = s.remove('"').simplified().trimmed();

        bool ok = ( (s.toUpper() == s || s.toLower() == s) && ((s.length()%2) == 0));
        for(int i = 0, iMax = s.length(); i < iMax && ok; i += 8)
            s.mid(i, 10).toULongLong(&ok, 16);

        if(ok){
            QByteArray arr("");
            for(int i = 0, iMax = s.length(); i < iMax; i += 2){
                if(s.mid(i,2) == "00")
                    continue;
                arr.append(s.mid(i,2).toLocal8Bit());
            }
            s = QByteArray::fromHex( arr ).simplified().trimmed();


            if(!s.isEmpty()){
                result.operatorName = s;
            }else{
                ok = false;
            }
        }

        if(!ok)
            result.operatorName = QString(l.at(2)).remove('"').simplified().trimmed();

        if(verboseMode)
            qDebug() << "decodeCops b " << ok << result.operatorName << l.at(2);
    }

    if(l.size() > 3){
        result.nMode2g3g = "-";
        bool ok;
        if(l.at(3).toInt(&ok) == 2)
            result.nMode2g3g = "UMTS";
        else if(ok)
            result.nMode2g3g = "GSM";
    }
    if(verboseMode)
        qDebug() << "decodeCops c " << readStr << result.operatorName << result.nMode2g3g << l;

    result.isNull = result.operatorName.isEmpty();//if !true than ok

    return result;// !operatorName.isEmpty();

}

//------------------------------------------------------------------------------------

AT_CREG PrettyGsmHL8518values::decodeCreg(const QString &readStr)
{
    //+CREG: 2,1,"697E","01FB39B7",6
    //+CREG: 2,1,"697E","4845"

    AT_CREG result;

    bool retVal = false;



    if(readStr.left(7) != "+CREG: ")
        return result;

    QStringList l = readStr.mid(7).simplified().trimmed().split(",",
                                                            #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                                                Qt::SkipEmptyParts
                                                            #else
                                                                QString::SkipEmptyParts
                                                            #endif
                                                                );
    int s = l.size();

    int val = 0;
    bool ok = false;

    if(s > 1)
        val = l.at(1).toInt(&ok);

    result.regState = "-";
    if(ok){
        result.bandName = getCregState(val);
        retVal = true;

    }

    if(s > 2)
        result.lac = QString(l.at(2)).remove('"').simplified().trimmed().toULong(&ok, 16);

    retVal = (retVal && ok);

    if(s > 3)
        result.cellId = QString(l.at(3)).remove('"').simplified().trimmed().toULong(&ok, 16);

    retVal = (retVal && ok);

    ok = false;
    if(s > 4)
        val = l.at(4).simplified().trimmed().toInt(&ok);


    if(ok){
        retVal = true;
        result.bandName = getCregName(val);

    }

    if(result.bandName.isEmpty() && s > 3 ){//сумістність зі сторонніми модемами
        if(l.at(3).size() == 6)
            result.bandName = "2G";
        else if(l.at(3).size() == 10)
            result.bandName = "3G";

    }
    result.isNull = false;
    return result;
}

//------------------------------------------------------------------------------------

AT_CSQ PrettyGsmHL8518values::decodeCsqCommand(const QString &leftAnswr, const QString &readStr)
{
    //    hasEcNo = false;
    //    rssi = ber = ecNo = 99;

    AT_CSQ result;

    if(readStr.left(leftAnswr.length()) != leftAnswr)
        return result;


    const QStringList l = readStr.split(",",
                                    #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
                                        Qt::SkipEmptyParts
                                    #else
                                        QString::SkipEmptyParts
                                    #endif
                                        );
    if(verboseMode)
        qDebug() << "decodeCsqCommand l size " << l.size() << l;
    if(l.size() == 3 || l.size() == 2){
        bool ok, ok2, ok3;

        result.rssi = l.at(0).mid(leftAnswr.size()).simplified().trimmed().toInt(&ok);//$CSQ: 16,99,-12
        result.ber = l.at(1).simplified().trimmed().toInt(&ok2);

        result.hasEcNo = (l.size() == 3);
        if(result.hasEcNo)
            result.ecNo = l.at(2).simplified().trimmed().toInt(&ok3);
        else
            ok3 = true;

        result.isNull = !(ok && ok2 && ok3);


    }
    return result;
}

//------------------------------------------------------------------------------------
