#ifndef CREATEANEMPTYTABLEWIDGET_H
#define CREATEANEMPTYTABLEWIDGET_H

#include <QCheckBox>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QStackedLayout>
#include <QMessageBox>
#include <QStackedWidget>

class CreateAnEmptyTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateAnEmptyTableWidget(QWidget *parent);
    ~CreateAnEmptyTableWidget();
private:
    void InitModel();
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnMakeAction();
    void OnClearAllColumns();
    void OnClearAllRows();
    void OnCountComboBoxChanged(int count);
    void OnShowSubWidget(int index);
    void OnPlaceToPutChanged(int index);
public:
    bool IsHasColumns() const;
    bool IsHasRows() const;
    QStringList GetAllColumnsNames() const;
    QStringList GetAllRowNames() const;
private:
    bool FormIsCorrect() const;
    QStringList MakeListOfItem(bool isAddingColumn) const;
    QStringList AdditionalColumnsToRealVal() const;
    void MakeActionWithStringList(QStringListModel *model, const QStringList &items);

    void AppendItemsToModel(const QStringList &itemsWantToInsert, QStringListModel *model);
    void RemoveItemsFromModel(const QStringList &itemsWantToDelete, QStringListModel *model);
    void AddStringToModel(const QString &string, QStringListModel *model);

    QString Prefix() const;

private:
    QStringListModel *m_columnModel;
    QStringListModel *m_rowModel;
private:
    QVBoxLayout *m_mainLayout;

    QLabel *m_additionalColumnsLabel;
    QHBoxLayout *m_actionHeaderLayout;

    QComboBox *m_itemCountComboBox;
    QComboBox *m_placeToPutComboBox;
    QComboBox *m_actionDoCombBox;

    QStackedLayout *m_stackedActionLayout;

    QWidget *m_addMoreColumnsWidget;
    QHBoxLayout *m_addMoreColumnsLayout;
    QLabel *m_columnNameLabel;
    QLineEdit *m_manyNames;
    QLabel *m_fromValueLabel;
    QSpinBox *m_firstValueSpinBox;
    QLabel *m_toValueLabel;
    QSpinBox *m_secondValueSpinBox;

    QWidget *m_addOneColumnWidget;
    QHBoxLayout *m_addOneColumnLayout;
    QLabel *m_addOneRowLabel;
    QLineEdit *m_oneName;

    QHBoxLayout *m_footerLayout;
    QLabel *m_columnTypeLabel;
    QComboBox *m_typeComboBox;

    QWidget *m_additionalColumnsSubWidget;
    QVBoxLayout *m_additionalColumnsLayout;
    QCheckBox *m_addFormulasToValueCB;
    QCheckBox *m_addWeightCoefficentToValCB;
    QCheckBox *m_addBorderCoefficentToValCB;
    QComboBox *m_borderCoefficentCountCB;

    QPushButton *m_actionButton;
    QPushButton *m_clearAllRowsButton;
    QPushButton *m_clearAllColumnsButton;

    QGridLayout *m_resultListLayout;

    QLabel *m_tableRowListLabel;
    QLabel *m_tableColumnListLabel;

    QListView *m_tableColumnsList;
    QListView *m_tableRowList;
};

#endif // CREATEANEMPTYTABLEWIDGET_H
