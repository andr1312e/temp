#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject *parent)
    :QSqlRelationalDelegate(parent)
{

}

TableDelegate::~TableDelegate()
{

}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(QMetaType::Bool==index.model()->data(index).userType())
    {
        if (true==index.model()->data(index).toBool())
        {
            CrossWidget::DrawCross(painter, option.rect);
        }
        else
        {
            painter->fillRect(option.rect, Qt::red);
        }
    }
    else
    {
        if (QMetaType::Int==index.model()->data(index).userType())
        {
            painter->fillRect(option.rect, Qt::cyan);
        }
        else
        {
            painter->fillRect(option.rect, Qt::green);
        }
        QSqlRelationalDelegate::paint(painter, option, index);
    }
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QVariant currentIndexData=index.model()->data(index);
    if(QMetaType::Bool==currentIndexData.userType())
    {
        qDebug()<< "create cross widget ";
        CrossWidget* const crossWidget = new CrossWidget(parent, currentIndexData.toBool());
        return crossWidget;
    }
    else
    {
        return QSqlRelationalDelegate::createEditor(parent, option, index);
    }
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    if(QMetaType::Bool==index.model()->data(index).userType())
//    {
//        QPainter painter(editor);
//        if (true==index.model()->data(index).toBool())
//        {
//        }
//        else
//        {
//            painter.fillRect(editor->rect(), Qt::white);
//        }
//    }
//    else
//    {
        QSqlRelationalDelegate::setEditorData(editor, index);
        //    }
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const QVariant currentIndexData=index.model()->data(index);
    if(QMetaType::Bool==currentIndexData.userType())
    {
        qDebug()<< "setModelData cross widget";
        CrossWidget* crossWidget=qobject_cast<CrossWidget*>(editor);
        if(crossWidget!=Q_NULLPTR)
        {
            model->setData(index, crossWidget->GetIsChecked());
        }
    }
    else
    {
        return QSqlRelationalDelegate::setModelData(editor, model, index);
    }
}


