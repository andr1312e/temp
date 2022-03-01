#ifndef ITOOLBARREQUESTMAKER_H
#define ITOOLBARREQUESTMAKER_H
class QStringList;
class QSqlQueryModel;
#include <QSqlDatabase>

class IDatabaseMediator{
public:
    virtual ~IDatabaseMediator() {};
    virtual void RegisterQSqlDatabase(const QSqlDatabase &database)
    {
        m_db=database;
    };
    virtual QSqlQueryModel* UpdateAllTablesListIntoModel() = 0;
    virtual QStringList GetAllTablesList() = 0;

    virtual void CreateTable(const QString &sqlRequest) = 0;
    virtual void FillTableData(const QString &sqlRequest) = 0;
    virtual void DropTable(const QString &tableName) = 0;

protected:
    QSqlDatabase m_db;
};
#endif // ITOOLBARREQUESTMAKER_H
