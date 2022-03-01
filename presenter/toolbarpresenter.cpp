#include "presenter/toolbarpresenter.h"

ToolBarPresenter::ToolBarPresenter(const QSharedPointer<MediatorRepository> &mediatorRepository, QObject *parent)
    : QObject(parent)
    , m_mediatorRepository(mediatorRepository)
{

}

ToolBarPresenter::~ToolBarPresenter()
{

}

bool ToolBarPresenter::ConnectedToDb(const QString &databaseDriver, const QString &hostName, const quint16 databasePort, const QString &databaseName, const QString &userName, const QString &userPassword, QString &error)
{
    if(!m_sqlDatabase.isOpen())
    {
        m_sqlDatabase=QSqlDatabase::addDatabase(databaseDriver, QLatin1String("defaultConnection"));
        m_sqlDatabase.setHostName(hostName);
        m_sqlDatabase.setPort(databasePort);
        m_sqlDatabase.setDatabaseName(databaseName);
        if(m_sqlDatabase.open(userName, userPassword))
        {
            CreateRequestMakerBasedOnDriverName(databaseDriver);
            return true;
        }
        else
        {
            error=m_sqlDatabase.lastError().text();
        }
    }
    return false;
}

void ToolBarPresenter::DisconnectFromDB()
{
    if (m_sqlDatabase.isOpen())
    {
        m_sqlDatabase.close();
        Q_EMIT ToStatusBar(QStringLiteral("Соединение закрыто"));
    }
    else
    {
        Q_EMIT ToStatusBar(QStringLiteral("Соединение не может быть закрыто, m_sqlDatabase.isOpen() вернул фолс. Ошибка: " )+ m_sqlDatabase.lastError().text());
    }
}

QSqlQueryModel *ToolBarPresenter::GetAllModelTablesList()
{
    return m_iRequestMaker->UpdateAllTablesListIntoModel();
}

QStringList ToolBarPresenter::GetAllTablesList()
{
    return m_iRequestMaker->GetAllTablesList();
}

void ToolBarPresenter::CreateTable(const QString &query)
{
     m_iRequestMaker->CreateTable(query);
}

void ToolBarPresenter::FillTablesByData(const QString &query)
{
    m_iRequestMaker->FillTableData(query);
}

void ToolBarPresenter::CreateRequestMakerBasedOnDriverName(const QString &driverName)
{
    //переписать логику на проверку
    const int qtDriverMetaType=m_databaseDriverNameToDatabaseName.value(driverName).second;
    if(m_mediatorRepository->CreateObjectBasedOnDriver(qtDriverMetaType))
    {
        m_mediatorRepository->RegisterQSqlDatabaseObject(m_sqlDatabase);
    }
    m_iRequestMaker=m_mediatorRepository->GetDatabaseMediator();
}
