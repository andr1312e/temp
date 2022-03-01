#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QDockWidget>
#include <QLabel>
#include <QStatusBar>
#include <QSharedPointer>

#include "model/mediatorrepository.h"

#include "view/toolbar.h"
#include "oneTable/view/tablewidget.h"

#include "presenter/toolbarpresenter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent);
    ~MainWindow();
private:
    void CreateObjects();
    void CreateUI();
    void InsertWidgetsIntoLayoutsAndMainWindow();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnStatusBar(const QString &message);
    void OnOpenTable(const QString &tableName);
private:
    QSharedPointer<MediatorRepository> m_mediatorRepository;
    ToolBar *m_toolBar;

    QVector<QDockWidget *>m_dockWidgetList;
    QLabel *m_label;
    QStatusBar *m_statusBar;


};
#endif // VIEW_MAINWINDOW_H
