#ifndef TOOLBARPRESENTER_H
#define TOOLBARPRESENTER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMetaType>

#include "model/databasedrivers.h"

#include "model-interface/itablemediator.h"
#include "model/postgrerequestmaker.h"
#include "model/mediatorrepository.h"

class ToolBarPresenter : public QObject
{
    Q_OBJECT
public:
    explicit ToolBarPresenter(const QSharedPointer<MediatorRepository> &mediatorRepository, QObject *parent);
    ~ToolBarPresenter();
Q_SIGNALS:
    void ToStatusBar(const QString &message);
public:
    IDatabaseMediator *GetInterface(){return m_iRequestMaker;};
    bool ConnectedToDb(const QString& databaseDriver, const QString &hostName, const quint16 databasePort, const QString &databaseName, const QString &userName, const QString &userPassword, QString &error);
    void DisconnectFromDB();
    QSqlQueryModel *GetAllModelTablesList();
    QStringList GetAllTablesList();

    void CreateTable(const QString &query);
    void FillTablesByData(const QString &query);
private:
    void CreateRequestMakerBasedOnDriverName(const QString &driverName);
private:
    QSqlDatabase m_sqlDatabase;
    IDatabaseMediator *m_iRequestMaker=Q_NULLPTR;
    const QSharedPointer<MediatorRepository> m_mediatorRepository;

};

#endif // TOOLBARPRESENTER_H
