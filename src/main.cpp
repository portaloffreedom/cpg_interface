#include "cpg_interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    cpg_interface w;
    w.show();

    return app.exec();
}

