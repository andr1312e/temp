#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QDebug>
#include <QPainter>
#include <QCheckBox>
#include <QSqlRelationalDelegate>

#include "oneTable/delegate/crosswidget.h"

class TableDelegate : public QSqlRelationalDelegate
{
public:
    TableDelegate(QObject *parent);
    ~TableDelegate();

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
        virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:


};

#endif // TABLEDELEGATE_H

