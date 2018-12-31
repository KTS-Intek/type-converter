#include "embeedefaultreadcommandlist.h"

EmbeeDefaultReadCommandList::EmbeeDefaultReadCommandList(QObject *parent) : QObject(parent)
{

}

QStringList EmbeeDefaultReadCommandList::getDefaultReadCommandList()
{
    return QString("ATAD ATBD ATCH ATID ATNI ATSH ATSL ATVR ATHV ATHP ATC0 ATAP ATRN ATCP0").split(" ", QString::SkipEmptyParts);
}

QStringList EmbeeDefaultReadCommandList::getReadCommandList()
{

    QStringList l = getDefaultReadCommandList();
    l.append("ATSM");
    return l;
}

