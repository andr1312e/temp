#ifndef IMPORTTABLEFROMXSLWIDGET_H
#define IMPORTTABLEFROMXSLWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QDebug>

#include "myLib/xlsx/xlsxdocument.h"
#include "myLib/xlsx/xlsxworksheet.h"
#include "myLib/xlsx/xlsxcell.h"

class ImportTableFromXslWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImportTableFromXslWidget(QWidget *parent);
    ~ImportTableFromXslWidget();
private:
    void InitUI();
    void InsertWidgetsIntoLayouts();
    void FillUI();
    void ConnectObjects();
private Q_SLOTS:
    void OnXlsFileOpen();
public:
    QString GetFileName(){return m_fileName;};
private:
    QString m_fileName;
private:
    QVBoxLayout *m_mainLayout;

    QLabel *m_importedFileName;
    QPushButton *m_importedFileSelectButton;
    QLabel *m_exportedTableColumnsLabel;
    QListView *m_importedFromFileTableColumnsNamesList;

};

#endif // IMPORTTABLEFROMXSLWIDGET_H
