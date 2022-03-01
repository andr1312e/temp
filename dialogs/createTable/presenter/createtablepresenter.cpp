#include "createtablepresenter.h"

CreateTablePresenter::CreateTablePresenter(IDatabaseMediator *iRequestMaker, QObject *parent)
    : QObject(parent)
    , m_iRequestMaker(iRequestMaker)
{

}

CreateTablePresenter::~CreateTablePresenter()
{

}

QStringList CreateTablePresenter::GetAllTablesList()
{
    return  m_iRequestMaker->GetAllTablesList();
}
