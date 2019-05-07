#ifndef COMMANDLINEDECODER_H
#define COMMANDLINEDECODER_H

#include <QStringList>


class CommandLineDecoder
{

public:

    static int valFromArgs(const QStringList &listArgs, const QString &keyStr, const int minVal, const int maxVal, bool &valGood, QString &mess);
    static int valFromArgs(const QStringList &listArgs, const QString &keyStr, const QList<int> allowVal, bool &valGood, QString &mess);

    static QString valFromArgs(const QStringList &listArgs, const QString &keyStr, bool &valGood, QString &mess);
    static QString valFromArgs(const QStringList &listArgs, const QString &keyStr, const QStringList allowVal, bool &valGood, QString &mess);


};

#endif // COMMANDLINEDECODER_H
