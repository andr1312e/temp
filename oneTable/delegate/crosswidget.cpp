#include "crosswidget.h"

CrossWidget::CrossWidget(QWidget *parent, bool isChecked)
    : QWidget(parent)
    , m_isChecked(isChecked)
{

}

CrossWidget::~CrossWidget()
{
}

void CrossWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_isChecked)
    {
        DrawCross(&painter, event->rect());
    }
    else
    {
        painter.fillRect(event->rect(), Qt::white);
    }
}

void CrossWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<< "clicked was: " << m_isChecked;
    Q_UNUSED(event);
    if (m_isChecked)
    {
        m_isChecked=false;
    }
    else
    {
        m_isChecked=true;
    }
    update();
}

void CrossWidget::DrawCross(QPainter *painter, const QRect &rect)
{
    //отступы
    const int rectWidth=rect.width()/6;
    const int rectHeight=rect.height()/6;
    const QPoint firstLineMargin(rectWidth, rectHeight);
    const QPoint secondLineMargin(-rectWidth, +rectHeight);
    //рисуем крест х
    painter->drawLine(rect.topLeft()+firstLineMargin, rect.bottomRight()-firstLineMargin);
    painter->drawLine(rect.topRight()+secondLineMargin, rect.bottomLeft()-secondLineMargin);
}
