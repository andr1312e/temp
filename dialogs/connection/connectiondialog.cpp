#include "connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint)

{
    CreateUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
    OnUpdateAllDriversList();
}

ConnectionDialog::~ConnectionDialog()
{
    delete m_mainLayout;
    delete m_sqlDatabaseDriverLabel;
    delete m_sqlDatabaseDriverComboBox;
    delete m_refreshSqlDatabaseDriverButton;

    delete m_hostNameLabel;
    delete m_hostNameValue;
    delete m_databasePortLabel;
    delete m_databasePortValue;
    delete m_databaseNameLabel;
    delete m_databaseNameValue;
    delete m_userNameLabel;
    delete m_userNameValue;
    delete m_passwordLabel;
    delete m_passwordValue;
    delete m_connectButton;
    delete m_errorMessageLabel;
}

void ConnectionDialog::CreateUI()
{
    m_mainLayout=new QGridLayout(this);

    m_sqlDatabaseDriverLabel=new QLabel();
    m_sqlDatabaseDriverComboBox=new QComboBox();
    m_refreshSqlDatabaseDriverButton=new QPushButton();

    m_hostNameLabel=new QLabel();
    m_hostNameValue=new QLineEdit();
    m_databasePortLabel=new QLabel();
    m_databasePortValue=new QLineEdit();
    m_databaseNameLabel=new QLabel();
    m_databaseNameValue=new QLineEdit();
    m_userNameLabel=new QLabel();
    m_userNameValue=new QLineEdit();
    m_passwordLabel=new QLabel();
    m_passwordValue=new QLineEdit();
    m_connectButton=new QPushButton();
    m_errorMessageLabel=new QLabel();
}

void ConnectionDialog::InsertWidgetsIntoLayouts()
{
    m_mainLayout->addWidget(m_sqlDatabaseDriverLabel, 0, 0);
    m_mainLayout->addWidget(m_sqlDatabaseDriverComboBox, 0, 1);
    m_mainLayout->addWidget(m_refreshSqlDatabaseDriverButton, 1, 0, 1, -1);

    m_mainLayout->addWidget(m_hostNameLabel, 2, 0);
    m_mainLayout->addWidget(m_hostNameValue, 2, 1);

    m_mainLayout->addWidget(m_databasePortLabel, 3, 0);
    m_mainLayout->addWidget(m_databasePortValue, 3, 1);

    m_mainLayout->addWidget(m_databaseNameLabel, 4, 0);
    m_mainLayout->addWidget(m_databaseNameValue, 4, 1);

    m_mainLayout->addWidget(m_userNameLabel, 5, 0);
    m_mainLayout->addWidget(m_userNameValue, 5, 1);

    m_mainLayout->addWidget(m_passwordLabel, 6, 0);
    m_mainLayout->addWidget(m_passwordValue, 6, 1);

    m_mainLayout->addWidget(m_connectButton, 7, 0, 1, -1);
    m_mainLayout->addWidget(m_errorMessageLabel, 8, 0, 1, -1);
}

void ConnectionDialog::FillUI()
{
    m_sqlDatabaseDriverLabel->setText(QStringLiteral("Список дров БД:"));

    m_sqlDatabaseDriverComboBox->setEditable(false);
    m_refreshSqlDatabaseDriverButton->setText(QStringLiteral("Обновить список дров"));
    m_refreshSqlDatabaseDriverButton->setToolTip(QStringLiteral("Запрашиваем список установленных драйверов бд у QSqlDatabase::drivers()"));

    m_hostNameLabel->setText(QStringLiteral("хост"));
    m_hostNameLabel->setToolTip(QStringLiteral("Скорее всего localhost"));
    m_hostNameValue->setText(QStringLiteral("localhost"));
    m_databasePortLabel->setText(QStringLiteral("порт"));
    m_databasePortValue->setText(QStringLiteral("5432"));
    m_databaseNameLabel->setText(QStringLiteral("Имя бд"));
    m_databaseNameValue->setText(QStringLiteral("postgres"));
    m_userNameLabel->setText(QStringLiteral("имя юзера"));
    m_userNameValue->setText(QStringLiteral("postgres"));
    m_passwordLabel->setText(QStringLiteral("пароль"));
    m_passwordValue->setText(QStringLiteral("user1234"));

    m_connectButton->setText(QStringLiteral("Подключится к БД"));
}

void ConnectionDialog::ConnectObjects()
{
    connect(m_refreshSqlDatabaseDriverButton, &QPushButton::clicked, this, &ConnectionDialog::OnUpdateAllDriversList);
    connect(m_sqlDatabaseDriverComboBox, &QComboBox::currentTextChanged, this, &ConnectionDialog::OnDatabaseDriverChanged);
    connect(m_connectButton, &QPushButton::clicked, this, &ConnectionDialog::accept);
}

void ConnectionDialog::OnDatabaseDriverChanged(const QString &databaseDriverName)
{
    if(m_databaseDriverNameToDatabaseName.contains(databaseDriverName))
    {
        const QString &databaseName=m_databaseDriverNameToDatabaseName.value(databaseDriverName).first;
        m_connectButton->setText(QStringLiteral("Подключится к БД ")+ databaseName);
    }
    else
    {
        m_connectButton->setText(QStringLiteral("Подключится к БД ")+ databaseDriverName);
    }
}

void ConnectionDialog::OnUpdateAllDriversList()
{
    m_sqlDatabaseDriverComboBox->clear();
    const QStringList &allDrivers=QSqlDatabase::drivers();
    m_sqlDatabaseDriverComboBox->addItems(allDrivers);
}

void ConnectionDialog::accept()
{
    if (!m_sqlDatabaseDriverComboBox->currentText().isEmpty()&&!m_hostNameValue->text().isEmpty()&& !m_databasePortValue->text().isEmpty() && !m_databaseNameValue->text().isEmpty() && !m_userNameValue->text().isEmpty() && !m_passwordValue->text().isEmpty())
    {
        QDialog::accept();
    }
    else
    {
        m_errorMessageLabel->setText(QStringLiteral("Ошибка, есть пустая строка!"));
        return;
    }
}

QStringList ConnectionDialog::GetAllConnectionDialogData()
{
    QStringList connectionData;
    connectionData << m_sqlDatabaseDriverComboBox->currentText();
    connectionData << m_hostNameValue->text();
    connectionData << m_databasePortValue->text();
    connectionData << m_databaseNameValue->text();
    connectionData << m_userNameValue->text();
    connectionData << m_passwordValue->text();
    return  connectionData;
}
