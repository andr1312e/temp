#include "toolbar.h"

ToolBar::ToolBar(const QSharedPointer<MediatorRepository> &mediatorRepository, QWidget *parent)
    :QToolBar(parent)
{
    CreatePresenter(mediatorRepository);
    CreateUI();
    InsertWidgetsIntoLayoutsToolBar();
    FillUI();
    ConnectObjects();
}

ToolBar::~ToolBar()
{
    delete m_connectToDatabase;
    delete m_disconnectFromDatase;

    delete m_tablesCountLabel;
    delete m_connectToTableLabel;
    delete m_allTablesComboBox;
    delete m_openTable;
    delete m_dropTable;
}

void ToolBar::CreatePresenter(const QSharedPointer<MediatorRepository> &mediatorRepository)
{
    m_presenter=new ToolBarPresenter(mediatorRepository, this);
}

void ToolBar::CreateUI()
{
    m_connectToDatabase=new QAction();
    m_disconnectFromDatase=new QAction();

    m_tablesCountLabel=new QLabel();
    m_connectToTableLabel=new QLabel();
    m_allTablesComboBox=new QComboBox();
    m_openTable=new QAction();
    m_dropTable=new QAction();
    m_createTable=new QAction();
}

void ToolBar::InsertWidgetsIntoLayoutsToolBar()
{
    addAction(m_connectToDatabase);
    addAction(m_disconnectFromDatase);
    addWidget(m_tablesCountLabel);
    addWidget(m_connectToTableLabel);
    addWidget(m_allTablesComboBox);
    addAction(m_openTable);
    addAction(m_dropTable);
    addAction(m_createTable);
}

void ToolBar::FillUI()
{
    m_connectToDatabase->setText(QStringLiteral("Подключится к бд "));
    m_disconnectFromDatase->setText(QStringLiteral("Отключится от бд "));
    m_disconnectFromDatase->setDisabled(true);

    m_tablesCountLabel->setText(QStringLiteral("Колличество таблиц: 0"));
    m_connectToTableLabel->setText(QStringLiteral(" Выберите таблицу: "));
    m_allTablesComboBox->setEditable(false);
    m_openTable->setText(QStringLiteral("открыть таблицу"));
    m_openTable->setDisabled(true);
    m_dropTable->setText(QStringLiteral("удалить таблицу"));
    m_dropTable->setDisabled(true);
    m_createTable->setText(QStringLiteral("Создать таблицу"));
    m_createTable->setDisabled(true);
    QWidget::setToolTip(QStringLiteral("Чтобы перетащить панель нажмите на две полоски и переведите курсор мыши в нужное место"));
}

void ToolBar::ConnectObjects()
{
    connect(m_connectToDatabase, &QAction::triggered, this, &ToolBar::OnConnectToDatabase);
    connect(m_disconnectFromDatase, &QAction::triggered, this, &ToolBar::OnDisconnectFromDatabase);
    connect(m_openTable, &QAction::triggered, this, &ToolBar::OnOpenTableInNewTab);
    connect(m_dropTable, &QAction::triggered, this, &ToolBar::OnDropTable);
    connect(m_createTable, &QAction::triggered, this, &ToolBar::OnCreateTable);
}

void ToolBar::OnConnectToDatabase()
{
    ConnectionDialog* const connectToDbDialog = new ConnectionDialog(this);
    if (QDialog::Accepted==connectToDbDialog->exec())
    {
        const QStringList params=connectToDbDialog->GetAllConnectionDialogData();
        Q_ASSERT(params.count()==6);
        const QString driverName=params.front();
        const QString hostName=params.at(1);
        const quint16 port=params.at(2).toUInt();
        const QString name=params.at(3);
        const QString userName=params.at(4);
        const QString password=params.at(5);
        QString connectionError;
        if (m_presenter->ConnectedToDb(driverName, hostName, port, name, userName, password, connectionError))
        {
            FillComboBoxWithTableList();
            SetButtonsEnabled(true);
            Q_EMIT ToStatusBar(QStringLiteral("Соединение установлено, работа доступна"));

        }
        else
        {
            Q_EMIT ToStatusBar(QStringLiteral("Соединение не установлено. Ошибка: ")+connectionError);
        }
    }
    else
    {
        m_allTablesComboBox->clear();
        SetButtonsEnabled(false);
    }
    delete connectToDbDialog;
}

void ToolBar::OnDisconnectFromDatabase()
{
    m_presenter->DisconnectFromDB();
    m_allTablesComboBox->clear();
    SetButtonsEnabled(false);
}

void ToolBar::OnOpenTableInNewTab()
{
    if(m_allTablesComboBox->count()==0)
    {
        FillComboBoxWithTableList();
        Q_EMIT ToStatusBar(QStringLiteral("Таблиц нет или произошла рассинхронизация"));
    }
    else
    {
        const QString tableName=m_allTablesComboBox->currentText();
        const QStringList allTables=m_presenter->GetAllTablesList();
        if(allTables.contains(tableName))
        {
            Q_EMIT ToOpenTable(tableName);
        }
        else
        {
            FillComboBoxWithTableList();
            Q_EMIT ToStatusBar(QStringLiteral("Таблица не может быть открыта. Так как ее уже нет ") + tableName + QStringLiteral(". Список таблиц был обновлен, проверьте таблицу еще раз"));
        }
    }
}

void ToolBar::OnDropTable()
{
    if(m_allTablesComboBox->count()==0)
    {
        return;
    }
    else
    {
        const QString tableName=m_allTablesComboBox->currentText();
        Q_EMIT ToDropTable(tableName);
    }
}

void ToolBar::OnCreateTable()
{
    CreateTableDialog createTableDialog(m_presenter->GetInterface(), this);
    if(QDialog::Accepted==createTableDialog.exec())
    {
        const QString sqlQueryTableCreate=createTableDialog.SqlQueryCreateTable();
        m_presenter->CreateTable(sqlQueryTableCreate);
        const QString sqlQueryTableFill=createTableDialog.SqlQueryFillTable();
        m_presenter->FillTablesByData(sqlQueryTableFill);
        FillComboBoxWithTableList();
    }
}

void ToolBar::FillComboBoxWithTableList()
{
    QSqlQueryModel *const tablesListModel=m_presenter->GetAllModelTablesList();
    m_allTablesComboBox->setModel(tablesListModel);
    m_tablesCountLabel->setText(QStringLiteral("Колличество таблиц: ")+ QString::number(m_allTablesComboBox->count()));
}

void ToolBar::SetButtonsEnabled(bool state)
{
    m_openTable->setEnabled(state);
    m_dropTable->setEnabled(state);
    m_createTable->setEnabled(state);
    m_disconnectFromDatase->setEnabled(state);
    m_connectToDatabase->setDisabled(state);
    m_allTablesComboBox->setEnabled(state);
}
