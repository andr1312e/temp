#ifndef VIEW_DATABASETABLEWIDGET_H
#define VIEW_DATABASETABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QDockWidget>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

#include "oneTable/model/mytablemodel.h"

#include "model-interface/itablemediator.h"

#include "oneTable/delegate/tabledelegate.h"

#include "oneTable/view/mytableview.h"

class TableWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit TableWidget(ITableMediator * requestMaker, const QString &tableName, QWidget *parent);
    ~TableWidget();
private:
    void CreateModel();
    void CreateDelegate();
    void CreateUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
Q_SIGNALS:

private Q_SLOTS:
    void OnUpdateTable();
public:
    const QString &GetTableName()   { return m_tableName; };
private:
    ITableMediator *const m_tableMediator;
    const QString m_tableName;
    MyTableModel *m_tableModel;
private:
    QWidget *m_parentWidget;

    QVBoxLayout *m_mainLayout;

    QHBoxLayout *m_toolsLayout;
    QPushButton *m_updateTableButton;
    QLabel *m_searchLabel;
    QLineEdit *m_fromIdLineEdit;
    QLabel *m_searchToLabel;
    QLineEdit *m_toIdLineEdit;


    TableDelegate *m_tableDelegate;
    MyTableView *m_tableView;
};

#endif // VIEW_DATABASETABLEWIDGET_H
