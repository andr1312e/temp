#include "myheaderview.h"

MyHeaderView::MyHeaderView(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent)
{

}

MyHeaderView::~MyHeaderView()
{

}

void MyHeaderView::mouseReleaseEvent(QMouseEvent *event)
{

    if(Qt::LeftButton==event->button())
    {
        const int index=logicalIndexAt(event->pos());
        Q_EMIT ToLeftButtonClicked(index);
    }
    else
    {
        if(Qt::RightButton==event->button())
        {
            const int index=logicalIndexAt(event->pos());
            Q_EMIT ToRightButtonClicked(index);
        }
        else
        {
            const int index=logicalIndexAt(event->pos());
            Q_EMIT ToMidButtonClicked(index);
        }
    }
}

QSize MyHeaderView::sizeHint() const
{
    const QSize originalSize = QHeaderView::sizeHint();
    if(originalSize.width()>0 || originalSize.height()>0)
    {
        return originalSize;
    }
    else
    {
        //Тут отображаем если в таблице нет ничего
        QStyleOptionHeader optionHeader;
        //Класс QStyleOptionHeader используется
        //для описания параметров отрисовки заголовка.
        //QStyleOptionHeader содержит всю информацию,
        //которая необходима функциям QStyle
        //для рисования области заголовка представлений элементов,
        //стрелки сортировки заголовка и метки заголовка.
        initStyleOption(&optionHeader);
        return style()->sizeFromContents(QStyle::CT_HeaderSection, &optionHeader, QSize(), this);
    }
}
