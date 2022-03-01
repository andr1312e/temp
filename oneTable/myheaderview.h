#ifndef MYHEADERVIEW_H
#define MYHEADERVIEW_H

#include <QHeaderView>
#include <QMouseEvent>

class MyHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    MyHeaderView(QWidget *parent);
    ~MyHeaderView();
Q_SIGNALS:
    void ToLeftButtonClicked( int logicalIndex);
    void ToRightButtonClicked(int logicalIndex);
    void ToMidButtonClicked(int logicalIndex);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif // MYHEADERVIEW_H
