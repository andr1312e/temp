#ifndef THIRDSTEPWIDGET_H
#define THIRDSTEPWIDGET_H

#include <QLabel>
#include <QStackedLayout>
#include <QWidget>

#include "createanemptytablewidget.h"
#include "importtablefromxslwidget.h"

class ThirdStepWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThirdStepWidget(QWidget *parent);
    ~ThirdStepWidget();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnSetVisibleStepWidget(bool state);
public:
    void SetWorkWidget(int index);
    //Для пустой таблицы
    bool IsHasRows(){return m_createEmptyTableWidget->IsHasRows();};
    bool IsHasColumns(){return m_createEmptyTableWidget->IsHasColumns();};
    QStringList GetAllRowNames(){return m_createEmptyTableWidget->GetAllRowNames();};
    QStringList GetAllColumnsNames(){return m_createEmptyTableWidget->GetAllColumnsNames();};
    //для XLS
private:

    QVBoxLayout *m_mainLayout;

    QHBoxLayout *m_headerLayout;
    QLabel *m_thirdStepLabel;
    QPushButton *m_thirdStepShowHideButton;

    QStackedLayout *m_workWidgetLayout;
    CreateAnEmptyTableWidget *m_createEmptyTableWidget;
    ImportTableFromXslWidget *m_importTableFromXlsWidget;

};

#endif // THIRDSTEPWIDGET_H
