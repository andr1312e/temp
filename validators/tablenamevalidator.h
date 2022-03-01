#ifndef TABLENAMEVALIDATOR_H
#define TABLENAMEVALIDATOR_H
#include <QValidator>

class TableNameValidator: public QValidator
{
public:
    TableNameValidator(QObject *parent);
    ~TableNameValidator();
public:
    virtual State validate(QString &text, int &pos) const Q_DECL_OVERRIDE;
private:
    const QVarLengthArray<QChar, 29> badCharecterList = {
        '\\',
        '/',
        '`',
        ':',
        '&',
        '*',
        '?',
        '\'',
        '<',
        '>',
        '`',
        '(',
        ')',
        ':',
        ';',
        '\'',
        ' ',
        ']',
        '[',
        '.',
        '!',
        '@',
        '#',
        '$',
        '%',
        '^',
        '=',
        '+',
        '~'
    };
};

#endif // TABLENAMEVALIDATOR_H
