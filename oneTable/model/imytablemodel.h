#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H
class QString;
class QStringMatcher;

class IMyTableModel{
public:
    virtual void AddColumn(const QString &columnName, bool defaultValue) = 0;
    virtual void AddColumn(const QString &columnName, int defaulValue) = 0;
    virtual void AddColumn(const QString &columnName, double defaultValue) = 0;
    virtual void AddColumn(const QString &columnName, const QString &defaultValue) = 0;
    virtual void AddColumn(const QString &columnName, const QStringMatcher &defaultValue) = 0;

    virtual void RemoveColumn(const QString &columnName) = 0;
};

#endif // MYTABLEMODEL_H
