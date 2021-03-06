#ifndef CPG_INTERFACE_H
#define CPG_INTERFACE_H

#include <QMainWindow>

namespace Ui {
class cpg_interface;
}

class QHBoxLayout;
class QSpinBox;
class Chart;

class cpg_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit cpg_interface(QWidget *parent = 0);
    ~cpg_interface();

private:
    QHBoxLayout * init_control_bar();

private:
    Ui::cpg_interface *ui;
    Chart *m_chart;

    QSpinBox * timerDelaySpinBox_;

};

#endif // CPG_INTERFACE_H
