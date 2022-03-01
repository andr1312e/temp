#ifndef MYSQLQUERYTABLEMODEL_H
#define MYSQLQUERYTABLEMODEL_H
#include <QDockWidget>

#include <QSqlRelationalTableModel>

#include "oneTable/model/imytablemodel.h"
#include "model-interface/itablemediator.h"

class MyTableModel : public QSqlRelationalTableModel, public IMyTableModel
{
    Q_OBJECT
public:
    MyTableModel(ITableMediator *tableMediator, const QString &tableName, QDockWidget *parentWidget);
    ~MyTableModel();
public:
    virtual void AddColumn(const QString &columnName, bool defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumn(const QString &columnName, int defaulValue) Q_DECL_OVERRIDE;
    virtual void AddColumn(const QString &columnName, double defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumn(const QString &columnName, const QString &defaultValue) Q_DECL_OVERRIDE;
    virtual void AddColumn(const QString &columnName, const QStringMatcher &defaultValue) Q_DECL_OVERRIDE;

    virtual void RemoveColumn(const QString &columnName) Q_DECL_OVERRIDE;
private:
    const QString m_tableName;
    ITableMediator * const m_tableMediator;
};

#endif // MYSQLQUERYTABLEMODEL_H
