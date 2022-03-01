#include "model-interface/itablemediator.h"

void ITableMediator::RegisterQSqlDatabase(const QSqlDatabase &database)
{
    m_db=database;
}

QString ITableMediator::GetStringInRowFromMessage(const QSqlRecord &record, const int &numberOfField) const
{
    if(record.count()>numberOfField)
    {
        if(QVariant::String==record.value(numberOfField).type())
        {
            return record.value(numberOfField).toString();
        }
        else
        {
            qFatal("%s", QString(Q_FUNC_INFO + QStringLiteral(" Тип текущей записи не строка, а должен быть строкой")  +  QStringLiteral( " тип записи: ") + QString::number(record.value(numberOfField).type())).toUtf8().constData());
        }
    }
    else
    {
        qFatal("%s", QString(Q_FUNC_INFO + QStringLiteral("Колличество записей в запросе больше чем колличество строк")  +  QStringLiteral( " колличество строк: ") + QString::number(numberOfField) +  QStringLiteral( " колличество записей в запросе: ") + QString::number(record.count())).toUtf8().constData());
    }
}

QStringList ITableMediator::GetStringListFromRowMessage(const QSqlRecord &record) const
{
    QStringList respondsList;
    for (int i=0; i<record.count(); ++i)
    {
        respondsList<<GetStringInRowFromMessage(record, i);
    }
    return respondsList;
}
