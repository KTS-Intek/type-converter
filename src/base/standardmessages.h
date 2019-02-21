#ifndef STANDARDMESSAGES_H
#define STANDARDMESSAGES_H

#include <QObject>
#include <QString>

class StandardMessages : public QObject
{
    Q_OBJECT
public:
    explicit StandardMessages(QObject *parent = nullptr);

    static QString cantOpenTheFile(const QString &filename, const QString &errstr);

    static QString cantOpenTheFileSmpl(const QString &errstr);

    static QString cantOpenTheFileMeter(const QString &errstr);

    static QString cantReadThisNplainTextFile(const QString &filename);


    static QString cantSaveTheFile(const QString &filename, const QString &errstr);

    static QString cantSaveTheseSettings(const QString &errstr);


    static QString cantOpenTheConnection(const QString &err);

    static QString badInputDataNesessaryKeys();


    static QString cantDeleteTheFile(const QString &filename, const QString &errstr);


signals:

public slots:
private:
    static QString addFileName(const QString &filename);

};

#endif // STANDARDMESSAGES_H
