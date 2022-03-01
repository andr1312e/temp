#ifndef CREATENEWCOLUMNDIALOG_H
#define CREATENEWCOLUMNDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "validators/tablenamevalidator.h"

class CreateNewColumnDialog : public QDialog
{
    Q_OBJECT
public:
    CreateNewColumnDialog(const QString &tableName, const QStringList &columnNames, QWidget *parent);
    ~CreateNewColumnDialog();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnOkButtonClicked();
    void OnColumnTypeChanged(int index);
public:
    QString GetNewColumnName(){return m_newColumnLineEditName->text();};
    QString GetColumnType(){return m_fieldType->currentText();};
    bool GetBoolDefaultValue(){return m_boolDefaultValue->currentText()==QStringLiteral("Да");};
    QString GetDefaultValueForNotBoolType(){return m_otherDefaultValues->text();};
private:
    const QString m_tableName;
    const QStringList &m_allColumnNames;
    TableNameValidator *m_tableNameValidator;
private:
    QVBoxLayout *m_mainLayout;
    QLabel *m_addFieldlabel;

    QLabel *m_newColumnNameLabel;
    QLineEdit *m_newColumnLineEditName;

    QLabel *m_newColumnNameType;
    QComboBox *m_fieldType;

    QLabel *m_defaultValueLabel;
    QComboBox *m_boolDefaultValue;
    QLineEdit *m_otherDefaultValues;

    QPushButton *m_okButton;

};

#endif // CREATENEWCOLUMNDIALOG_H
