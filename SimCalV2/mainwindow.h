#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "varianteandcolumnselectiondialog.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openOtherVarianteFiles(const QString &otherVarianteFileName, const QString &ColumnNameSelectedForComaparision, const qint64 &varianteNumber);

private slots:
    void on_actionOpen_Folder_Location_triggered();









    void on_pushButton_clicked();

    void on_actionUsage_Of_Application_triggered();

private:
    Ui::MainWindow *ui;
    VarianteAndColumnSelectionDialog *varColUi;

    QStack<QString> globalOtherVarianteFileNames;

    qint16 sliderValue;

};
#endif // MAINWINDOW_H
