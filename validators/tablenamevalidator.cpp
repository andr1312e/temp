#include "tablenamevalidator.h"

TableNameValidator::TableNameValidator(QObject *parent)
    :QValidator(parent)
{

}

TableNameValidator::~TableNameValidator()
{

}

QValidator::State TableNameValidator::validate(QString &text, int &pos) const
{
    Q_UNUSED(pos);
    for (const QChar &charecter:badCharecterList)
    {
        if (text.contains(charecter))
        {
          return QValidator::Invalid;
        }
    }
    return QValidator::Acceptable;
}
