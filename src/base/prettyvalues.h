#ifndef PRETTYVALUES_H
#define PRETTYVALUES_H

#include <QObject>
#include <QString>
#include <QVariantHash>

class PrettyValues
{

public:
    static QString getBuildDateStr() ;

    static QDateTime getBuildDate();

    static QString prettyTimeValueFromSecsWitAMask(const qint64 &secsmynulo);

    static QString prettyTimeValueFromSecs(const qint64 &secsmynulo);

    static QString prettyTimeValue(const qint64 &msecmynulo);
    static QString prettyTimeValueMsec(const qint64 &msecmynulo);

    static QString prettyTimeValue(QString &f, qint64 msecmynulo);

    static QString prettyTimeValueExt(const bool &addmsec, QString &f, qint64 msecmynulo);


//    static QString tablenameEnd4pollCode(const quint8 &pollCode);


    static QDateTime tableName2DateTime(const QString &tableName, const qint32 addDays = 0, const bool useLocal = false);


    static QString getTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode);

    static QString getFullTableName4poll(const QDateTime &dtPoll, const quint8 &pollCode);

    static QDateTime getDateTime4poll(const QDateTime &dtPoll, const quint8 &pollCode);


    static QString prettyNumber(const qreal &val, int mPrec) ;

     static QString prettyNumber(const qreal &val, int mPrec, const int &maxPlgPrec) ;

     static QString prettyLongNumber(const QString &s) ;

     static QString prettyLongNumber(const int &v) ;

     static QString prettyBabloNumber(const QString &s) ;


     static QString prettyHexDump(const QList<quint8> &list, const quint8 &command);

     static QString prettyHexDump(const QByteArray &messArrH, const QByteArray &commandH, const quint8 &errCode);

     static QString prettyHexDump(QByteArray arr);

     static  void removeLineFromList(const QString &lPartOfline, QStringList &l);

     static  QStringList replaceLineFromList(const QString &lPartOfline, QStringList l, const QString &rPartOfLine);


     //guihelper
     static QString humanByteView(QString str);

     static QString humanByteView(const qint64 &val);

     //showmesshelper4wdgt
     static QString addWithFontColorRed(const QString m);

     static QString byte2humanRead(const qint64 &bytes);

     static QString connectionsett2prettyHuman(const QString &ip, const quint16 &port, const QString &login, const QString &objname, const QString &optionalmac);


     static QString getPrettyIfaceName(const QVariantHash &h);


     static QString normalizeStr(const qreal &value, const int &decimalPosition, const bool &useDecimalPoint);
     static QString checkDecimalSeparator(const QString &valuestr, const bool &useDecimalPoint);

     static QString prettyLongTextView(QString s);

};

#endif // PRETTYVALUES_H
