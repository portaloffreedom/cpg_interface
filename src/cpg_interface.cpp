#include "cpg_interface.h"
#include "ui_cpg_interface.h"
#include "chart.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>

cpg_interface::cpg_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cpg_interface)
{
    ui->setupUi(this);
    m_chart = new Chart(this);
    QWidget *centralWidget = new QWidget(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    centralWidget->setLayout(mainLayout);

    QHBoxLayout * controlsLayout = init_control_bar();
    mainLayout->addLayout(controlsLayout);

    mainLayout->addWidget(m_chart);

    this->setCentralWidget(centralWidget);
}

cpg_interface::~cpg_interface()
{
    delete ui;
}

QHBoxLayout * cpg_interface::init_control_bar()
{
    QHBoxLayout *controlsLayout = new QHBoxLayout;

    timerDelaySpinBox_ = new QSpinBox(this);
    controlsLayout->addWidget(timerDelaySpinBox_);
    QObject::connect(timerDelaySpinBox_, SIGNAL(valueChanged(int)), m_chart, SLOT(setUpdateTimerDelay(int)));
    timerDelaySpinBox_->setValue(30);

    return controlsLayout;
}
