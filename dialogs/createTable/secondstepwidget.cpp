#include "secondstepwidget.h"

SecondStepWidget::SecondStepWidget(CreateTablePresenter *presenter, QWidget *parent)
    : QWidget(parent)
    , m_presenter(presenter)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

SecondStepWidget::~SecondStepWidget()
{
    delete m_childrenLayout;
    delete m_headerLayout;
    delete m_middleLayout;
    delete m_footerLayout;
    delete m_mainLayout;

    delete m_secondStepLabel;
    delete m_secondStepShowHideButton;
    delete m_tableNameLabel;
    delete m_tableMainName;
    delete m_validator;
    delete m_addChildrenTable;

    for(AddRelationTableWidget* widget: qAsConst(m_childrenList))
    {
        delete widget;
    }
    delete m_scrollAreaWidgetContents;
    delete m_childrensArea;

    delete m_returnedNameLabel;
    delete m_returnedNameValue;
}

void SecondStepWidget::InitUI()
{
    m_mainLayout =new QVBoxLayout();

    m_headerLayout=new QHBoxLayout();
    m_secondStepLabel=new QLabel();
    m_secondStepShowHideButton=new QPushButton();

    m_middleLayout=new QHBoxLayout();
    m_tableNameLabel=new QLabel();
    m_tableMainName=new QLineEdit();
    m_validator=new TableNameValidator(this);
    m_addChildrenTable=new QPushButton();

    m_childrensArea=new QScrollArea();
    m_scrollAreaWidgetContents=new QWidget();
    m_childrenLayout=new QVBoxLayout();

    m_footerLayout=new QHBoxLayout();
    m_returnedNameLabel=new QLabel();
    m_returnedNameValue=new QLabel();
}

void SecondStepWidget::InsertWidgetsIntoLayouts()
{
    m_headerLayout->addWidget(m_secondStepLabel, 0, Qt::AlignLeft);
    m_headerLayout->addWidget(m_secondStepShowHideButton, 0, Qt::AlignRight);

    m_middleLayout->addWidget(m_tableNameLabel);
    m_middleLayout->addWidget(m_tableMainName);
    m_middleLayout->addWidget(m_addChildrenTable);

    m_mainLayout->addLayout(m_headerLayout);
    m_mainLayout->addLayout(m_middleLayout);

    m_scrollAreaWidgetContents->setLayout(m_childrenLayout);
    m_childrensArea->setWidget(m_scrollAreaWidgetContents);

    m_mainLayout->addWidget(m_childrensArea);

    m_footerLayout->addWidget(m_returnedNameLabel, 0, Qt::AlignLeft);
    m_footerLayout->addWidget(m_returnedNameValue, 0, Qt::AlignRight);

    m_mainLayout->addLayout(m_footerLayout);

    setLayout(m_mainLayout);
}

void SecondStepWidget::FillUI()
{
    m_secondStepLabel->setText(QStringLiteral("Шаг 2: Введите название таблицы:"));
    m_secondStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    m_secondStepShowHideButton->setCheckable(true);
    m_secondStepShowHideButton->setChecked(true);
    m_secondStepShowHideButton->setFlat(true);

    m_tableNameLabel->setText(QStringLiteral("Введите имя таблицы:"));
    m_tableMainName->setValidator(m_validator);

    m_addChildrenTable->setText(QStringLiteral("Добавить таблицу ребенка..."));
    m_addChildrenTable->setToolTip(QStringLiteral("откуда данные берем"));

    m_childrensArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_childrensArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_childrensArea->setWidgetResizable(true);

    m_returnedNameLabel->setText(QStringLiteral("Итоговое имя таблицы:"));
}

void SecondStepWidget::ConnectObjects()
{
    connect(m_addChildrenTable, &QPushButton::clicked, this, &SecondStepWidget::OnAddNewRelationshipTable);
    connect(m_secondStepShowHideButton, &QPushButton::clicked, this, &SecondStepWidget::OnSetVisibleStepWidget);
    connect(m_tableMainName, &QLineEdit::textChanged, this, &SecondStepWidget::OnTableNameChanged);
}

void SecondStepWidget::OnAddNewRelationshipTable()
{
    AddRelationTableWidget *const newRelationshipWidget=new AddRelationTableWidget(m_presenter->GetAllTablesList(), this);
    connect(newRelationshipWidget, &AddRelationTableWidget::ToChangedTableName, this, &SecondStepWidget::OnChildrenTableChecked);
    m_childrenList.append(newRelationshipWidget);

    m_childrenLayout->insertWidget(m_childrenLayout->count()-1, newRelationshipWidget);
    m_childrensArea->ensureWidgetVisible(m_scrollAreaWidgetContents);
    repaint();
}

void SecondStepWidget::OnChildrenTableChecked()
{
    AddRelationTableWidget* widget=qobject_cast<AddRelationTableWidget*>(sender());
    if(widget!=Q_NULLPTR)
    {
        for (AddRelationTableWidget* widgetInList: m_childrenList)
        {
            if(widgetInList!=widget)
            {
                if(!widgetInList->GetRelationTableText().isEmpty() && widgetInList->GetRelationTableText()==widget->GetRelationTableText())
                {
                    widget->ResetComboBox();
                    return;
                }
            }
        }
        OnTableNameChanged(m_tableMainName->text());
    }
}

void SecondStepWidget::OnTableNameChanged(const QString &name)
{
    if (name.isEmpty())
    {
        m_returnedNameValue->clear();
    }
    else
    {
        QString resultName=name + QStringLiteral(" <- ");
        bool childrenIsEmpty=true;
        for (AddRelationTableWidget* const  widgetInList: m_childrenList)
        {
            if(!widgetInList->GetRelationTableText().isEmpty())
            {
                resultName+=' '+widgetInList->GetRelationTableText();
                childrenIsEmpty=false;
            }
        }
        if(childrenIsEmpty)
        {
            resultName+=QStringLiteral(" NULL");
        }
        m_returnedNameValue->setText(resultName);
    }
}

void SecondStepWidget::OnSetVisibleStepWidget(bool state)
{
    m_tableNameLabel->setVisible(state);
    m_tableMainName->setVisible(state);
    m_addChildrenTable->setVisible(state);
    m_childrensArea->setVisible(state);
    m_returnedNameValue->setVisible(state);
    m_returnedNameLabel->setVisible(state);
    if(state)
    {
        m_secondStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    }
    else
    {
        m_secondStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/down-arrow.png")));
    }
}
