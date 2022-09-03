#include "embeedefaultreadcommandlist.h"

EmbeeDefaultReadCommandList::EmbeeDefaultReadCommandList(QObject *parent) : QObject(parent)
{

}

QStringList EmbeeDefaultReadCommandList::getDefaultReadCommandList()
{
    return QString("ATAD ATBD ATCH ATID ATNI ATSH ATSL ATVR ATHV ATHP ATC0 ATAP ATRN ATCP0").split(" ",
                                                                                               #if QT_VERSION >= 0x050900
                                                                                                   Qt::SkipEmptyParts
                                                                                               #else
                                                                                                   QString::SkipEmptyParts
                                                                                               #endif
                                                                                                   );
}

QStringList EmbeeDefaultReadCommandList::getReadCommandList()
{

    QStringList l = getDefaultReadCommandList();
    l.append("ATSM");
    return l;
}

