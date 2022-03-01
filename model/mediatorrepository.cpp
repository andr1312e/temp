#include "mediatorrepository.h"

MediatorRepository::MediatorRepository()
{

}

MediatorRepository::~MediatorRepository()
{
    DeleteOldObject();
}

IDatabaseMediator *MediatorRepository::GetDatabaseMediator() const
{
    return m_iDatabaseMediator;
}

void MediatorRepository::SetIDatabaseMediator(IDatabaseMediator *iDatabaseMediator)
{
    m_iDatabaseMediator = iDatabaseMediator;
}

ITableMediator *MediatorRepository::GetTableMediator() const
{
    return m_iTableMediator;
}

void MediatorRepository::SetITableMediator(ITableMediator *iTableMediator)
{
    m_iTableMediator = iTableMediator;
}

bool MediatorRepository::CreateObjectBasedOnDriver(const int qtDriverMetaType)
{
    DeleteOldObject();
    const QMetaObject * const metaObjectForOurDatabase = QMetaType::metaObjectForType(qtDriverMetaType);
    m_mediatorObject=metaObjectForOurDatabase->newInstance();
    m_iDatabaseMediator=dynamic_cast<IDatabaseMediator*>(m_mediatorObject);
    m_iTableMediator=dynamic_cast<ITableMediator*>(m_mediatorObject);
    return (m_iDatabaseMediator!=Q_NULLPTR)&&(m_iDatabaseMediator!=Q_NULLPTR);
}

void MediatorRepository::RegisterQSqlDatabaseObject(QSqlDatabase &database)
{
    m_iDatabaseMediator->RegisterQSqlDatabase(database);
    m_iTableMediator->RegisterQSqlDatabase(database);
}

void MediatorRepository::DeleteOldObject()
{
    if(m_mediatorObject!=Q_NULLPTR)
    {
        delete m_mediatorObject;
        m_mediatorObject=Q_NULLPTR;
        m_iDatabaseMediator=Q_NULLPTR;
        m_iTableMediator=Q_NULLPTR;
    }
}
