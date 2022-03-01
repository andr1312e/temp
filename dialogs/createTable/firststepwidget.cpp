#include "firststepwidget.h"

FirstStepWidget::FirstStepWidget(QWidget *parent)
    : QWidget(parent)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

FirstStepWidget::~FirstStepWidget()
{
    delete m_headerLayout;
    delete m_mainLayout;

    delete m_firstStepLabel;
    delete m_firstStepShowHideButton;
    delete m_buttonGroup;
    delete m_importRowsNamesAsAColumnsFromAnotherTableRadio;
    delete m_importColumnsNamesAsARowsFromAnotherTableRadio;
    delete m_makeCopyRadio;
    delete m_loadTableFromXlsFileRadio;
    delete m_createAnEmptyTableRadio;
}

void FirstStepWidget::InitUI()
{
    m_mainLayout=new QVBoxLayout();

    m_headerLayout=new QHBoxLayout();

    m_firstStepLabel=new QLabel();
    m_firstStepShowHideButton=new QPushButton();

    m_buttonGroup=new QButtonGroup();
    m_importRowsNamesAsAColumnsFromAnotherTableRadio=new QRadioButton();
    m_importColumnsNamesAsARowsFromAnotherTableRadio=new QRadioButton();
    m_makeCopyRadio=new QRadioButton();
    m_loadTableFromXlsFileRadio=new QRadioButton();
    m_createAnEmptyTableRadio=new QRadioButton();
}

void FirstStepWidget::InsertWidgetsIntoLayouts()
{
    m_headerLayout->addWidget(m_firstStepLabel, 0, Qt::AlignLeft);
    m_headerLayout->addWidget(m_firstStepShowHideButton, 0, Qt::AlignRight);

    m_mainLayout->addLayout(m_headerLayout);
    m_mainLayout->addWidget(m_importRowsNamesAsAColumnsFromAnotherTableRadio);
    m_mainLayout->addWidget(m_importColumnsNamesAsARowsFromAnotherTableRadio);
    m_mainLayout->addWidget(m_makeCopyRadio);
    m_mainLayout->addWidget(m_loadTableFromXlsFileRadio);
    m_mainLayout->addWidget(m_createAnEmptyTableRadio);

    setLayout(m_mainLayout);
}

void FirstStepWidget::FillUI()
{
    m_buttonGroup->addButton(m_importRowsNamesAsAColumnsFromAnotherTableRadio, 0);
    m_buttonGroup->addButton(m_importColumnsNamesAsARowsFromAnotherTableRadio, 1);
    m_buttonGroup->addButton(m_makeCopyRadio, 2);
    m_buttonGroup->addButton(m_loadTableFromXlsFileRadio, 3);
    m_buttonGroup->addButton(m_createAnEmptyTableRadio, 4);

    m_firstStepLabel->setText(QStringLiteral("Шаг 1: Выберите действие: (Один раз)"));
    m_firstStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    m_firstStepShowHideButton->setCheckable(true);
    m_firstStepShowHideButton->setChecked(true);
    m_importRowsNamesAsAColumnsFromAnotherTableRadio->setText(QStringLiteral("Импортировать строки как столбцы из другой таблицы"));
    m_importColumnsNamesAsARowsFromAnotherTableRadio->setText(QStringLiteral("Импортировать столбцы как строки из другой таблицы"));
    m_makeCopyRadio->setText(QStringLiteral("Сделать копию таблицы:"));
    m_loadTableFromXlsFileRadio->setText(QStringLiteral("Загрузить таблицу из ХLS файла(EXEL):"));
    m_loadTableFromXlsFileRadio->setToolTip(QStringLiteral("Файл должен быть правильно отформатирован!"));
    m_createAnEmptyTableRadio->setText(QStringLiteral("Создать пустую таблицу с заданным шаблоном:"));
    m_createAnEmptyTableRadio->setChecked(true);

//    QFrame::setFrameStyle(QFrame::Box | QFrame::Sunken);
//    this->setF(2);
}

void FirstStepWidget::ConnectObjects()
{
    connect(m_firstStepShowHideButton, &QPushButton::clicked, this, &FirstStepWidget::OnSetVisibleStateWidget);
    connect(m_buttonGroup, QOverload<int, bool>::of(&QButtonGroup::buttonToggled), this, &FirstStepWidget::ToSetThirdStepWidget);
}

void FirstStepWidget::OnSetVisibleStateWidget(bool checked)
{
    for (QAbstractButton * const button:m_buttonGroup->buttons())
    {
        button->setVisible(checked);
    }
    if(checked)
    {
        m_firstStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    }
    else
    {
       m_firstStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/down-arrow.png")));
    }
}
