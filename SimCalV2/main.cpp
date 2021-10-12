#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Set the app stylesheet
    QFile StylesheetFile("C:/Users/vivek/OneDrive/Documents/SimCalV2/Adaptic.qss");
    StylesheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(StylesheetFile.readAll());
    app.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return app.exec();
}
