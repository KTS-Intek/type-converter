#ifndef IFACEMANAGERHELPER_H
#define IFACEMANAGERHELPER_H

#include <QString>
#include <QHostAddress>

class IfaceManagerHelper
{
public:
    static bool isPppName(const QString &name);

    static bool ignoreThisIface(const QString &name, const QHostAddress &ip, const QHostAddress &mask);
};

#endif // IFACEMANAGERHELPER_H
