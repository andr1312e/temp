#include "mytablemodel.h"

MyTableModel::MyTableModel(ITableMediator *tableMediator, const QString &tableName, QDockWidget *parentWidget)
    : QSqlRelationalTableModel(parentWidget, tableMediator->GetDatabase())
    , m_tableName(tableName)
    , m_tableMediator(tableMediator)
{
    m_tableMediator->FillTable(this, tableName);
}

MyTableModel::~MyTableModel()
{

}

void MyTableModel::AddColumn(const QString &columnName, bool defaultValue)
{
    m_tableMediator->AddColumnToTable(m_tableName, columnName, defaultValue);
    m_tableMediator->FillTable(this, m_tableName);
}

void MyTableModel::AddColumn(const QString &columnName, int defaultValue)
{
    m_tableMediator->AddColumnToTable(m_tableName, columnName, defaultValue);
    m_tableMediator->FillTable(this, m_tableName);
}

void MyTableModel::AddColumn(const QString &columnName, double defaultValue)
{
    m_tableMediator->AddColumnToTable(m_tableName, columnName, defaultValue);
    m_tableMediator->FillTable(this, m_tableName);
}

void MyTableModel::AddColumn(const QString &columnName, const QString &defaultValue)
{
    m_tableMediator->AddColumnToTable(m_tableName, columnName, defaultValue);
    m_tableMediator->FillTable(this, m_tableName);
}

void MyTableModel::AddColumn(const QString &columnName, const QStringMatcher &defaultValue)
{

}

void MyTableModel::RemoveColumn(const QString &columnName)
{
    m_tableMediator->RemoveColumnFromTable(m_tableName, columnName);
    m_tableMediator->FillTable(this, m_tableName);
}





