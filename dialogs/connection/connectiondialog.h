#ifndef CONNECTTODBDIALOG_H
#define CONNECTTODBDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QGridLayout>

#include "model/databasedrivers.h"

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionDialog(QWidget *parent);
    ~ConnectionDialog();
private:
    void CreateUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnDatabaseDriverChanged(const QString &databaseDriverName);
    void OnUpdateAllDriversList();
public Q_SLOTS:
    void accept();
public:
    QStringList GetAllConnectionDialogData();
private:
    QGridLayout *m_mainLayout;
    QLabel *m_sqlDatabaseDriverLabel;
    QComboBox *m_sqlDatabaseDriverComboBox;
    QPushButton *m_refreshSqlDatabaseDriverButton;

    QLabel *m_hostNameLabel;
    QLineEdit *m_hostNameValue;
    QLabel *m_databasePortLabel;
    QLineEdit *m_databasePortValue;
    QLabel *m_databaseNameLabel;
    QLineEdit *m_databaseNameValue;
    QLabel *m_userNameLabel;
    QLineEdit *m_userNameValue;
    QLabel *m_passwordLabel;
    QLineEdit *m_passwordValue;

    QPushButton *m_connectButton;
    QLabel *m_errorMessageLabel;
};

#endif // CONNECTTODBDIALOG_H
