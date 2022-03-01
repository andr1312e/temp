#include "addrelationtablewidget.h"

AddRelationTableWidget::AddRelationTableWidget(const QStringList &allTables, QWidget *parent)
    : QWidget(parent)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI(allTables);
    ConnectObjects();
}

AddRelationTableWidget::~AddRelationTableWidget()
{
    delete m_mainLayout;
    delete m_label;
    delete m_tableComboBox;
}


void AddRelationTableWidget::InitUI()
{
    m_mainLayout=new QHBoxLayout();
    m_label=new QLabel();
    m_tableComboBox=new QComboBox();
}

void AddRelationTableWidget::InsertWidgetsIntoLayouts()
{
    m_mainLayout->addWidget(m_label);
    m_mainLayout->addWidget(m_tableComboBox);
    setLayout(m_mainLayout);
}

void AddRelationTableWidget::FillUI(const QStringList &allTables)
{
    m_label->setText(QStringLiteral("Таблица:"));
    m_tableComboBox->setEditable(false);
    UpdateAllTables(allTables);
}

void AddRelationTableWidget::ConnectObjects()
{
    connect(m_tableComboBox , QOverload<const QString&>::of(&QComboBox::activated), this, &AddRelationTableWidget::ToChangedTableName);
}

void AddRelationTableWidget::UpdateAllTables(const QStringList &allTables)
{
    m_tableComboBox->clear();
    m_tableComboBox->addItem(QStringLiteral());
    m_tableComboBox->addItems(allTables);
    ResetComboBox();
}

void AddRelationTableWidget::ResetComboBox()
{
    m_tableComboBox->setCurrentIndex(0);
}
