#include "mytableview.h"

MyTableView::MyTableView(IMyTableModel * const iModel, const QString &tableName, QWidget *parent)
    : QTableView(parent)
    , m_tableName(tableName)
    , m_iModel(iModel)
{
    CreateHeader();
    ConnectObjects();
}

MyTableView::~MyTableView()
{

}

void MyTableView::CreateHeader()
{
    m_myHeaderView=new MyHeaderView(this);
    setHorizontalHeader(m_myHeaderView);
}

void MyTableView::ConnectObjects()
{
    connect(m_myHeaderView, &MyHeaderView::ToRightButtonClicked, this, &MyTableView::OnRightButtonClicked);
    connect(m_myHeaderView, &MyHeaderView::ToLeftButtonClicked, this, &MyTableView::OnLeftButtonClicked);
    connect(m_myHeaderView, &MyHeaderView::ToMidButtonClicked, this, &MyTableView::OnMidButtonClicked);
}

void MyTableView::OnRightButtonClicked(int logicalIndex)
{
    if(logicalIndex!=-1)
    {
        const QString columnName=model()->headerData(logicalIndex, Qt::Horizontal).toString();
        const int result=QMessageBox::information(this, QStringLiteral("Удалить колонку ") +  columnName + QStringLiteral(" из таблицы?"), tr("Вы хотите её удалить?"), QMessageBox::Yes | QMessageBox::No);
        if(QMessageBox::Yes==result)
        {
            m_iModel->RemoveColumn(columnName);
        }
    }
}

void MyTableView::OnLeftButtonClicked(int logicalIndex)
{
    if (logicalIndex==-1)
    {
        QStringList allColumntList;
        for (int i=0; i<this->model()->columnCount(); i++)
        {
            allColumntList.append(this->model()->headerData(i, Qt::Horizontal).toString());
        }
        CreateNewColumnDialog dialog(m_tableName, allColumntList, this);
        if(dialog.exec()==QDialog::Accepted)
        {
            const QString newColumnName=dialog.GetNewColumnName();
            const QString type=dialog.GetColumnType();
            if (type==QStringLiteral("Логическое значение"))
            {
                const bool initBoolValue=dialog.GetBoolDefaultValue();
                m_iModel->AddColumn(newColumnName, initBoolValue);
            }
            else
            {
                if(type==QStringLiteral("Целое число"))
                {
                    const int initValue=dialog.GetDefaultValueForNotBoolType().toInt();
                    m_iModel->AddColumn(newColumnName, initValue);
                }
                else
                {
                    if(type==QStringLiteral("Дробное число"))
                    {
                        const int initValue=dialog.GetDefaultValueForNotBoolType().toDouble();
                        m_iModel->AddColumn(newColumnName, initValue);
                    }
                    else
                    {

                    }
                }
            }
        }
    }
    else
    {
        bool isOkPressed;
        const QString oldText=this->model()->headerData(logicalIndex, Qt::Horizontal).toString();
        const QString  newColumnName=  QInputDialog::getText(this, QStringLiteral("Изменить значение с ") +  oldText + QStringLiteral(" на другое "), tr("Ведите новое значение:"), QLineEdit::Normal, oldText, &isOkPressed, Qt::WindowFlags(), Qt::ImhDigitsOnly);
        if(isOkPressed)
        {
            this->model()->setHeaderData(logicalIndex,Qt::Horizontal, newColumnName);
        }
    }
}

void MyTableView::OnMidButtonClicked(int logicalIndex)
{
//    const QModelIndex firstColumnIndex=model()->index(0, headerIndex);
    if(logicalIndex!=-1)
    {
       const QModelIndex firstRowIndex=model()->index(1, logicalIndex);
       const QVariant::Type indexType=firstRowIndex.data(Qt::DisplayRole).type();
       switch (indexType) {
       case QVariant::Invalid:
           break;
       case QVariant::Bool:
       {

           break;
       }
       case QVariant::Int:
           break;
       case QVariant::UInt:
           break;
       case QVariant::LongLong:
           break;
       case QVariant::ULongLong:
           break;
       case QVariant::Double:
           break;
       case QVariant::Char:
           break;
       case QVariant::Map:
           break;
       case QVariant::List:
           break;
       case QVariant::String:
           break;
       case QVariant::StringList:
           break;
       case QVariant::ByteArray:
           break;
       case QVariant::BitArray:
           break;
       case QVariant::Date:
           break;
       case QVariant::Time:
           break;
       case QVariant::DateTime:
           break;
       case QVariant::Url:
           break;
       case QVariant::Locale:
           break;
       case QVariant::Rect:
           break;
       case QVariant::RectF:
           break;
       case QVariant::Size:
           break;
       case QVariant::SizeF:
           break;
       case QVariant::Line:
           break;
       case QVariant::LineF:
           break;
       case QVariant::Point:
           break;
       case QVariant::PointF:
           break;
       case QVariant::RegExp:
           break;
       case QVariant::RegularExpression:
           break;
       case QVariant::Hash:
           break;
       case QVariant::EasingCurve:
           break;
       case QVariant::Uuid:
           break;
       case QVariant::ModelIndex:
           break;
       case QVariant::PersistentModelIndex:
           break;
       case QVariant::LastCoreType:
           break;
       case QVariant::Font:
           break;
       case QVariant::Pixmap:
           break;
       case QVariant::Brush:
           break;
       case QVariant::Color:
           break;
       case QVariant::Palette:
           break;
       case QVariant::Image:
           break;
       case QVariant::Polygon:
           break;
       case QVariant::Region:
           break;
       case QVariant::Bitmap:
           break;
       case QVariant::Cursor:
           break;
       case QVariant::KeySequence:
           break;
       case QVariant::Pen:
           break;
       case QVariant::TextLength:
           break;
       case QVariant::TextFormat:
           break;
       case QVariant::Matrix:
           break;
       case QVariant::Transform:
           break;
       case QVariant::Matrix4x4:
           break;
       case QVariant::Vector2D:
           break;
       case QVariant::Vector3D:
           break;
       case QVariant::Vector4D:
           break;
       case QVariant::Quaternion:
           break;
       case QVariant::PolygonF:
           break;
       case QVariant::Icon:
           break;
       case QVariant::SizePolicy:
           break;
       case QVariant::UserType:
           break;
       case QVariant::LastType:
           break;

       }
    }


}
