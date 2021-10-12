#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QLineEdit"
#include "QStack"
#include "QString"
#include "QDirIterator"
#include "QGroupBox"
#include "QMessageBox"
#include "ctime"
#include "time.h"
#include "chrono"
#include "unistd.h"
#include "iostream"
#include "QTextBrowser"
#include "QtCore"
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox->setFixedWidth(100);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setValue(0);
    ui->label->hide();
    ui->ColumnNameSelectedForComparision->hide();
    ui->spinBox->hide();
    ui->pushButton->hide();
    ui->tableWidget_2->setFixedWidth(440);
    ui->tableWidget_2->setFixedHeight(155);
    ui->tableWidget_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOtherVarianteFiles(const QString &otherVarianteFileName, const QString &ColumnNameSelectedForComaparision, const qint64 &varianteNumber) {
    qDebug()<< "Inside other variante";

    QString otherVarianteFromVarCol;
    QString ColumnNameSelected;
    ColumnNameSelected = ColumnNameSelectedForComaparision;


    otherVarianteFromVarCol = otherVarianteFileName;
    if(otherVarianteFromVarCol == "")
        return;
    QDir dir1 = QDir::current();
    QFile file(dir1.filePath(otherVarianteFromVarCol));
    QStringList listA;
    QMap<qint64, QStringList> mapUniqueKeyToRow;
    int row = 0;
    if (file.open(QIODevice::ReadOnly)){
        QList<int> columnIndex;
        QString line0 = file.readLine();
        QStringList columnNames = line0.split(";");
        for (int i = 0; i < columnNames.size(); i++) {
            if(columnNames[i] == "Takt"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zug-Nr."){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zugklasse"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zugcharakteristikkürzel"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Stationsindex"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Stationskürzel"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == ColumnNameSelected){
                columnIndex.push_back(i);
                continue;
            }


        }
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
        while (!file.atEnd()){

            QString line = file.readLine();
            listA = line.split(";");
            if(listA.at(0) == "Mittelwert Simulationen") {
                QStringList finallist;
                for (int i : columnIndex) {
                    finallist.push_back(listA.at(i));

                }

                qint64 uniqueKey = (finallist.at(1) + finallist.at(4)).toInt();

                mapUniqueKeyToRow.insert(uniqueKey, finallist);


            }


        }
        qDebug()<< "The unique key size is: "<< mapUniqueKeyToRow.size();
            for (auto e : mapUniqueKeyToRow.keys())
            {
                QStringList displaylist = mapUniqueKeyToRow.value(e);

               // QTableWidgetItem *test = new QTableWidgetItem(displaylist.at(6));
                //qDebug()<< "the coresponding values in other variants are:" <<e<< "and" << mapUniqueKeyToRow.value(e);
                ui->tableWidget->setHorizontalHeaderItem(ui->tableWidget->columnCount()-1, new QTableWidgetItem("Variante_" + QString::number(varianteNumber)));
                QTableWidgetItem *test = new QTableWidgetItem(displaylist.at(6));
                test->setFlags(test->flags() &  ~Qt::ItemIsEditable);
                ui->tableWidget->setItem(row, ui->tableWidget->columnCount()-1, test);
                row++;

            }

        }



     file.close();

}


QMap<qint64, QStringList> mapUniqueKeyToRow;
int sliderValueFromMainWindow;
int zugKlasseNRz = 0;
int zugKlasseFRz = 0;
int zugKlasseS = 0;
QString ColumnNameSelectedForComaparision;


void MainWindow::on_actionOpen_Folder_Location_triggered()
{


    QString nullVarianteFromVarCol;
    QStack<QString> otherVarianteFileNames;

    varColUi = new VarianteAndColumnSelectionDialog(this);

    QString filename= QFileDialog::getExistingDirectory(this,"Choose Folder");
    qDebug()<<"The filename is" <<filename;

    if (filename.isEmpty())
        return;
    //ui->lineEdit->setText(filename);
    //ui->listWidget->clear();

   // QString dirPath= ui->lineEdit->text();
   // qDebug()<<"The dirpath is" <<dirPath;

    if (filename.isEmpty())
        return;

    QDir dir(filename);
    // used to store the file paths
    QStack<QString> filesStack;
    dir.setFilter(QDir::Files |QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    QStringList qsl;
    qsl.append("*.csv"); // I only want .csv files
    dir.setNameFilters(qsl);
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while(it.hasNext()) {
        filesStack.push(it.next());
    }
    if (filesStack.isEmpty())
        QMessageBox::about(this, "Error Message", "No CSV files found");


    varColUi->setComboBoxOptions(filesStack);

    varColUi->setModal(true);
    varColUi->exec();
    varColUi->update();

    nullVarianteFromVarCol = varColUi->getNullVarianteSelected();
    if(nullVarianteFromVarCol == "")
        return;
    QDir dir1 = QDir::current();
    QFile file(dir1.filePath(nullVarianteFromVarCol));
    QStringList listA;
   // QMap<qint64, QStringList> mapUniqueKeyToRow;
    int row = 0;
    if (file.open(QIODevice::ReadOnly)){
        QList<int> columnIndex;
        QString line0 = file.readLine();
        QStringList columnNames = line0.split(";");
        for(int i = 0 ; i<columnNames.size(); i++) {
           // qDebug()<<"the name of the column"<<i+1<<"is"<<columnNames.at(i);
        }
        ColumnNameSelectedForComaparision = varColUi->getColumnSelectedForComparision();
        //ColumnNameSelectedForComaparision = "Abfahrtsverspätungsentwicklung (in s)";
        for (int i = 0; i < columnNames.size(); i++) {
            if(columnNames[i] == "Takt"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zug-Nr."){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zugklasse"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Zugcharakteristikkürzel"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Stationsindex"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == "Stationskürzel"){
                columnIndex.push_back(i);
                continue;
            }
            else if(columnNames[i] == ColumnNameSelectedForComaparision){
                columnIndex.push_back(i);
                continue;
            }


        }
        for (int i=0;i<columnIndex.size() ;i++ ) {
            qDebug()<<"The column indexes are:"<<columnIndex.at(i);
        }
        while (!file.atEnd()){

            QString line = file.readLine();
            listA = line.split(";");
            if(listA.at(0) == "Mittelwert Simulationen") {
                QStringList finallist;
                for (int i : columnIndex) {
                    finallist.push_back(listA.at(i));

                }

                qint64 uniqueKey = (finallist.at(1) + finallist.at(4)).toInt();


                mapUniqueKeyToRow.insert(uniqueKey, finallist);



                    }


            }
        qDebug()<< "The unique key size is: "<< mapUniqueKeyToRow.size();

            for(auto e : mapUniqueKeyToRow.keys())
            {
                QStringList displaylist = mapUniqueKeyToRow.value(e);
                ui->tableWidget->setColumnCount(columnIndex.size());
                ui->tableWidget->insertRow(row);
                //qDebug()<< "the coresponding values in null variante are:" <<e<< "and" << mapUniqueKeyToRow.value(e);
                for (int x = 0; x < displaylist.size(); x++){
                    QTableWidgetItem *test = new QTableWidgetItem(displaylist.at(x));
                    test->setFlags(test->flags() &  ~Qt::ItemIsEditable);

                    ui->tableWidget->setItem(row, x, test);

                    }row++;

            }

        }



     file.close();
     otherVarianteFileNames = varColUi->getOtherVarianteSelectedForComparision();
     globalOtherVarianteFileNames = otherVarianteFileNames;

     for(int i = 0; i < otherVarianteFileNames.size(); i++) {
          openOtherVarianteFiles(otherVarianteFileNames.at(i), ColumnNameSelectedForComaparision, i + 1);
     }

     for(int j = 1; j<otherVarianteFileNames.size()+1; j++) {
         ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
         ui->tableWidget->setHorizontalHeaderItem(ui->tableWidget->columnCount()-1, new QTableWidgetItem("Diff_Var" + QString::number(j) + "_Sec"));
         qint64 row_diff = 0;
         qint64 differenceTimeSec;
         if(ColumnNameSelectedForComaparision == "Abfahrtsverspätungsentwicklung (in s)" || ColumnNameSelectedForComaparision == "Ankunftsverspätungsentwicklung (in s)") {
             for(int i=0; i<mapUniqueKeyToRow.size();i++) {
                 QString nullVarianteTime  = ui->tableWidget->item(row_diff, 6)->text();
                 QString otherVarianteTime = ui->tableWidget->item(row_diff, j+6)->text();
                 differenceTimeSec = nullVarianteTime.toInt() - otherVarianteTime.toInt();
                 ui->tableWidget->setItem(i, ui->tableWidget->columnCount()-1, new QTableWidgetItem(QString::number(differenceTimeSec)));
                 row_diff++;

             }


         }

         else
         for(int i = 0; i<mapUniqueKeyToRow.size();i++) {

             QString nullVarianteTime  = ui->tableWidget->item(row_diff, 6)->text();

             //qDebug()<< "The null variante time is:"<<nullVarianteTime;
             QStringList nullVarianteHHMMSS;
             qint64 nullVarianteTimeSec;
             if(nullVarianteTime.isEmpty()){
                 nullVarianteTimeSec = 0;
             }
             else
             {
                 nullVarianteHHMMSS = nullVarianteTime.split(":");
                 nullVarianteTimeSec = ((nullVarianteHHMMSS.at(0).toInt())*3600 + (nullVarianteHHMMSS.at(1).toInt())*60 + (nullVarianteHHMMSS.at(2).toInt()));

             }

             //qDebug()<< "The null variantetime in sec is : "<<nullVarianteTimeSec;


             QString otherVarianteTime = ui->tableWidget->item(row_diff, j+6)->text();

             //qDebug()<< "The other variante time is:"<<otherVarianteTime;
             QStringList otherVarianteHHMMSS;
             qint64 otherVarianteTimeSec;
             if(otherVarianteTime.isEmpty()){
                 otherVarianteTimeSec = 0;
             }
             else
             {
                 otherVarianteHHMMSS = otherVarianteTime.split(":");
                 otherVarianteTimeSec = ((otherVarianteHHMMSS.at(0).toInt())*3600 + (otherVarianteHHMMSS.at(1).toInt())*60 + (otherVarianteHHMMSS.at(2).toInt()));

             }
             //qDebug()<< "The othere variante time in sec is: "<<otherVarianteTimeSec;
               differenceTimeSec = nullVarianteTimeSec - otherVarianteTimeSec;
             //qDebug()<< "The difference time secs for the" <<i+1<<"row is: "<<differenceTimeSec;

             ui->tableWidget->setItem(i, ui->tableWidget->columnCount()-1, new QTableWidgetItem(QString::number(differenceTimeSec)));
             row_diff++;


         }


     }

     for(int j = 1; j<otherVarianteFileNames.size()+1; j++) {
         ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
         ui->tableWidget->setHorizontalHeaderItem(ui->tableWidget->columnCount()-1, new QTableWidgetItem("Nutzen_Var" + QString::number(j)));
         qint64 row_diff = 0;
         //QLocale german(QLocale::German);
         for(int i=0; i<mapUniqueKeyToRow.size();i++) {
             QString VarianteTimeSec  = ui->tableWidget->item(row_diff, 6+otherVarianteFileNames.size()+j)->text();
             QString zugKlasse = ui->tableWidget->item(row_diff, 2)->text();
             float nutzen;
             if (zugKlasse == "FRz") {
                 nutzen = (VarianteTimeSec.toFloat() * 250 * 7) / 3600;
                 zugKlasseFRz+=1;

             }
             else if (zugKlasse == "NRz") {
                 nutzen = (VarianteTimeSec.toFloat() * 50 * 7) / 3600;
                 zugKlasseNRz+=1;
             }
             else {
                 nutzen = (VarianteTimeSec.toFloat() * 50 * 7) / 3600;
                 zugKlasseS+=1;
             }




             //QString nutzenString =  QString::number(nutzen);
             ui->tableWidget->setItem(i, ui->tableWidget->columnCount()-1, new QTableWidgetItem(QString::number(nutzen,\
                                                                                                                'f', 2).replace(".", ",") + "€"));
             row_diff++;
         }




}
     ui->spinBox->show();
     ui->pushButton->show();
     ui->label->show();
     ui->ColumnNameSelectedForComparision->show();
     ui->ColumnNameSelectedForComparision->setText("The Column Selected for Comparision is : " + ColumnNameSelectedForComaparision);







    }











void MainWindow::on_pushButton_clicked()
{

    int zugKlasseNRzNutzenWirkung = 0;
    int zugKlasseFRzNutzenWirkung = 0;
    int zugKlasseSNutzenWirkung = 0;
    float nutzenProJahrNRz = 0.00;
    float nutzenProJahrFRz = 0.00;
    float nutzenProJahrS = 0.00;
    ui->tableWidget_2->show();
    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(QString::number(zugKlasseNRz)));
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem(QString::number(zugKlasseFRz)));
    ui->tableWidget_2->setItem(2, 1, new QTableWidgetItem(QString::number(zugKlasseS)));
    ui->tableWidget_2->setItem(3, 1, new QTableWidgetItem(QString::number(zugKlasseNRz + zugKlasseFRz + zugKlasseS)));
    sliderValueFromMainWindow = ui->spinBox->value();
    int sliderValue = sliderValueFromMainWindow;
    qDebug()<<"The selected value is :" <<sliderValue;
    for(int j = 1; j<globalOtherVarianteFileNames.size()+1; j++) {
        qint64 row_diff = 0;
        float nutzen=0.00;

        for(int i=0; i<mapUniqueKeyToRow.size();i++) {
            QString VarianteTimeSec  = ui->tableWidget->item(row_diff, 6+globalOtherVarianteFileNames.size()+j)->text();
            QString zugKlasse = ui->tableWidget->item(row_diff, 2)->text();
            if (VarianteTimeSec.toFloat() >= sliderValue or VarianteTimeSec.toFloat() <= -(sliderValue)) {
                if (zugKlasse == "FRz") {
                    nutzen = (VarianteTimeSec.toFloat() * 250 * 7) / 3600;
                    nutzenProJahrFRz = nutzenProJahrFRz + nutzen;
                    zugKlasseFRzNutzenWirkung+=1;

                }
                else if (zugKlasse == "NRz") {
                    nutzen = (VarianteTimeSec.toFloat() * 50 * 7) / 3600;
                    nutzenProJahrNRz = nutzenProJahrNRz + nutzen;
                    zugKlasseNRzNutzenWirkung+=1;
                }
                else if (zugKlasse == "S") {
                    nutzen = (VarianteTimeSec.toFloat() * 50 * 7) / 3600;
                    nutzenProJahrS = nutzenProJahrS + nutzen;
                    zugKlasseSNutzenWirkung+=1;
                }



            }

            else
                nutzen = 0.00;



            ui->tableWidget->setItem(i, 6 + 2 * globalOtherVarianteFileNames.size() + j, new QTableWidgetItem(QString::number(nutzen,\
                                                                                                                              'f', 2).replace(".", ",") + "€"));
            row_diff++;
        }

    }

    ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(QString::number(zugKlasseNRzNutzenWirkung)));
    ui->tableWidget_2->setItem(1, 2, new QTableWidgetItem(QString::number(zugKlasseFRzNutzenWirkung)));
    ui->tableWidget_2->setItem(2, 2, new QTableWidgetItem(QString::number(zugKlasseSNutzenWirkung)));
    ui->tableWidget_2->setItem(3, 2, new QTableWidgetItem(QString::number(zugKlasseNRzNutzenWirkung + zugKlasseFRzNutzenWirkung + zugKlasseSNutzenWirkung)));
    ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(QString::number(nutzenProJahrNRz,\
                                                                          'f', 2).replace(".", ",") + "€"));
    ui->tableWidget_2->setItem(1, 3, new QTableWidgetItem(QString::number(nutzenProJahrFRz,\
                                                                          'f', 2).replace(".", ",") + "€"));
    ui->tableWidget_2->setItem(2, 3, new QTableWidgetItem(QString::number(nutzenProJahrS,\
                                                                          'f', 2).replace(".", ",") + "€"));
    ui->tableWidget_2->setItem(3, 3, new QTableWidgetItem(QString::number(nutzenProJahrNRz + nutzenProJahrFRz + nutzenProJahrS,\
                                                                          'f', 2).replace(".", ",") + "€"));


}

void MainWindow::on_actionUsage_Of_Application_triggered()
{
    QMessageBox *m_setting4 = new QMessageBox();
    m_setting4->setWindowTitle("Instructions for Use");
    QString text = QString("1. After opening the Application, Click on the File option at the top left and select Open Folder Location \n 2. Now select the directory path \n "
"3. Now choose the base variante and press Confirm \n 4. Now the Other Variante Files will pop up and check out the files of your wish \n "
"5. Choose the column needed for comparision from the list of radio buttons \n 6. Now the table is showed and you can calculate Nutzen werte with "
" your difference time given in Spinbox values (Here if difference is <= -(value) or difference is >= value, the nutzen  werte are calculated \n "
"6.  Now Click on Update Nutzen Column(s) and Display Gesamtnutzen [pro Jahr] button for final Calculations \n "
"---------------------------------------------------------------------------------------------------- \n "
"Scope of Improvements: \n "
"a. Reset Button to erase all existing values and re-run application can be implemented later \n "
"b. The maximum other varinate files that can be compared at the moment are only 5");
    m_setting4->setText(text);
    m_setting4->show();
}

