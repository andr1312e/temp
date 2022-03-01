#ifndef IREQUESTMAKER_H
#define IREQUESTMAKER_H
class QStringList;
class QString;
class QDockWidget;
class QSqlQueryModel;
class MyTableModel;
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>

class ITableMediator{

public:
    virtual ~ITableMediator() {};
    virtual void RegisterQSqlDatabase(const QSqlDatabase &database);
public:
    virtual void FillTable(MyTableModel * model, const QString &tableName) = 0;
    virtual QStringList GetAllTableColumns(const QString &tableName) = 0;
    virtual QString GetColumnType(const QString &tableName, const QString &columnNames) = 0;
    virtual QStringList GetAllColumnRows(const QString &tableName, const QString &columnNames) = 0;

    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, bool defaultValue) = 0;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, double defaultValue) = 0;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, int defaultValue) = 0;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, const QString &defaultValue) = 0;

    virtual void RemoveColumnFromTable(const QString &tableName, const QString &columnName) = 0;

    virtual void SetBoolIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, bool value) = 0;
    virtual void SetIntIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value) = 0;
    virtual void SetStringIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value) = 0;
public:
    const QSqlDatabase& GetDatabase(){return m_db;};
protected:
    QString GetStringInRowFromMessage(const QSqlRecord &record, const int &numberOfField) const;
    QStringList GetStringListFromRowMessage(const QSqlRecord &record) const;
protected:
    QSqlDatabase m_db;
};


#endif // IREQUESTMAKER_H

