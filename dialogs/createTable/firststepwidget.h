#ifndef FIRSTSTEPWIDGET_H
#define FIRSTSTEPWIDGET_H

#include <QButtonGroup>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class FirstStepWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FirstStepWidget(QWidget *parent);
    ~FirstStepWidget();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
Q_SIGNALS:
    void ToSetThirdStepWidget(int index, bool state);
private Q_SLOTS:
    void OnSetVisibleStateWidget(bool checked);
private:
    QVBoxLayout *m_mainLayout;

    QHBoxLayout *m_headerLayout;
    QLabel *m_firstStepLabel;
    QPushButton *m_firstStepShowHideButton;
    QButtonGroup *m_buttonGroup;
    QRadioButton *m_importRowsNamesAsAColumnsFromAnotherTableRadio;
    QRadioButton *m_importColumnsNamesAsARowsFromAnotherTableRadio;
    QRadioButton *m_makeCopyRadio;
    QRadioButton *m_loadTableFromXlsFileRadio;
    QRadioButton *m_createAnEmptyTableRadio;
};

#endif // FIRSTSTEPWIDGET_H
