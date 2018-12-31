#ifndef EMBEEDEFAULTREADCOMMANDLIST_H
#define EMBEEDEFAULTREADCOMMANDLIST_H

#include <QObject>
#include <QStringList>

class EmbeeDefaultReadCommandList : public QObject
{
    Q_OBJECT
public:
    explicit EmbeeDefaultReadCommandList(QObject *parent = nullptr);

    static QStringList getDefaultReadCommandList();

    static QStringList getReadCommandList();

signals:

public slots:
};

#endif // EMBEEDEFAULTREADCOMMANDLIST_H
