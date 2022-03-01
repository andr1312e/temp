#include "importtablefromxslwidget.h"

ImportTableFromXslWidget::ImportTableFromXslWidget(QWidget *parent)
    : QWidget(parent)
{
    InitUI();
    InsertWidgetsIntoLayouts();
    FillUI();
    ConnectObjects();
}

ImportTableFromXslWidget::~ImportTableFromXslWidget()
{

}

void ImportTableFromXslWidget::InitUI()
{
    m_mainLayout=new QVBoxLayout();
    m_importedFileName=new QLabel();
    m_importedFileSelectButton=new QPushButton();
    m_exportedTableColumnsLabel=new QLabel();
    m_importedFromFileTableColumnsNamesList=new QListView();

}

void ImportTableFromXslWidget::InsertWidgetsIntoLayouts()
{
    m_mainLayout->addWidget(m_importedFileName);
    m_mainLayout->addWidget(m_importedFileSelectButton);
    m_mainLayout->addWidget(m_exportedTableColumnsLabel);
    m_mainLayout->addWidget(m_importedFromFileTableColumnsNamesList);
    setLayout(m_mainLayout);
}

void ImportTableFromXslWidget::FillUI()
{
    m_importedFileName->setText(QStringLiteral("Имя файла не выбрано"));
    m_importedFileSelectButton->setText(QStringLiteral("Нажмите для выбора файла"));
    m_exportedTableColumnsLabel->setText(QStringLiteral("Имена колонок импортируемой таблицы:"));

}

void ImportTableFromXslWidget::ConnectObjects()
{
    connect(m_importedFileSelectButton, &QPushButton::clicked, this, &ImportTableFromXslWidget::OnXlsFileOpen);

}

void ImportTableFromXslWidget::OnXlsFileOpen()
{
    const QString fileName=QFileDialog::getOpenFileName(this, QStringLiteral("Добавление файла таблицы:"), QDir::homePath());
    if(!fileName.isEmpty())
    {
        QXlsx::Document xlsx(fileName, this);
        const QStringList sheetNames=xlsx.sheetNames();
        if (!sheetNames.isEmpty())
        {
            if(sheetNames.count()>2)
            {
                qDebug()<< "Обработка 2  более таблиц не реализована";
            }
            QXlsx::Worksheet * firstSheet=static_cast<QXlsx::Worksheet*>(xlsx.sheet(sheetNames.first()));
            if(Q_NULLPTR!=firstSheet)
            {
                QStringList allCellNames;
                const int columntCount=firstSheet->dimension().lastColumn();
                for (int i=1; i<=columntCount; ++i)
                {
                    QXlsx::Cell *cell=firstSheet->cellAt(1, i);
                    if(Q_NULLPTR!=cell)
                    {
                        qDebug()<<cell->cellType();
                        QString currentColumnName=QString::number(i)+QStringLiteral(". ");
                        if(QXlsx::Cell::StringType==cell->cellType() || QXlsx::Cell::SharedStringType==cell->cellType() )
                        {
                            currentColumnName.append(cell->value().toString());
                        }
                        allCellNames.append(currentColumnName);
                    }
                }
                QStringListModel *model=new QStringListModel(allCellNames, this);
                m_importedFromFileTableColumnsNamesList->setModel(model);

            }
        }
    }
    m_fileName=fileName;
}
