#ifndef CROSSWIDGET_H
#define CROSSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>

class CrossWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrossWidget(QWidget *parent, bool isChecked);
    ~CrossWidget();
    bool GetIsChecked() {return m_isChecked; };
protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public:
    static void DrawCross(QPainter *painter, const QRect &rect);
private:
    bool m_isChecked;
};

#endif // CROSSWIDGET_H
