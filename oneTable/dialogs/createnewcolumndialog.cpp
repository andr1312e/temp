#include "createnewcolumndialog.h"

CreateNewColumnDialog::CreateNewColumnDialog(const QString &tableName, const QStringList &columnNames, QWidget *parent)
    : QDialog(parent)
    , m_tableName(tableName)
    , m_allColumnNames(columnNames)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

CreateNewColumnDialog::~CreateNewColumnDialog()
{
    delete m_mainLayout;

    delete m_addFieldlabel;
    delete m_newColumnNameLabel;
    delete m_newColumnLineEditName;
    delete m_newColumnNameType;
    delete m_fieldType;
    delete m_defaultValueLabel;
    delete m_boolDefaultValue;
    delete m_otherDefaultValues;
    delete m_okButton;
}

void CreateNewColumnDialog::InitUI()
{
    m_mainLayout=new QVBoxLayout(this);
    m_addFieldlabel=new QLabel();
    m_newColumnNameLabel=new QLabel();
    m_newColumnLineEditName=new QLineEdit();

    m_newColumnNameType=new QLabel();
    m_fieldType=new QComboBox();

    m_defaultValueLabel=new QLabel();
    m_boolDefaultValue=new QComboBox();
    m_otherDefaultValues=new QLineEdit();

    m_okButton=new QPushButton();

    m_tableNameValidator=new TableNameValidator(this);
}

void CreateNewColumnDialog::InsertWidgetsIntoLayouts()
{
    m_mainLayout->addWidget(m_addFieldlabel);
    m_mainLayout->addWidget(m_newColumnNameLabel);
    m_mainLayout->addWidget(m_newColumnLineEditName);
    m_mainLayout->addWidget(m_newColumnNameType);
    m_mainLayout->addWidget(m_fieldType);
    m_mainLayout->addWidget(m_defaultValueLabel);
    m_mainLayout->addWidget(m_boolDefaultValue);
    m_mainLayout->addWidget(m_otherDefaultValues);
    m_mainLayout->addWidget(m_okButton);
}

void CreateNewColumnDialog::FillUI()
{
    setWindowTitle(QStringLiteral("Добавить новую колонку для таблицы: ")+ m_tableName);
    m_addFieldlabel->setText(QStringLiteral("Добавить столбец справа:"));

    m_newColumnNameLabel->setText(QStringLiteral("Значения поля:"));
    m_newColumnNameType->setText(QStringLiteral("Тип поля:"));

    m_newColumnLineEditName->setValidator(m_tableNameValidator);

    m_fieldType->addItems({QStringLiteral("Логическое значение"), QStringLiteral("Целое число"), QStringLiteral("Дробное число"), QStringLiteral("Строка"), QStringLiteral("Формула")});
    m_fieldType->setEditable(false);

    m_defaultValueLabel->setText(QStringLiteral("Значение по умолчанию для поля:"));
    m_boolDefaultValue->addItems({QStringLiteral("Да"), QStringLiteral("Нет")});
    m_boolDefaultValue->setEditable(false);
    m_otherDefaultValues->setVisible(false);
    m_okButton->setText(QStringLiteral("Применить"));

    resize(400, this->height());
}

void CreateNewColumnDialog::ConnectObjects()
{
    connect(m_okButton, &QPushButton::clicked, this, &CreateNewColumnDialog::OnOkButtonClicked);
    connect(m_fieldType, QOverload<int>::of(&QComboBox::activated), this, &CreateNewColumnDialog::OnColumnTypeChanged);
}

void CreateNewColumnDialog::OnOkButtonClicked()
{
    const QString newColumnName=m_newColumnLineEditName->text();
    if (newColumnName.isEmpty())
    {
        QMessageBox::information(this, "Не ввели имя столбца...", "Надо его ввести");
        return;
    }
    for (const QString &columnName: m_allColumnNames)
    {
        if(columnName==newColumnName)
        {
            QMessageBox::information(this, "Строка с таким именем уже имеется...", "Строка с таким именем существует");
            return;
        }
        else
        {
            if(!m_fieldType->currentText().isEmpty()&&m_fieldType->currentText()==QStringLiteral("Целое число"))
            {
                bool canConvert=false;
                m_otherDefaultValues->text().toInt(&canConvert);
                if (!canConvert)
                {
                    QMessageBox::information(this, "Не можем преобразовать в целое число значение по умолчанию...", "Измените значение");
                    return;
                }
            }
            else
            {
                if(!m_fieldType->currentText().isEmpty()&&m_fieldType->currentText()==QStringLiteral("Дробное число"))
                {
                    bool canConvert=false;
                    m_otherDefaultValues->text().toDouble(&canConvert);
                    if (!canConvert)
                    {
                        if(m_otherDefaultValues->text().contains(','))
                        {
                            QMessageBox::information(this, "Не можем преобразовать в дробное число значение по умолчанию...", "Вы ввели запятую вместо точки");
                            return;
                        }
                        else
                        {
                            QMessageBox::information(this, "Не можем преобразовать в дробное число значение по умолчанию...", "Введите число еще раз, проверьте символы пробел");
                            return;
                        }
                    }
                }
            }
        }

    }
    accept();
}

void CreateNewColumnDialog::OnColumnTypeChanged(int index)
{
    if(index==0)
    {
        m_boolDefaultValue->setVisible(true);
        m_otherDefaultValues->setVisible(false);
    }
    else
    {
        m_boolDefaultValue->setVisible(false);
        m_otherDefaultValues->setVisible(true);
    }
}
