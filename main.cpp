#include "mainwindow.h"
#include <QApplication>
#include "page1_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    page1_dialog w;
    w.show();

    return a.exec();
}
