#include "postgrerequestmaker.h"

PostgreRequestsMaker::PostgreRequestsMaker(QObject *parent)
    : QObject(parent)
    , ITableMediator()
    , IDatabaseMediator()
    , m_allTablesListModel(new QSqlQueryModel())
{
    qDebug()<< "created";
}

PostgreRequestsMaker::~PostgreRequestsMaker()
{
    qDebug()<< "deleted";
}

QSqlQueryModel *PostgreRequestsMaker::UpdateAllTablesListIntoModel()
{
    QSqlQuery query(IDatabaseMediator::m_db);
    query.prepare(QStringLiteral("SELECT tablename FROM pg_tables WHERE schemaname = 'public'"));
    if(query.exec())
    {
        m_allTablesListModel->setQuery(query);
        if(1==m_allTablesListModel->columnCount())
        {
            return  m_allTablesListModel;
        }
        else
        {
            return Q_NULLPTR;
        }
    }
    return  Q_NULLPTR;
}

QStringList PostgreRequestsMaker::GetAllTablesList()
{
    QSqlQuery query(IDatabaseMediator::m_db);
    query.prepare(QStringLiteral("SELECT tablename FROM pg_tables WHERE schemaname = 'public'"));
    if(query.exec())
    {
        QStringList tablesList;
        while(query.next())
        {
            tablesList.append(GetStringInRowFromMessage(query.record(), 0));
        }
        return  tablesList;
    }
    else
    {
        qFatal("%s", QString(Q_FUNC_INFO+ QStringLiteral(" Не получается проверить наличилие таблицы с пользователями. Ошибка: ")+ query.lastError().text()+ QStringLiteral( " запрос: ") + query.lastQuery()).toUtf8().constData());
    }
}

void PostgreRequestsMaker::CreateTable(const QString &sqlRequest)
{
    if(sqlRequest.startsWith(QStringLiteral("CREATE TABLE ")))
    {
        const QStringList TablesList=GetAllTablesList();
        qDebug()<< sqlRequest;
        int indexOfStart=sqlRequest.indexOf('(');
        //15 так как "CREATE TABLE " уже 14 и длина таблицы >=1 символа
        if(indexOfStart>=15)
        {
            //13 это позииция после пробела у строки "CREATE TABLE "
            //14 так как индекс указывает на скобочку
            const QString tableName=sqlRequest.mid(13, indexOfStart-14);
            if (TablesList.contains(tableName))
            {
                Q_EMIT ToStatusBar(QStringLiteral("Таблица %1 уже существует").arg(tableName));
            }
            else
            {
                QSqlQuery query(IDatabaseMediator::m_db);
                if(query.exec(sqlRequest))
                {
                    Q_EMIT ToNewTableCreated(tableName);
                }
                else
                {
                    Q_EMIT ToStatusBar(QStringLiteral("Не получилось создать таблицу %1. Ошибка %2").arg(tableName).arg(query.lastError().text()));
                }
            }
        }
        else
        {
            qFatal("%s", QStringLiteral("Неправильный запрос").toUtf8().constData());
        }
    }
    else
    {
        qFatal("%s", QStringLiteral("Неверная команда в метод создания таблицы").toUtf8().constData());
    }
}

void PostgreRequestsMaker::FillTableData(const QString &sqlRequest)
{
    if(sqlRequest.startsWith(QStringLiteral("INSERT INTO ")))
    {
        QSqlQuery query(IDatabaseMediator::m_db);
        if(!query.exec(sqlRequest))
        {
            Q_EMIT ToStatusBar(QStringLiteral("Не запонить создать таблицу. Ошибка %1").arg(query.lastError().text()));
        }
    }
    else
    {
        qFatal("%s", QStringLiteral("Неверная команда в метод заполнения таблицы").toUtf8().constData());
    }
}

void PostgreRequestsMaker::DropTable(const QString &tableName)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    const QString request="DROP TABLE "+tableName;
    if(!query.exec(request))
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу удалить таблицу. ")+ tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::FillTable(MyTableModel * model, const QString &tableName)
{
    model->setTable(tableName);
    const bool canSelect=model->select();
    if(!canSelect)
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу получить данные с таблицы. Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

QStringList PostgreRequestsMaker::GetAllTableColumns(const QString &tableName)
{

}

QString PostgreRequestsMaker::GetColumnType(const QString &tableName, const QString &columnNames)
{

}

QStringList PostgreRequestsMaker::GetAllColumnRows(const QString &tableName, const QString &columnNames)
{

}

void PostgreRequestsMaker::AddColumnToTable(const QString &tableName, const QString &columnName, bool defaultValue)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    QString request;
    if (defaultValue)
    {
        request="ALTER TABLE " +tableName +" ADD COLUMN "+columnName+" boolean NOT NULL DEFAULT true";
    }
    else
    {
        request="ALTER TABLE " +tableName +" ADD COLUMN "+columnName+" boolean NOT NULL DEFAULT false";
    }
    if(!query.exec(request))
    {
        qDebug()<<  query.lastError().text();
        Q_EMIT ToStatusBar(QStringLiteral("Не могу добавить колонку в таблицу: ") + tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::AddColumnToTable(const QString &tableName, const QString &columnName, double defaultValue)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    const QString request="ALTER TABLE " +tableName +" ADD COLUMN "+columnName+" real NOT NULL DEFAULT "+QString::number(defaultValue) + ";";
    if(!query.exec(request))
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу добавить колонку в таблицу: ") + tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::AddColumnToTable(const QString &tableName, const QString &columnName, int defaultValue)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    const QString request="ALTER TABLE " +tableName +" ADD COLUMN "+columnName+" integer NOT NULL DEFAULT "+QString::number(defaultValue) + ";";
    if(!query.exec(request))
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу добавить колонку в таблицу: ") + tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::AddColumnToTable(const QString &tableName, const QString &columnName, const QString &defaultValue)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    const QString request="ALTER TABLE " +tableName +" ADD COLUMN "+columnName+" character varying (20) NOT NULL DEFAULT ('"+ defaultValue+",'::varchar(20));";
    if(!query.exec(request))
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу добавить колонку в таблицу: ") + tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::RemoveColumnFromTable(const QString &tableName, const QString &columnName)
{
    QSqlQuery query(IDatabaseMediator::m_db);
    const QString request="ALTER TABLE " +tableName +" DROP COLUMN "+columnName;
    if(!query.exec(request))
    {
        Q_EMIT ToStatusBar(QStringLiteral("Не могу добавить колонку в таблицу: ") + tableName + QStringLiteral(" Ошибка: ")+ ITableMediator::m_db.lastError().text());
    }
}

void PostgreRequestsMaker::SetBoolIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, bool value)
{

}

void PostgreRequestsMaker::SetIntIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value)
{

}

void PostgreRequestsMaker::SetStringIntoTable(const QString &tableName, const QString &columnName, const QString &rowId, int value)
{

}
