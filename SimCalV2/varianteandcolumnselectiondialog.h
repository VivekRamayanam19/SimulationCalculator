#ifndef VARIANTEANDCOLUMNSELECTIONDIALOG_H
#define VARIANTEANDCOLUMNSELECTIONDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QArrayData>
#include <QStack>

namespace Ui {
class VarianteAndColumnSelectionDialog;
}

class VarianteAndColumnSelectionDialog : public QDialog
{
    Q_OBJECT
    QVector<QCheckBox*> checkboxes;

public:
    explicit VarianteAndColumnSelectionDialog(QWidget *parent = nullptr);
    ~VarianteAndColumnSelectionDialog();
    void setComboBoxOptions(const QStack<QString> &fileStack);
    void setCheckBoxOptions(const QStack<QString> &fileStack);
    void updateCheckBoxes();
    QString getNullVarianteSelected();
    QString getColumnSelectedForComparision();
    QStack<QString> getOtherVarianteSelectedForComparision();




public slots:





private slots:




    void on_pushButton_3_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);






    void on_pushButton_clicked();



private:
    Ui::VarianteAndColumnSelectionDialog *ui;
    QStack<QString> globalFileStack;
    QString fileToBeDeletedLastName;
    QString fileToBeDeleted;
    QString nullVarianteSelected;
    QStack<QString> otherVarianteCheckedForComparision;
    QString columnSelectedForComparision;

};

#endif // VARIANTEANDCOLUMNSELECTIONDIALOG_H
