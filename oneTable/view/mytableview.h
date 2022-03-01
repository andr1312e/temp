#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include <QMouseEvent>
#include <QModelIndex>
#include <QHeaderView>
#include <QDebug>
#include <QInputDialog>

#include "oneTable/model/imytablemodel.h"

#include "oneTable/myheaderview.h"

#include "oneTable/dialogs/createnewcolumndialog.h"

class MyTableView : public QTableView
{
    Q_OBJECT
public:
    MyTableView(IMyTableModel * const iModel, const QString &tableName, QWidget *parent);
    ~MyTableView();
private:
    void CreateHeader();
    void ConnectObjects();
private Q_SLOTS:
    void OnRightButtonClicked(int logicalIndex);
    void OnLeftButtonClicked(int logicalIndex);
    void OnMidButtonClicked(int logicalIndex);
private:
    const QString m_tableName;
    IMyTableModel * const m_iModel;
    MyHeaderView * m_myHeaderView;
};

#endif // MYTABLEVIEW_H
