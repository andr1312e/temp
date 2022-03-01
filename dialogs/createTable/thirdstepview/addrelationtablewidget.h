#ifndef ADDRELATIONTABLEWIDGET_H
#define ADDRELATIONTABLEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>

class AddRelationTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddRelationTableWidget(const QStringList &allTables, QWidget *parent);
    ~AddRelationTableWidget();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI(const QStringList &allTables);
    void ConnectObjects();
Q_SIGNALS:
    void ToChangedTableName();
public:
    QString GetRelationTableText() {return m_tableComboBox->currentText();};
    void UpdateAllTables(const QStringList &allTables);
    void ResetComboBox();
private:
    QHBoxLayout *m_mainLayout;
    QLabel *m_label;
    QComboBox *m_tableComboBox;
};

#endif // ADDRELATIONTABLEWIDGET_H
