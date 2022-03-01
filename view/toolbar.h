#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQueryModel>

#include "model/mediatorrepository.h"

#include "dialogs/connection/connectiondialog.h"
#include "dialogs/createTable/createtabledialog.h"

#include "presenter/toolbarpresenter.h"
#include "model-interface/itoolbarrequestmaker.h"

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(const QSharedPointer<MediatorRepository> &mediatorRepository, QWidget *parent);
    ~ToolBar();
private:
    void CreatePresenter(const QSharedPointer<MediatorRepository> &mediatorRepository);
    void CreateUI();
    void InsertWidgetsIntoLayoutsToolBar();
    void FillUI();
    void ConnectObjects();
Q_SIGNALS:
    void ToStatusBar(const QString &message);
    void ToOpenTable(const QString &tableName);
    void ToDropTable(const QString &tableName);
private Q_SLOTS:
    void OnConnectToDatabase();
    void OnDisconnectFromDatabase();
    void OnOpenTableInNewTab();
    void OnDropTable();
    void OnCreateTable();
private:
    void FillComboBoxWithTableList();
    void SetButtonsEnabled(bool state);
private:
    ToolBarPresenter *m_presenter=Q_NULLPTR;
private:
    QAction *m_connectToDatabase;
    QAction *m_disconnectFromDatase;

    QLabel *m_tablesCountLabel;
    QLabel *m_connectToTableLabel;
    QComboBox *m_allTablesComboBox;
    QAction *m_openTable;
    QAction *m_dropTable;
    QAction *m_createTable;
};

#endif // TOOLBAR_H
