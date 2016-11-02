#include "cpg_interface.h"
#include "ui_cpg_interface.h"
#include "chart.h"

cpg_interface::cpg_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cpg_interface)
{
    ui->setupUi(this);
    m_chart = new Chart(this);
    this->setCentralWidget(m_chart);
}

cpg_interface::~cpg_interface()
{
    delete ui;
}
