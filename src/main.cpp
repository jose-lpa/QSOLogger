#include "qsologger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSOLogger w;
    w.show();

    return a.exec();
}
