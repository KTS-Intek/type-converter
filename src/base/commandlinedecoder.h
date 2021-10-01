#ifndef COMMANDLINEDECODER_H
#define COMMANDLINEDECODER_H

#include <QStringList>


class CommandLineDecoder
{

public:

    static int valFromArgs(const QStringList &listArgs, const QString &keyStr, const int minVal, const int maxVal, bool &valGood, QString &messageStrr);
    static int valFromArgs(const QStringList &listArgs, const QString &keyStr, const QList<int> allowVal, bool &valGood, QString &messageStrr);

    static QString valFromArgs(const QStringList &listArgs, const QString &keyStr, bool &valGood, QString &messageStrr);
    static QString valFromArgs(const QStringList &listArgs, const QString &keyStr, const QStringList allowVal, bool &valGood, QString &messageStrr);


};

#endif // COMMANDLINEDECODER_H
