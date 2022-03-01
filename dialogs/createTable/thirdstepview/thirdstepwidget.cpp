#include "thirdstepwidget.h"

ThirdStepWidget::ThirdStepWidget(QWidget *parent)
    : QWidget(parent)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

ThirdStepWidget::~ThirdStepWidget()
{
    delete m_headerLayout;
    delete m_workWidgetLayout;
    delete m_mainLayout;

    delete m_thirdStepLabel;
    delete m_thirdStepShowHideButton;

    delete m_createEmptyTableWidget;
    delete m_importTableFromXlsWidget;
}

void ThirdStepWidget::InitUI()
{
    m_mainLayout=new QVBoxLayout();

    m_headerLayout=new QHBoxLayout();
    m_thirdStepLabel=new QLabel();
    m_thirdStepShowHideButton=new QPushButton();

    m_workWidgetLayout=new QStackedLayout();

    m_createEmptyTableWidget=new CreateAnEmptyTableWidget(this);
    m_importTableFromXlsWidget=new ImportTableFromXslWidget(this);
}

void ThirdStepWidget::InsertWidgetsIntoLayouts()
{
    m_headerLayout->addWidget(m_thirdStepLabel, 0, Qt::AlignLeft);
    m_headerLayout->addWidget(m_thirdStepShowHideButton, 0, Qt::AlignRight);

    m_mainLayout->addLayout(m_headerLayout);

    m_workWidgetLayout->addWidget(m_createEmptyTableWidget);
    m_workWidgetLayout->addWidget(m_importTableFromXlsWidget);

    m_mainLayout->addLayout(m_workWidgetLayout);
    setLayout(m_mainLayout);
}

void ThirdStepWidget::FillUI()
{
    m_thirdStepLabel->setText(QStringLiteral("Шаг 3: произведите начальную инициализацию: (Допускается многократно) \n Следует добавить колонки отношения и колонку со значением (одну и более)"));
    m_thirdStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    m_thirdStepShowHideButton->setCheckable(true);
    m_thirdStepShowHideButton->setChecked(true);
    m_thirdStepShowHideButton->setFlat(true);
}

void ThirdStepWidget::ConnectObjects()
{
    connect(m_thirdStepShowHideButton, &QPushButton::clicked, this, &ThirdStepWidget::OnSetVisibleStepWidget);
}

void ThirdStepWidget::OnSetVisibleStepWidget(bool state)
{
    m_workWidgetLayout->currentWidget()->setVisible(state);
    if(state)
    {
        m_thirdStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/up-arrows.png")));
    }
    else
    {
        m_thirdStepShowHideButton->setIcon(QIcon(QStringLiteral(":/icons/down-arrow.png")));
    }
}

void ThirdStepWidget::SetWorkWidget(int index)
{
  if (index>=m_workWidgetLayout->count())
  {
      qFatal("%s", QStringLiteral("Вышли за допустимые пределы").toUtf8().constData());
  }
  else
  {
      m_workWidgetLayout->setCurrentIndex(index);
  }
}
