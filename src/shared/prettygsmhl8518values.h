#ifndef PRETTYGSMHL8518VALUES_H
#define PRETTYGSMHL8518VALUES_H

#include <QObject>
#include <QStringList>
#include <QVariantHash>
#include <QDebug>

#include "gsmnotificationtypes.h"

class PrettyGsmHL8518values : public QObject
{
    Q_OBJECT
public:
    explicit PrettyGsmHL8518values(QObject *parent = nullptr);

    bool verboseMode;

    enum SIM_STATE{
        UNKNOWN = -1,
        READY ,
        SIM_PIN,
        SIM_PUK,
        SIM_PIN2,
        SIM_PUK2,
        PH_NET_PIN,
        PH_NET_PUK,
        PH_NETSUB_PIN ,
        PH_NETSUB_PUK ,
        PH_SP_PIN,
        PH_SP_PUK,
        PH_CORP_PIN,
        PH_CORP_PUK
    };

    static QString convert2gsmString(const QString &utfstr);


    static QString getBandName(const quint32 &kbnd);

    static QString getCregState(const int &val);

    static QString getCregName(const int &val);


    static QString getHumanReadableRssi(const int &csqrssi);

    static QString getHumanReadableBer(const int &csqber);

    static QStringList getPinPossibleAnswers();

    static QString getPIN1stateMessage(const SIM_STATE &simstate);


    bool decodeKbnd(const QString &readStr, QString &bandName);



    AT_COPS decodeCops(const QString &readStr, const bool &ignoreCopsCheck);


    AT_CREG decodeCreg(const QString &readStr);

    AT_CSQ decodeCsqCommand(const QString &leftAnswr, const QString &readStr);



signals:

};

#endif // PRETTYGSMHL8518VALUES_H
