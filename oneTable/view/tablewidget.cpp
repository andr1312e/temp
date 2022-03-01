#include "oneTable/view/tablewidget.h"

TableWidget::TableWidget(ITableMediator *requestMaker, const QString &tableName, QWidget *parent)
    : QDockWidget(parent)
    , m_tableMediator(requestMaker)
    , m_tableName(tableName)
{
    CreateModel();
    CreateDelegate();
    CreateUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

TableWidget::~TableWidget()
{
    if(m_tableModel!=Q_NULLPTR)
        delete m_tableModel;
}

void TableWidget::CreateModel()
{
    m_tableModel=new MyTableModel(m_tableMediator, m_tableName, this);
}

void TableWidget::CreateDelegate()
{
   m_tableDelegate=new TableDelegate(this);
}

void TableWidget::CreateUI()
{
    m_parentWidget=new QWidget();
    m_mainLayout=new QVBoxLayout();

    m_toolsLayout=new QHBoxLayout();
    m_updateTableButton=new QPushButton();
    m_searchLabel=new QLabel();
    m_fromIdLineEdit=new QLineEdit();
    m_searchToLabel=new QLabel();
    m_toIdLineEdit=new QLineEdit();

    m_tableView=new MyTableView(m_tableModel, m_tableName, this);
}

void TableWidget::InsertWidgetsIntoLayouts()
{
    m_toolsLayout->addWidget(m_updateTableButton);
    m_toolsLayout->addWidget(m_searchLabel);
    m_toolsLayout->addWidget(m_fromIdLineEdit);
    m_toolsLayout->addWidget(m_searchToLabel);
    m_toolsLayout->addWidget(m_toIdLineEdit);


    m_mainLayout->addLayout(m_toolsLayout);
    m_mainLayout->addWidget(m_tableView);

    m_parentWidget->setLayout(m_mainLayout);
    setWidget(m_parentWidget);
}

void TableWidget::FillUI()
{
    m_updateTableButton->setText(QStringLiteral("Обновить таблицу"));
    m_searchLabel->setText(QStringLiteral("Показывать начиная c номера: "));
    m_searchToLabel->setText(QStringLiteral(" до "));
    m_tableView->setItemDelegate(m_tableDelegate);
    m_tableView->setModel(m_tableModel);
    this->setWindowTitle(m_tableName);
}

void TableWidget::ConnectObjects()
{
    connect(m_updateTableButton, &QPushButton::clicked, this, &TableWidget::OnUpdateTable);
    connect(m_tableView, &QTableView::clicked, m_tableView, QOverload<const QModelIndex &>::of(&QTableView::edit));//перегрузка моуспресс и поиск индекса по позиции выдает фалл едитинг хз поч
}

void TableWidget::OnUpdateTable()
{

}
