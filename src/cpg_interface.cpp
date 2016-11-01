#include "cpg_interface.h"
#include "ui_cpg_interface.h"

cpg_interface::cpg_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cpg_interface)
{
    ui->setupUi(this);
}

cpg_interface::~cpg_interface()
{
    delete ui;
}
