#ifndef POSTGREREQUESTMAKER_H
#define POSTGREREQUESTMAKER_H
#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

#include "model-interface/itablemediator.h"
#include "model-interface/itoolbarrequestmaker.h"

#include "oneTable/model/mytablemodel.h"

class PostgreRequestsMaker : public QObject, public ITableMediator, public IDatabaseMediator
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PostgreRequestsMaker(QObject *parent=Q_NULLPTR);
    virtual ~PostgreRequestsMaker() Q_DECL_OVERRIDE;
Q_SIGNALS:
    void ToStatusBar(const QString &message);
    void ToNewTableCreated(const QString &tableName);
public: 
    virtual QSqlQueryModel *UpdateAllTablesListIntoModel() Q_DECL_OVERRIDE;
    virtual QStringList GetAllTablesList() Q_DECL_OVERRIDE;
    virtual void CreateTable(const QString &sqlRequest) Q_DECL_OVERRIDE;
    virtual void FillTableData(const QString &sqlRequest) Q_DECL_OVERRIDE;
    virtual void DropTable(const QString &tableName) Q_DECL_OVERRIDE;
public:
    virtual void FillTable(MyTableModel * model, const QString &tableName) Q_DECL_OVERRIDE;
    virtual QStringList GetAllTableColumns(const QString &tableName) Q_DECL_OVERRIDE;
    virtual QString GetColumnType(const QString &tableName, const QString &columnNames) Q_DECL_OVERRIDE;
    virtual QStringList GetAllColumnRows(const QString &tableName, const QString &columnNames) Q_DECL_OVERRIDE;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, bool defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, double defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, int defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumnToTable(const QString &tableName, const QString &columnName, const QString &defaultValue) Q_DECL_OVERRIDE;
    virtual void RemoveColumnFromTable(const QString &tableName, const QString &columnName) Q_DECL_OVERRIDE;

    virtual void SetBoolIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, bool value) Q_DECL_OVERRIDE;
    virtual void SetIntIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value) Q_DECL_OVERRIDE;
    virtual void SetStringIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value) Q_DECL_OVERRIDE;
private:
    QSqlQueryModel * const m_allTablesListModel;

};
Q_DECLARE_METATYPE(PostgreRequestsMaker*)

#endif // POSTGREREQUESTMAKER_H
