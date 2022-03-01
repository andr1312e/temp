#ifndef CREATE_TABLE_SECONDSTEPWIDGET_H
#define CREATE_TABLE_SECONDSTEPWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QScrollArea>

#include "validators/tablenamevalidator.h"

#include "presenter/createtablepresenter.h"

#include "dialogs/createTable/thirdstepview/addrelationtablewidget.h"

class SecondStepWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SecondStepWidget(CreateTablePresenter *presenter, QWidget *parent);
    ~SecondStepWidget();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();

private Q_SLOTS:
    void OnAddNewRelationshipTable();
    void OnChildrenTableChecked();
    void OnTableNameChanged(const QString &name);
    void OnSetVisibleStepWidget(bool state);
public:
    QString GetTableName(){return m_returnedNameValue->text();};
private:
    CreateTablePresenter * const m_presenter;
private:
    QVBoxLayout *m_mainLayout;

    QHBoxLayout *m_headerLayout;
    QLabel *m_secondStepLabel;
    QPushButton *m_secondStepShowHideButton;

    QHBoxLayout *m_middleLayout;
    QLabel *m_tableNameLabel;
    QLineEdit *m_tableMainName;
    TableNameValidator *m_validator;
    QPushButton *m_addChildrenTable;

    QScrollArea *m_childrensArea;
    QWidget *m_scrollAreaWidgetContents;
    QVBoxLayout *m_childrenLayout;

    QList<AddRelationTableWidget*> m_childrenList;

    QHBoxLayout *m_footerLayout;
    QLabel *m_returnedNameLabel;
    QLabel *m_returnedNameValue;
};

#endif // CREATE_TABLE_SECONDSTEPWIDGET_H
