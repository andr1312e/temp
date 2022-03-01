#ifndef CREATETABLEPRESENTER_H
#define CREATETABLEPRESENTER_H

#include <QObject>
#include <QSharedPointer>
#include "model/mediatorrepository.h"

class CreateTablePresenter : public QObject
{
    Q_OBJECT
public:
    explicit CreateTablePresenter(IDatabaseMediator *iRequestMaker, QObject *parent);
    ~CreateTablePresenter();
public:
    QStringList GetAllTablesList();
private:
    IDatabaseMediator *m_iRequestMaker;
};

#endif // CREATETABLEPRESENTER_H
