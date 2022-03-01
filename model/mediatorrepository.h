#ifndef MEDIATORREPOSITORY_H
#define MEDIATORREPOSITORY_H
#include <QSqlDatabase>

#include "model-interface/itablemediator.h"
#include "model-interface/itoolbarrequestmaker.h"

class MediatorRepository
{
public:
    MediatorRepository();
    ~MediatorRepository();

public:
    IDatabaseMediator *GetDatabaseMediator() const;
    void SetIDatabaseMediator(IDatabaseMediator *GetDatabaseMediator);

    ITableMediator *GetTableMediator() const;
    void SetITableMediator(ITableMediator *GetTableMediator);

    bool CreateObjectBasedOnDriver(const int qtDriverMetaType);
    void RegisterQSqlDatabaseObject(QSqlDatabase &database);
private:
    void DeleteOldObject();
private:
    QObject *m_mediatorObject=Q_NULLPTR;
    IDatabaseMediator *m_iDatabaseMediator=Q_NULLPTR;
    ITableMediator *m_iTableMediator=Q_NULLPTR;
};

#endif // MEDIATORREPOSITORY_H
