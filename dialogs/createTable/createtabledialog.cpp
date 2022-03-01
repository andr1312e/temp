#include "createtabledialog.h"

//#include <type_traits>

CreateTableDialog::CreateTableDialog(IDatabaseMediator *iRequestMaker, QWidget *parent)
    : QDialog(parent, Qt::WindowMaximizeButtonHint| Qt::WindowCloseButtonHint)
{
    CreatePresenter(iRequestMaker);
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

CreateTableDialog::~CreateTableDialog()
{

}

void CreateTableDialog::CreatePresenter(IDatabaseMediator *iRequestMaker)
{
    m_presenter=new CreateTablePresenter(iRequestMaker, this);
}

void CreateTableDialog::InitUI()
{
    m_mainLayouyt=new QVBoxLayout();

    m_firstStepWidget=new FirstStepWidget(this);
    m_secondStepWidget=new SecondStepWidget(m_presenter, this);
    m_thirdStepWidget=new ThirdStepWidget(this);

    m_footerLayout=new QHBoxLayout();
    m_acceptButton=new QPushButton();
    m_rejectButton=new QPushButton();
}

void CreateTableDialog::InsertWidgetsIntoLayouts()
{
    m_mainLayouyt->addWidget(m_firstStepWidget);
    m_mainLayouyt->addWidget(m_secondStepWidget);
    m_mainLayouyt->addWidget(m_thirdStepWidget);

    m_footerLayout->addWidget(m_acceptButton);
    m_footerLayout->addWidget(m_rejectButton);
    m_mainLayouyt->addLayout(m_footerLayout);
    setLayout(m_mainLayouyt);
}

void CreateTableDialog::FillUI()
{
    setWindowTitle(QStringLiteral("Создаем таблицу"));

    m_acceptButton->setText(QStringLiteral("Создать таблицу"));
    m_rejectButton->setText(QStringLiteral("Выйти без сохранения"));
}

void CreateTableDialog::ConnectObjects()
{
    connect(m_firstStepWidget, &FirstStepWidget::ToSetThirdStepWidget, this , &CreateTableDialog::OnSetThirdStepWidget);
    connect(m_acceptButton, &QPushButton::clicked, this, &CreateTableDialog::OnAcceptButtonClicked);
    connect(m_rejectButton, &QPushButton::clicked, this, &QDialog::reject);
}

void CreateTableDialog::OnSetThirdStepWidget(int index, bool state)
{
    //state нужен что бы radiobutton который анчекд не обрабатывать
    if(state)
    {
        m_thirdStepWidget->SetWorkWidget(index-3);
        m_currentActionType=static_cast<ActionType>(index);
    }
}

void CreateTableDialog::OnAcceptButtonClicked()
{
    if (m_secondStepWidget->GetTableName().isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("Название таблицы не введено"), QStringLiteral("Сделайте 2 шаг"));
    }
    else
    {
        accept();
    }
}

QString CreateTableDialog::SqlQueryCreateTable() const
{
    QString sqlQueryCreate=QStringLiteral("CREATE TABLE \"")+ m_secondStepWidget->GetTableName() + QStringLiteral("\" ( ");
    switch (m_currentActionType)
    {
    case ImportRowAsColumns:
        break;
    case ImportColumnsAsRow:
        break;
    case CopyTable:
        break;
    case LoadFromXls:
        break;
    case CreateEmptyTable:
    {
        if (m_thirdStepWidget->IsHasColumns())
        {
            const QStringList columnsNames=m_thirdStepWidget->GetAllColumnsNames();
            for (int i=0; i<columnsNames.count()-1; ++i)
            {
                sqlQueryCreate.append(columnsNames.at(i) + QStringLiteral(" ")+ SqlColumnProp(columnsNames.at(i)) + QStringLiteral(", "));
            }
            sqlQueryCreate.append(columnsNames.back() + QStringLiteral(" ")+ SqlColumnProp(columnsNames.back()));
            sqlQueryCreate.append(QStringLiteral(" );"));
        }
        else
        {
            qFatal("%s", QStringLiteral("Недопустимый код").toUtf8().constData());
        }
        break;
    }
    default:
    {
        qFatal("%s", QStringLiteral("Не реализовано").toUtf8().constData());
        break;
    }
    }
    return sqlQueryCreate;
}

QString CreateTableDialog::SqlQueryFillTable() const
{
    //здесь проверяем: если нет строк возвращаем пустой. Дальше идет проверка на емпти!
    QString sqlQueryFill;
    switch (m_currentActionType)
    {
    case ImportRowAsColumns:
        break;
    case ImportColumnsAsRow:
        break;
    case CopyTable:
        break;
    case LoadFromXls:
        break;
    case CreateEmptyTable:
    {
        sqlQueryFill=QStringLiteral("INSERT INTO \"")+ m_secondStepWidget->GetTableName() + QStringLiteral("\" (name) VALUES ");
        if (m_thirdStepWidget->IsHasRows())
        {
            const QStringList rowNames=m_thirdStepWidget->GetAllRowNames();
            for (int i=0; i<rowNames.count()-1; ++i)
            {
                sqlQueryFill.append(QStringLiteral("( '")+rowNames.at(i)+ QStringLiteral("' ), "));
            }
            sqlQueryFill.append(QStringLiteral("( '")+rowNames.back() + QStringLiteral("');"));
        }
    }
    default:
    {
        qFatal("%s", QStringLiteral("Не реализовано").toUtf8().constData());
        break;
    }
    }
    return sqlQueryFill;
}

QString CreateTableDialog::SqlColumnProp(const QString &columnName) const
{
    if(columnName.count()>3)
    {
        if (columnName.at(1)==QChar('_'))
        {
            const QChar prefix=columnName.front();
            if(prefix=='b')
            {
                return QStringLiteral(" boolean NOT NULL DEFAULT false");
            }
            if(prefix=='v')
            {
                return QStringLiteral(" real NOT NULL DEFAULT 0.0 ");
            }
            if(prefix=='s')
            {
                return QStringLiteral(" varchar(50) NOT NULL ");
            }
            if(prefix=='r')
            {
                return QStringLiteral(" real NOT NULL DEFAULT 0 ");
            }
            if(prefix=='k')
            {
                return QStringLiteral(" real NOT NULL DEFAULT 0 ");
            }
            if(prefix=='f')
            {
                return QStringLiteral(" real NOT NULL DEFAULT 0 ");
            }
            else
            {
                qFatal("%s", QStringLiteral("Неизвестный префикс у элемента").toUtf8().constData());
            }
        }
        else
        {
            if(QStringLiteral("name")==columnName)
            {
                return QStringLiteral(" varchar(50) NOT NULL");
            }
            else
            {
                qFatal("%s", QStringLiteral("У элемента на 2 позиции [1] нет _, ошибка в коде").toUtf8().constData());
            }
        }
    }
    else
    {
        qFatal("%s", QStringLiteral("Колличество элементов а строке недостаточно, ошибка в коде").toUtf8().constData());
    }
}

