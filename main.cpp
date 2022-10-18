#include "qsnowflake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSnowflake w;
    w.setWindowFlag(Qt::Dialog);
    w.show();
    return a.exec();
}
