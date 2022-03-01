#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QListView>
#include <QFileDialog>
#include <QButtonGroup>
#include <QStandardPaths>
#include <QDebug>
#include <QStringListModel>
#include <QStackedLayout>

#include "validators/tablenamevalidator.h"

#include "dialogs/createTable/presenter/createtablepresenter.h"

#include "dialogs/createTable/firststepwidget.h"
#include "dialogs/createTable/secondstepwidget.h"
#include "dialogs/createTable/thirdstepview/thirdstepwidget.h"

enum ActionType
{
    ImportRowAsColumns=0,
    ImportColumnsAsRow=1,
    CopyTable=2,
    LoadFromXls=3,
    CreateEmptyTable=4,
};

class CreateTableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateTableDialog(IDatabaseMediator *iRequestMaker, QWidget *parent);
    ~CreateTableDialog();
private:
    void CreatePresenter(IDatabaseMediator *iRequestMaker);
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnSetThirdStepWidget(int index, bool state);
    void OnAcceptButtonClicked();
public:
    QString SqlQueryCreateTable() const;
    QString SqlQueryFillTable() const;
private:
    QString SqlColumnProp(const QString &columnName) const;
private:
    CreateTablePresenter *m_presenter;
    ActionType m_currentActionType;
private:
    QVBoxLayout *m_mainLayouyt;

    FirstStepWidget *m_firstStepWidget;
    SecondStepWidget *m_secondStepWidget;
    ThirdStepWidget *m_thirdStepWidget;

    QHBoxLayout *m_footerLayout;
    QPushButton *m_acceptButton;
    QPushButton *m_rejectButton;
};

#endif // CREATETABLE_H
