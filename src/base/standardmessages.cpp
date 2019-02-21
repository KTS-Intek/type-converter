#include "standardmessages.h"

StandardMessages::StandardMessages(QObject *parent) : QObject(parent)
{

}

QString StandardMessages::cantOpenTheFile(const QString &filename, const QString &errstr)
{
    return tr("Can't open the file%1. '%2'").arg(addFileName(filename)).arg(errstr);
}

QString StandardMessages::cantOpenTheFileSmpl(const QString &errstr)
{
    return cantOpenTheFile(QString(), errstr);
}

QString StandardMessages::cantOpenTheFileMeter(const QString &errstr)
{
    return StandardMessages::cantOpenTheFile("meter", errstr);
}

QString StandardMessages::cantReadThisNplainTextFile(const QString &filename)
{
    return tr("It is not a plain text file.<br>Can't read this file(<br>%1").arg(filename);
}

QString StandardMessages::cantSaveTheFile(const QString &filename, const QString &errstr)
{
    return tr("Can't save the file%1. '%2'").arg(addFileName(filename)).arg(errstr);
}

QString StandardMessages::cantSaveTheseSettings(const QString &errstr)
{
    return tr("Can't save thsese settings '%1'").arg(errstr);
}

QString StandardMessages::cantOpenTheConnection(const QString &err)
{
    return tr("Can't establish a connection. '%1'").arg(err);
}

QString StandardMessages::badInputDataNesessaryKeys()
{
    return tr("The nesessary keys were not found");
}

QString StandardMessages::cantDeleteTheFile(const QString &filename, const QString &errstr)
{
    return tr("Can't delete the file%1, '%2'").arg(addFileName(filename)).arg(errstr);
}

QString StandardMessages::addFileName(const QString &filename)
{
    return filename.isEmpty() ? "" : QString(" '%1'").arg(filename);
}
