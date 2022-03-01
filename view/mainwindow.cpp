#include "view/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CreateObjects();
    CreateUI();
    InsertWidgetsIntoLayoutsAndMainWindow();
    FillUI();
    ConnectObjects();
}

MainWindow::~MainWindow()
{
    delete m_statusBar;
}

void MainWindow::CreateObjects()
{
    m_mediatorRepository=QSharedPointer<MediatorRepository>(new MediatorRepository());
}

void MainWindow::CreateUI()
{
    m_toolBar=new ToolBar(m_mediatorRepository, this);
    m_statusBar=new QStatusBar(this);
    QDockWidget *m_dockWidget=new QDockWidget("MyDock", this);
    m_label=new QLabel("fdsafd");
    m_dockWidget->setWidget(m_label);
    m_dockWidgetList.append(m_dockWidget);
}

void MainWindow::InsertWidgetsIntoLayoutsAndMainWindow()
{
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, m_toolBar);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockWidgetList.first());
    setStatusBar(m_statusBar);
}

void MainWindow::FillUI()
{
    QMainWindow::setWindowTitle(QStringLiteral("Редактирование таблиц. Подключения нет. Нажмите на кнопку подключится к бд"));
    OnStatusBar(QStringLiteral("Сперва подключитесь к бд, слева сверху"));
    showMaximized();
}

void MainWindow::ConnectObjects()
{
    connect(m_toolBar, &ToolBar::ToOpenTable, this, &MainWindow::OnOpenTable);
}

void MainWindow::OnStatusBar(const QString &message)
{
    m_statusBar->showMessage(message);
}

void MainWindow::OnOpenTable(const QString &tableName)
{
    TableWidget *const widget=new TableWidget(m_mediatorRepository->GetTableMediator(), tableName, this);
    m_dockWidgetList.append(widget);
    addDockWidget(Qt::LeftDockWidgetArea, widget);
    widget->show();
}


