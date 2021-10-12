#include "varianteandcolumnselectiondialog.h"
#include "ui_varianteandcolumnselectiondialog.h"
#include "QStack"
#include "QString"
#include "QStack"
#include "QGroupBox"
#include "QAction"
#include "QPoint"
#include "QVBoxLayout"
#include "QMessageBox"
#include "QButtonGroup"


VarianteAndColumnSelectionDialog::VarianteAndColumnSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VarianteAndColumnSelectionDialog)
{
    ui->setupUi(this);
    this->setFixedWidth(1000);
    this->setFixedHeight(500);
    ui->groupBox->setTitle("Base Variante");
    ui->comboBox->setCurrentIndex(10);
    ui->checkBox1->hide();
    ui->checkBox2->hide();
    ui->checkBox3->hide();
    ui->checkBox4->hide();
    ui->checkBox5->hide();
    ui->radioButton->setChecked(true);












}

VarianteAndColumnSelectionDialog::~VarianteAndColumnSelectionDialog()
{
    delete ui;
}

void VarianteAndColumnSelectionDialog::setComboBoxOptions(const QStack<QString> &fileStack){

    ui->comboBox->addItem("--select--");

    for(QString filename : fileStack){
        int i = 1;
        if(filename.contains("simexport"))
        {


           // qDebug()<<"Start of Global filestack";
            globalFileStack.push_back(filename);
           // qDebug()<<"End of Global filestack";
            size_t pos = filename.lastIndexOf("simexport");
            ui->comboBox->addItem(filename.right(filename.size()-pos-10));


            i++;
        }


    }



}

void VarianteAndColumnSelectionDialog::setCheckBoxOptions(const QStack<QString> &fileStack){

    qDebug()<<"In set checkbox options";
    QStack<QString> fileStackWithoutNullVariante;
    for(QString filename : fileStack) {
        if(filename.contains("simexport")){

     //       if(!filename.contains(ui->comboBox->currentText())) {
                fileStackWithoutNullVariante.push_back(filename);

       //     }
        }

    }
    //QWidget* MDAcheckboxes = new QWidget(ui->groupBox_3);
   // QVBoxLayout* MDAlayout = new QVBoxLayout(MDAcheckboxes);
    QCheckBox *MDAmycheckBox[5];
    MDAmycheckBox[0] = ui->checkBox1;
    MDAmycheckBox[1] = ui->checkBox2;
    MDAmycheckBox[2] = ui->checkBox3;
    MDAmycheckBox[3] = ui->checkBox4;
    MDAmycheckBox[4] = ui->checkBox5;




    for (int i = 0; i < fileStackWithoutNullVariante.size(); i++) {



        MDAmycheckBox[i]->show();
        size_t pos = fileStackWithoutNullVariante.lastIndexOf("simexport");
        MDAmycheckBox[i]->setText(fileStackWithoutNullVariante.at(i).right(fileStackWithoutNullVariante.size()-pos-10));
        qDebug()<<"The value to be displayed in the checkbox is:"<<fileStack.at(i);
        MDAmycheckBox[i]->setStyleSheet("margin-left:30%; margin-right:30%; margin-top:15%");
        MDAmycheckBox[i]->setLayoutDirection(Qt::RightToLeft);
        MDAmycheckBox[i]->depth();
        //otherVarianteCheckedForComparision.append(fileStack.at(i));
        //qDebug()<< "The other variante checked files are: "<<otherVarianteCheckedForComparision.at(i);

//        MDAlayout->addWidget(MDAmycheckBox[i]);
//        ui->checkBox1->setText(fileStackWithoutNullVariante.at(i).right(54));
//        ui->checkBox1->show();
}
   // ui->groupBox->Widget

}

//void VarianteAndColumnSelectionDialog::updateCheckBoxes(){
//    on_comboBox_currentTextChanged(fileToBeDeletedLastName);
//}







void VarianteAndColumnSelectionDialog::on_pushButton_3_clicked()
{
    fileToBeDeletedLastName = ui->comboBox->currentText();
    qDebug()<<"the current text selected in the combo box is"<<fileToBeDeletedLastName;
    QStack<QString> temporaryfilestack;
    temporaryfilestack = globalFileStack;
    if (!(ui->comboBox->currentText()).contains("select")) {


        for (QString filename : temporaryfilestack) {
            if(filename.contains(fileToBeDeletedLastName)) {
                fileToBeDeleted.append(filename);

            }
        }
        nullVarianteSelected.append(fileToBeDeleted);
        temporaryfilestack.removeAll(fileToBeDeleted);

    }
    setCheckBoxOptions(temporaryfilestack);
//    for(int i = 0; i < globalFileStack.size()+1; i++) {
//        QModelIndex index = ui->comboBox->model()->index(i, 0);

//        // This is the effective 'disable' flag
//        QVariant v(0);

//        // the magic
//        ui->comboBox->model()->setData(index, v, Qt::UserRole - 1);
        ui->comboBox->setDisabled(true);
        ui->pushButton_3->hide();


   // }




}





void VarianteAndColumnSelectionDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(!(ui->pushButton_3->isHidden())) {
    QString value = arg1;
    if(!(value.contains("select"))) {

            QMessageBox *m_setting2 = new QMessageBox();
            m_setting2->setWindowTitle("Press Confirm to Display Other Variants");
            m_setting2->setText("Selected Null variante is ");
            m_setting2->show();

            QString text = QString("Selected Null variante is:  %1").arg(value);
            m_setting2->setText(text);

}
}
}


QString VarianteAndColumnSelectionDialog::getNullVarianteSelected() {

    return nullVarianteSelected;
}

QString VarianteAndColumnSelectionDialog::getColumnSelectedForComparision() {
    return columnSelectedForComparision;


}

QStack<QString> VarianteAndColumnSelectionDialog::getOtherVarianteSelectedForComparision(){
    return otherVarianteCheckedForComparision;

}



void VarianteAndColumnSelectionDialog::on_pushButton_clicked()
{

    columnSelectedForComparision = NULL;
    QButtonGroup group4;
    QList<QRadioButton *> allButtons = ui->groupBox_2->findChildren<QRadioButton *>();
    qDebug() <<allButtons.size();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        group4.addButton(allButtons[i],i);
    }
    qDebug() << group4.checkedId();
    QRadioButton selectedRadioButton;

    columnSelectedForComparision.append(group4.checkedButton()->text());
    qDebug()<< "The column selected for comparision is: "<<columnSelectedForComparision;
    if(ui->checkBox1->isChecked()) {
        otherVarianteCheckedForComparision.append(ui->checkBox1->text());
    }
    if(ui->checkBox2->isChecked()) {
        otherVarianteCheckedForComparision.append(ui->checkBox2->text());

    }
    if(ui->checkBox3->isChecked()) {
        otherVarianteCheckedForComparision.append(ui->checkBox3->text());

    }
    if(ui->checkBox4->isChecked()) {
        otherVarianteCheckedForComparision.append(ui->checkBox4->text());

    }
    if(ui->checkBox5->isChecked()) {
        otherVarianteCheckedForComparision.append(ui->checkBox5->text());

    }


    bool checkboxresult = !(ui->checkBox1->isChecked()) && !(ui->checkBox2->isChecked()) && !(ui->checkBox3->isChecked()) && !(ui->checkBox4->isChecked()) && !(ui->checkBox5->isChecked());
    qDebug()<<"The checkedbox result is " <<checkboxresult;
    int radiobuttonresult = group4.checkedId();
    qDebug()<<"The radio button result is:"<<radiobuttonresult;
    if(checkboxresult) {



            QMessageBox *m_setting2 = new QMessageBox();
            m_setting2->setWindowTitle("No Checkbox option is selected");
            QString text = QString("Please select at least 1 other variante options for comparision");
            m_setting2->setText(text);
            m_setting2->show();

    }
    else
      this->close();


}



