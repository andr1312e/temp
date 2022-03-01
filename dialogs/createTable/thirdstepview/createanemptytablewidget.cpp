#include "createanemptytablewidget.h"

#include <QSizePolicy>

CreateAnEmptyTableWidget::CreateAnEmptyTableWidget(QWidget *parent)
    : QWidget(parent)
{
    InitModel();
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

CreateAnEmptyTableWidget::~CreateAnEmptyTableWidget()
{
    delete m_addMoreColumnsLayout;
    delete m_mainLayout;

    delete m_additionalColumnsLabel;


    delete m_placeToPutComboBox;
    delete m_actionDoCombBox;
    delete m_manyNames;
    delete m_fromValueLabel;
    delete m_firstValueSpinBox;
    delete m_toValueLabel;
    delete m_secondValueSpinBox;
    delete m_actionButton;
    delete m_clearAllColumnsButton;

    delete m_tableColumnsList;
}

void CreateAnEmptyTableWidget::InitModel()
{
    m_columnModel=new QStringListModel(this);
    m_rowModel=new QStringListModel(this);
}

void CreateAnEmptyTableWidget::InitUI()
{
    m_mainLayout=new QVBoxLayout(this);

    m_additionalColumnsLabel=new QLabel();

    m_actionHeaderLayout=new QHBoxLayout();
    m_placeToPutComboBox=new QComboBox();
    m_actionDoCombBox=new QComboBox();
    m_itemCountComboBox=new QComboBox();

    m_stackedActionLayout=new QStackedLayout();

    m_addMoreColumnsWidget=new QWidget();
    m_addMoreColumnsLayout=new QHBoxLayout();
    m_columnNameLabel=new QLabel();
    m_manyNames=new QLineEdit();
    m_fromValueLabel=new QLabel();
    m_firstValueSpinBox=new QSpinBox();
    m_toValueLabel=new QLabel();
    m_secondValueSpinBox=new QSpinBox();

    m_addOneColumnWidget=new QWidget();
    m_addOneColumnLayout=new QHBoxLayout();
    m_addOneRowLabel=new QLabel();
    m_oneName=new QLineEdit();

    m_footerLayout=new QHBoxLayout();
    m_columnTypeLabel=new QLabel();
    m_typeComboBox=new QComboBox();

    m_additionalColumnsSubWidget=new QWidget();
    m_additionalColumnsLayout=new QVBoxLayout();

    m_addFormulasToValueCB=new QCheckBox();
    m_addWeightCoefficentToValCB=new QCheckBox();
    m_addBorderCoefficentToValCB=new QCheckBox();
    m_borderCoefficentCountCB=new QComboBox();

    m_actionButton=new QPushButton();
    m_clearAllRowsButton=new QPushButton();
    m_clearAllColumnsButton=new QPushButton();

    m_resultListLayout=new QGridLayout();
    m_tableRowListLabel=new QLabel();
    m_tableColumnListLabel=new QLabel();

    m_tableColumnsList=new QListView();
    m_tableRowList=new QListView();
}

void CreateAnEmptyTableWidget::InsertWidgetsIntoLayouts()
{
    m_mainLayout->addWidget(m_additionalColumnsLabel);

    m_actionHeaderLayout->addWidget(m_itemCountComboBox);
    m_actionHeaderLayout->addWidget(m_placeToPutComboBox);
    m_actionHeaderLayout->addWidget(m_actionDoCombBox);

    m_mainLayout->addLayout(m_actionHeaderLayout);

    m_addMoreColumnsLayout->addWidget(m_columnNameLabel);
    m_addMoreColumnsLayout->addWidget(m_manyNames);
    m_addMoreColumnsLayout->addWidget(m_fromValueLabel);
    m_addMoreColumnsLayout->addWidget(m_firstValueSpinBox);
    m_addMoreColumnsLayout->addWidget(m_firstValueSpinBox);
    m_addMoreColumnsLayout->addWidget(m_toValueLabel);
    m_addMoreColumnsLayout->addWidget(m_secondValueSpinBox);
    m_addMoreColumnsWidget->setLayout(m_addMoreColumnsLayout);

    m_addOneColumnLayout->addWidget(m_addOneRowLabel);
    m_addOneColumnLayout->addWidget(m_oneName);
    m_addOneColumnWidget->setLayout(m_addOneColumnLayout);

    m_stackedActionLayout->addWidget(m_addOneColumnWidget);
    m_stackedActionLayout->addWidget(m_addMoreColumnsWidget);

    m_mainLayout->addLayout(m_stackedActionLayout);
    m_mainLayout->addWidget(m_columnTypeLabel);
    m_mainLayout->addWidget(m_typeComboBox);

    m_additionalColumnsLayout->addWidget(m_addFormulasToValueCB);
    m_additionalColumnsLayout->addWidget(m_addWeightCoefficentToValCB);
    m_additionalColumnsLayout->addWidget(m_addBorderCoefficentToValCB);
    m_additionalColumnsLayout->addWidget(m_borderCoefficentCountCB);
    m_additionalColumnsSubWidget->setLayout(m_additionalColumnsLayout);
    m_mainLayout->addWidget(m_additionalColumnsSubWidget);

    m_footerLayout->addWidget(m_actionButton);
    m_footerLayout->addWidget(m_clearAllRowsButton);
    m_footerLayout->addWidget(m_clearAllColumnsButton);

    m_mainLayout->addLayout(m_footerLayout);

    m_resultListLayout->addWidget(m_tableRowListLabel, 0, 0);
    m_resultListLayout->addWidget(m_tableColumnListLabel, 0, 1);

    m_resultListLayout->addWidget(m_tableRowList, 1, 0);
    m_resultListLayout->addWidget(m_tableColumnsList, 1, 1);



    m_mainLayout->addLayout(m_resultListLayout);
}

void CreateAnEmptyTableWidget::FillUI()
{

    m_additionalColumnsLabel->setText(QStringLiteral("В таблице:"));

    m_placeToPutComboBox->addItems(QStringList{QStringLiteral("колонку -> правая таб, горизонт"), QStringLiteral("строку <- слева, вериткальн")});
    m_placeToPutComboBox->setEditable(false);
    m_actionDoCombBox->addItems(QStringList({QStringLiteral("добавить"), QStringLiteral("удалить")}));
    m_actionDoCombBox->setEditable(false);
    m_itemCountComboBox->addItems(QStringList({QStringLiteral("Одну"), QStringLiteral("Много")}));
    m_itemCountComboBox->setEditable(false);

    m_columnNameLabel->setText(QStringLiteral("Имена колонок:"));
    m_fromValueLabel->setText(QStringLiteral(" c "));
    m_firstValueSpinBox->setMinimum(0);
    m_firstValueSpinBox->setMaximum(9999);
    m_toValueLabel->setText(QStringLiteral(" до "));
    m_secondValueSpinBox->setMinimum(1);
    m_secondValueSpinBox->setMaximum(9999);

    m_addOneRowLabel->setText(QStringLiteral("Имя одной колонки:"));

    m_columnTypeLabel->setText(QStringLiteral("Тип колонки: "));
    m_typeComboBox->addItems({QStringLiteral("булевский тип(отношение), по умол=ЛОЖЬ b_"), QStringLiteral("значение(веществ число), по умол=0 v_"), QStringLiteral("комментарий (строка), по умол=\"\" s_")});
    m_typeComboBox->setEditable(false);

    m_additionalColumnsSubWidget->hide();
    m_addFormulasToValueCB->setText(QStringLiteral("Добавить колонки формул (столько же сколько и колонок), формула пустая"));
    m_addWeightCoefficentToValCB->setText(QStringLiteral("Добавить колонки весов (столько же сколько и колонок), по умол=1"));
    m_addBorderCoefficentToValCB->setText(QStringLiteral("Добавить колонки границ. На одну колонку границ:, по умол=0"));
    m_borderCoefficentCountCB->addItems(QStringList({QStringLiteral("одно"), QStringLiteral("два"), QStringLiteral("три")}));
    m_borderCoefficentCountCB->setDisabled(true);

    m_actionButton->setText(QStringLiteral("Выполнить"));
    m_clearAllRowsButton->setText(QStringLiteral("Удалить все строки"));
    m_clearAllColumnsButton->setText(QStringLiteral("Удалить все колонки"));

    m_tableRowListLabel->setText(QStringLiteral("Список строк(текущий уровень):"));
    m_tableColumnListLabel->setText(QStringLiteral("Список колонок(уровень выше, кроме колонки ИМЯ) \n Первым идет префикс, его не надо удалять!:"));

    m_tableColumnsList->setModel(m_columnModel);
    AddStringToModel(QStringLiteral("name"), m_columnModel);
    m_tableRowList->setModel(m_rowModel);
    m_tableColumnsList->setSelectionMode( QAbstractItemView::ExtendedSelection );
    m_tableRowList->setSelectionMode( QAbstractItemView::ExtendedSelection );

    QSizePolicy policy;
    policy.setVerticalPolicy(QSizePolicy::Expanding);
    m_tableRowList->setSizePolicy(policy);
    m_tableColumnsList->setSizePolicy(policy);

}

void CreateAnEmptyTableWidget::ConnectObjects()
{
    connect(m_actionButton, &QPushButton::clicked, this, &CreateAnEmptyTableWidget::OnMakeAction);
    connect(m_clearAllColumnsButton, &QPushButton::clicked, this, &CreateAnEmptyTableWidget::OnClearAllColumns);
    connect(m_clearAllRowsButton, &QPushButton::clicked, this, &CreateAnEmptyTableWidget::OnClearAllRows);
    connect(m_itemCountComboBox, QOverload<int>::of(&QComboBox::activated), m_stackedActionLayout, &QStackedLayout::setCurrentIndex);
    connect(m_itemCountComboBox, QOverload<int>::of(&QComboBox::activated), this, &CreateAnEmptyTableWidget::OnCountComboBoxChanged);
    connect(m_typeComboBox, QOverload<int>::of(&QComboBox::activated), this, &CreateAnEmptyTableWidget::OnShowSubWidget);
    connect(m_addBorderCoefficentToValCB, &QCheckBox::toggled, m_borderCoefficentCountCB, &QWidget::setEnabled);
    connect(m_placeToPutComboBox, QOverload<int>::of(&QComboBox::activated), this, &CreateAnEmptyTableWidget::OnPlaceToPutChanged);
}

void CreateAnEmptyTableWidget::OnMakeAction()
{
    if(FormIsCorrect())
    {
        //сначала смотрим на то куда добавялем, от этого зависит префикс
        const bool isColumnAdding=m_placeToPutComboBox->currentIndex()==0;
        QStringList newItems=MakeListOfItem(isColumnAdding);
        if(isColumnAdding)
        {
            newItems.append(AdditionalColumnsToRealVal());
        }
        QStringListModel *currentModel;
        if(m_placeToPutComboBox->currentIndex()==0)
        {
            currentModel=m_columnModel;
        }
        else
        {
            currentModel=m_rowModel;
        }
        MakeActionWithStringList(currentModel, newItems);
    }
    else
    {
        QMessageBox::information(this, QStringLiteral("Левое значение больше чем правое"), QStringLiteral("Вы выбрали добавить много элементов. В строке имя у вас левое значение больше чем праворе"));
    }
}

void CreateAnEmptyTableWidget::OnClearAllColumns()
{
    m_columnModel->removeRows(1, m_columnModel->rowCount()-1);
}

void CreateAnEmptyTableWidget::OnClearAllRows()
{
    m_rowModel->removeRows(0, m_rowModel->rowCount());
}
QStringList AddAdditionalColumnsIfNeeded();
void CreateAnEmptyTableWidget::OnCountComboBoxChanged(int count)
{
    const int index=m_placeToPutComboBox->currentIndex();
    if(count==0)
    {
        m_placeToPutComboBox->clear();
        m_placeToPutComboBox->addItems(QStringList{QStringLiteral("колонку -> правая таб, горизонт"), QStringLiteral("строку <- слева, вериткальн")});
    }
    else
    {
        m_placeToPutComboBox->clear();
        m_placeToPutComboBox->addItems(QStringList{QStringLiteral("колонок -> правая таб, горизонт"), QStringLiteral("строк <- слева, вериткальн")});
    }
    m_placeToPutComboBox->setCurrentIndex(index);
}

void CreateAnEmptyTableWidget::OnShowSubWidget(int index)
{
    if(1==index)
    {
        m_additionalColumnsSubWidget->show();
    }
    else
    {
        m_additionalColumnsSubWidget->hide();
    }
    update();
}

void CreateAnEmptyTableWidget::OnPlaceToPutChanged(int index)
{
    if (index==0)
    {
        m_addOneRowLabel->setText(QStringLiteral("Имя одной колонки:"));
        m_columnNameLabel->setText(QStringLiteral("Имена колонок:"));
        m_columnTypeLabel->show();
        m_typeComboBox->show();
        OnShowSubWidget(m_typeComboBox->currentIndex());
    }
    else
    {
        m_addOneRowLabel->setText(QStringLiteral("Имя одной строки:"));
        m_columnNameLabel->setText(QStringLiteral("Имена строк:"));
        m_additionalColumnsSubWidget->hide();
        m_columnTypeLabel->hide();
        m_typeComboBox->hide();
    }
}

bool CreateAnEmptyTableWidget::IsHasColumns() const
{
    return m_columnModel->rowCount()>0;
}

bool CreateAnEmptyTableWidget::IsHasRows() const
{
    return m_rowModel->rowCount()>0;
}

QStringList CreateAnEmptyTableWidget::GetAllColumnsNames() const
{
    return m_columnModel->stringList();
}

QStringList CreateAnEmptyTableWidget::GetAllRowNames() const
{
    return m_rowModel->stringList();
}

bool CreateAnEmptyTableWidget::FormIsCorrect() const
{
    if (m_itemCountComboBox->currentIndex()==1)
    {
        const int firstVal=m_firstValueSpinBox->value();
        const int secondVal=m_secondValueSpinBox->value();
        return firstVal<secondVal;
    }
    return  true;
}

QStringList CreateAnEmptyTableWidget::MakeListOfItem(bool isAddingColumn) const
{
    QStringList listOfItems;
    if (m_itemCountComboBox->currentIndex()==0)//одну
    {
        if(isAddingColumn)
        {
            listOfItems.append(Prefix()+m_oneName->text());
        }
        else
        {
            listOfItems.append(m_oneName->text());
        }
    }
    else
    {
        const int valueBegin=m_firstValueSpinBox->value();
        const int valueEnd=m_secondValueSpinBox->value();
        QString columnName=m_manyNames->text();
        if(isAddingColumn)
        {
            columnName.prepend(Prefix());
        }
        for (int i=valueBegin; i<=valueEnd; ++i)
        {
            listOfItems<< columnName+QString::number(i);
        }
    }
    return listOfItems;
}

void CreateAnEmptyTableWidget::AppendItemsToModel(const QStringList &itemsWantToInsert, QStringListModel *model)
{
    for (const QString &itemToInsert: itemsWantToInsert)
    {
        QModelIndex index;
        for (int i=0; i<model->rowCount(); ++i)
        {
            if (model->index(i).data(Qt::DisplayRole).toString()==itemToInsert)
            {
                index=model->index(i);
                break;
            }
        }
        if(!index.isValid())
        {
            AddStringToModel(itemToInsert, model);
        }
    }
}

void CreateAnEmptyTableWidget::RemoveItemsFromModel(const QStringList &itemsWantToDelete, QStringListModel *model)
{
    for (const QString &itemToDelete: itemsWantToDelete)
    {
        QModelIndex index;
        for (int i=0; i<model->rowCount(); ++i)
        {
            if (itemToDelete==model->index(i).data(Qt::DisplayRole).toString())
            {
                index=model->index(i);
                break;
            }
        }
        if(index.isValid())
        {
            model->removeRow(index.row());
        }
    }
}

void CreateAnEmptyTableWidget::AddStringToModel(const QString &string, QStringListModel *model)
{
    model->insertRow(model->rowCount());
    const QModelIndex index=model->index(model->rowCount()-1);
    model->setData(index, string);
}

QString CreateAnEmptyTableWidget::Prefix() const
{
    const int index=m_typeComboBox->currentIndex();
    switch (index)
    {
    case 0:
    {
        return  QStringLiteral("b_");
    }
    case 1:
    {
        return  QStringLiteral("v_");
    }
    case 2:
    {
        return  QStringLiteral("s_");
    }
    }
    qFatal("%s", QStringLiteral("Неверный префикс, обновите список префиксов в методе").toUtf8().constData());
}

QStringList CreateAnEmptyTableWidget::AdditionalColumnsToRealVal() const
{
    //уже произведена проверка на то что строки
    QStringList appendedColumns;
    if(m_typeComboBox->currentIndex()==1)
    {
        if (m_itemCountComboBox->currentIndex()==0)//одну
        {
            if (m_addFormulasToValueCB->isChecked())
            {
                appendedColumns.append(QStringLiteral("f_")+m_oneName->text());
            }
            if (m_addWeightCoefficentToValCB->isChecked())
            {
                appendedColumns.append(QStringLiteral("w_")+m_oneName->text());
            }
            if (m_addBorderCoefficentToValCB->isChecked())
            {
                const int index=m_borderCoefficentCountCB->currentIndex();
                for (int i=0; i<index; ++i)
                {
                    appendedColumns.append('b'+QString::number(i)+'_'+m_oneName->text());
                }
            }
        }
        else
        {
            const int firstValue=m_firstValueSpinBox->value();
            const int secondValue=m_secondValueSpinBox->value();
            if (m_addFormulasToValueCB->isChecked())
            {
                for (int i=firstValue; i<=secondValue; ++i)
                {
                    appendedColumns.append(QStringLiteral("f_")+m_oneName->text()+QString::number(i));
                }
            }
            if (m_addWeightCoefficentToValCB->isChecked())
            {
                for (int i=firstValue; i<=secondValue; ++i)
                {
                    appendedColumns.append(QStringLiteral("w_")+m_oneName->text()+QString::number(i));
                }
            }
            if (m_addBorderCoefficentToValCB->isChecked())
            {
                for (int i=firstValue; i<=secondValue; ++i)
                {
                    const int index=m_borderCoefficentCountCB->currentIndex();
                    for (int j=0; j<index; ++j)
                    {
                        appendedColumns.append('b'+QString::number(j)+'_'+m_oneName->text()+QString::number(i));
                    }
                }
            }
        }
    }
    return  appendedColumns;
}

void CreateAnEmptyTableWidget::MakeActionWithStringList(QStringListModel *model, const QStringList &items)
{
    if(m_actionDoCombBox->currentIndex()==0)
    {
        AppendItemsToModel(items, model);
    }
    else
    {
        RemoveItemsFromModel(items, model);
    }
}
