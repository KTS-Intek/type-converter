#ifndef GSMNOTIFICATIONTYPES_H
#define GSMNOTIFICATIONTYPES_H

#include <QVector>

#define GSM_BAND_NOT_AVAILABLE  0x0000 // Not available
#define GSM_BAND_GSM_850        0x0001 // GSM 850 MHz
#define GSM_BAND_GSM_900        0x0002 // GSM 900 MHz and E-GSM
#define GSM_BAND_DCS_1800       0x0004 // DCS 1800 MHz
#define GSM_BAND_PCS_1900       0x0008 // PCS 1900 MHz
#define GSM_BAND_UMTS_1         0x0010 // UMTS Band 1 (2100 MHz)
#define GSM_BAND_UMTS_2         0x0020 // UMTS Band 2 (1900 MHz)
#define GSM_BAND_UMTS_5         0x0040 //UMTS Band 5 (850 MHz)
#define GSM_BAND_UMTS_6         0x0080 //UMTS Band 6 (800 MHz)
#define GSM_BAND_UMTS_8         0x0100 //UMTS Band 8 (900 MHz)
#define GSM_BAND_UMTS_9         0x0200 //UMTS Band 9 (800 MHz)

#define GSM_EVENT_LOW_BALANCE   0
#define GSM_EVENT_WAS_CHARGED   1

#define GSM_EVENT_STATE_UNKNOWN           0 //send a message
#define GSM_EVENT_STATE_ACTIVATED         1 //send a message
#define GSM_EVENT_STATE_IS_STILL_ACTV     2 //do not do anything
#define GSM_EVENT_STATE_DIDNT_ACTV        3 //
#define GSM_EVENT_STATE_IS_STILL_NACTV    4 //

struct AT_CREG
{
    bool isNull;
    quint32 lac;
    quint32 cellId;
    QString bandName;
    QString regState;

    AT_CREG() : isNull(true), lac(0), cellId(0) {}
};


struct AT_COPS
{
    bool isNull;
    QString operatorName;
    QString nMode2g3g;
    bool writeCopsZero;

    AT_COPS() : isNull(true), writeCopsZero(false) {}
    AT_COPS(const bool &writeCopsZero) : isNull(false), writeCopsZero(writeCopsZero) {}
};


struct AT_CSQ
{
    bool isNull;
    int rssi;
    int ber;
    int ecNo;
    bool hasEcNo;
    AT_CSQ() : isNull(true), rssi(99), ber(99), ecNo(99), hasEcNo(false) {}
};

struct SendSMSandMakeACall
{
    QStringList contacts;
    QString currencyLabel;
    bool currencyLabelIsAtTheEnd;
    qreal lowBalance;

    QString callThisNumber;

    SendSMSandMakeACall() : currencyLabelIsAtTheEnd(true), lowBalance(1.0) {}
};

#endif // GSMNOTIFICATIONTYPES_H
