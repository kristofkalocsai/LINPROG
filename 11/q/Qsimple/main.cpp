#include "mainwindow.h"
#include <QApplication>
#include "qtranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("qsimple_hu_HU");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
