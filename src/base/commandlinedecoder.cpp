#include "commandlinedecoder.h"

//---------------------------------------------------------------------------------

int CommandLineDecoder::valFromArgs(const QStringList &listArgs, const QString &keyStr, const int minVal, const int maxVal, bool &valGood, QString &messageStrr)
{
    int i = listArgs.indexOf(keyStr) + 1;
    valGood = false;
    int retVal = minVal - 1;
    if(i < listArgs.size()){
        retVal = listArgs.at(i).toInt(&valGood);
        if(valGood && retVal >= minVal && retVal <= maxVal)
            valGood = true;
        else
            valGood = false;
    }
    if(!valGood){
        messageStrr = "Invalid argument " + keyStr;
    }

    return retVal;
}

//---------------------------------------------------------------------------------

int CommandLineDecoder::valFromArgs(const QStringList &listArgs, const QString &keyStr, const QList<int> allowVal, bool &valGood, QString &messageStrr)
{
    int i = listArgs.indexOf(keyStr) + 1;
    valGood = false;
    int retVal = 0 - 1;
    if(i < listArgs.size()){
        retVal = listArgs.at(i).toInt(&valGood);
        if(!allowVal.contains(retVal))
            valGood = false;
    }
    if(!valGood){
        messageStrr = "Invalid argument " + keyStr;
    }

    return retVal;
}

//---------------------------------------------------------------------------------

QString CommandLineDecoder::valFromArgs(const QStringList &listArgs, const QString &keyStr, bool &valGood, QString &messageStrr)
{
    int i = listArgs.indexOf(keyStr) + 1;
    valGood = false;
    QString retVal;
    if(i < listArgs.size()){
        retVal = listArgs.at(i);
        valGood = true;
    }
    if(!valGood)
        messageStrr = "Invalid argument " + keyStr;

    return retVal;
}

//---------------------------------------------------------------------------------

QString CommandLineDecoder::valFromArgs(const QStringList &listArgs, const QString &keyStr, const QStringList allowVal, bool &valGood, QString &messageStrr)
{
    int i = listArgs.indexOf(keyStr) + 1;
    valGood = false;
    QString retVal("");
    if(i < listArgs.size()){
        retVal = listArgs.at(i);
        valGood = allowVal.contains(retVal);
    }
    if(!valGood){
        messageStrr = "Invalid argument " + keyStr;
    }
    return retVal;
}
//---------------------------------------------------------------------------------

