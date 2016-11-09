/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  Matteo De Carlo <matteo.dek@covolunablu.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "chart.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDoubleSpinBox>
#include <QtCharts/QValueAxis>
#include "rythmgeneratortimed.h"
#include "rythmtochart.h"
#include "patternformation.h"
#include "patterntochart.h"

QT_CHARTS_USE_NAMESPACE

QValueAxis *createXAxis(const char* name, unsigned int history = 100)
{
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, history);
    axisX->setLabelFormat("%g");
    axisX->setTitleText(name);

    return axisX;
}

QValueAxis *createYAxis(const char* name, qreal min = -1, qreal max = 1)
{
    QValueAxis *axisY = new QValueAxis;

    axisY = new QValueAxis;
    axisY->setRange(min, max);
    axisY->setTitleText(name);

    return axisY;
}

Chart::Chart(QWidget *parent)
    : QWidget(parent)
    , m_series_e(nullptr)
    , m_series_f(nullptr)
    , m_series_d(nullptr)
    , m_series_phi_e(nullptr)
    , m_series_phi_f(nullptr)
    , m_chart_e(nullptr)
    , m_chart_f(nullptr)
    , m_chart_d(nullptr)
    , m_chart_e_pf(nullptr)
    , m_chart_f_pf(nullptr)
    , m_chart_d_pf(nullptr)
{
    unsigned int history = 100; //points
    unsigned int timer_wait = 30; //ms

    m_chart_e = new QChart;
    m_chart_f = new QChart;
    m_chart_d = new QChart;

    m_chart_e_pf = new QChart;
    m_chart_f_pf = new QChart;
    m_chart_d_pf = new QChart;

    QChartView *chartView_e = new QChartView(m_chart_e, this);
    QChartView *chartView_f = new QChartView(m_chart_f, this);
    QChartView *chartView_d = new QChartView(m_chart_d, this);

    QChartView *chartView_e_pf = new QChartView(m_chart_e_pf, this);
    QChartView *chartView_f_pf = new QChartView(m_chart_f_pf, this);
    QChartView *chartView_d_pf = new QChartView(m_chart_d_pf, this);

    chartView_e->setMinimumSize(400,400);
    chartView_f->setMinimumSize(400,400);
    chartView_d->setMinimumSize(400,400);

    chartView_e_pf->setMinimumSize(400,400);
    chartView_f_pf->setMinimumSize(400,400);
    chartView_d_pf->setMinimumSize(400,400);

    m_series_e = new QLineSeries;
    m_series_phi_e = new QLineSeries;
    m_series_f = new QLineSeries;
    m_series_phi_f = new QLineSeries;
    m_series_d = new QLineSeries;

    m_series_e_pf = new QLineSeries;
    m_series_f_pf = new QLineSeries;
    m_series_d_pf = new QLineSeries;

    m_chart_e->addSeries(m_series_e);
    m_chart_e->addSeries(m_series_phi_e);
    m_chart_f->addSeries(m_series_f);
    m_chart_f->addSeries(m_series_phi_f);
    m_chart_d->addSeries(m_series_d);

    m_chart_e_pf->addSeries(m_series_e_pf);
    m_chart_f_pf->addSeries(m_series_f_pf);
    m_chart_d_pf->addSeries(m_series_d_pf);

    QValueAxis *axisX;
    QValueAxis *axisY;
    QValueAxis *axisY_phi;

    // RGE
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Value level");
    axisY_phi = createYAxis("Phi",-100000, 100000);

    m_chart_e->legend()->hide();
    m_chart_e->setTitle("Data from the neuron e");
    axisY->setLinePenColor(m_series_e->pen().color());
    axisY_phi->setLinePenColor(m_series_phi_e->pen().color());

    m_chart_e->addAxis(axisX, Qt::AlignBottom);
    m_chart_e->addAxis(axisY, Qt::AlignLeft);
    m_chart_e->addAxis(axisY_phi, Qt::AlignRight);
    m_series_e->attachAxis(axisX);
    m_series_e->attachAxis(axisY);
    m_series_phi_e->attachAxis(axisX);
    m_series_phi_e->attachAxis(axisY_phi);

    // RGF
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Value level");
    axisY_phi = createYAxis("Phi",-100000, 100000);

    m_chart_f->legend()->hide();
    m_chart_f->setTitle("Data from the neuron f");
    axisY->setLinePenColor(m_series_f->pen().color());
    axisY_phi->setLinePenColor(m_series_phi_f->pen().color());

    m_chart_f->addAxis(axisX, Qt::AlignBottom);
    m_chart_f->addAxis(axisY, Qt::AlignLeft);
    m_chart_f->addAxis(axisY_phi, Qt::AlignRight);
    m_series_f->attachAxis(axisX);
    m_series_f->attachAxis(axisY);
    m_series_phi_f->attachAxis(axisX);
    m_series_phi_f->attachAxis(axisY_phi);

    // RG Difference
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Difference", -2, 2);

    m_chart_d->legend()->hide();
    m_chart_d->setTitle("subtraction of the two data");

    m_chart_d->addAxis(axisX, Qt::AlignBottom);
    m_chart_d->addAxis(axisY, Qt::AlignLeft);
    m_series_d->attachAxis(axisX);
    m_series_d->attachAxis(axisY);

    // PFE
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Value level", 0, 1);

    m_chart_e_pf->legend()->hide();
    m_chart_e_pf->setTitle("Pattern Formation E");
    axisY->setLinePenColor(m_series_e_pf->pen().color());

    m_chart_e_pf->addAxis(axisX, Qt::AlignBottom);
    m_chart_e_pf->addAxis(axisY, Qt::AlignLeft);
    m_series_e_pf->attachAxis(axisX);
    m_series_e_pf->attachAxis(axisY);

    // PFF
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Value level", 0, 1);

    m_chart_f_pf->legend()->hide();
    m_chart_f_pf->setTitle("Pattern Formation F");
    axisY->setLinePenColor(m_series_f_pf->pen().color());

    m_chart_f_pf->addAxis(axisX, Qt::AlignBottom);
    m_chart_f_pf->addAxis(axisY, Qt::AlignLeft);
    m_series_f_pf->attachAxis(axisX);
    m_series_f_pf->attachAxis(axisY);

    // PF Difference
    axisX = createXAxis("Samples", history);
    axisY = createYAxis("Difference", -2, 2);

    m_chart_d_pf->legend()->hide();
    m_chart_d_pf->setTitle("Difference in PF");
    axisY->setLinePenColor(m_series_d_pf->pen().color());

    m_chart_d_pf->addAxis(axisX, Qt::AlignBottom);
    m_chart_d_pf->addAxis(axisY, Qt::AlignLeft);
    m_series_d_pf->attachAxis(axisX);
    m_series_d_pf->attachAxis(axisY);

    // rythm generator and chart-rythm connection
    m_rythm = new RythmGeneratorTimed(timer_wait,this);
    RythmToChart *to_chart = new RythmToChart(
        m_series_e,
        m_series_f,
        m_series_d,
        m_series_phi_e,
        m_series_phi_f,
        m_rythm,
        history,
        this);

    m_pattern_formation = new PatternFormation(this);
    connect(m_rythm, &RythmGeneratorTimed::neuron_output,
            m_pattern_formation, &PatternFormation::neuron_activate);
    PatternToChart *p_to_chart = new PatternToChart(
        m_series_e_pf,
        m_series_f_pf,
        m_series_d_pf,
        m_pattern_formation,
        history,
        this);


    QGridLayout *mainLayout = new QGridLayout;

    {
        QVBoxLayout *e_layout = new QVBoxLayout;
        e_layout->addWidget(chartView_e);
        QLayout *form_layout = add_control_layout(m_rythm->getRGE());
        e_layout->addLayout(form_layout);


        mainLayout->addLayout(e_layout, 1, 1);
    }

    {
        QVBoxLayout *f_layout = new QVBoxLayout;
        f_layout->addWidget(chartView_f);
        QLayout *form_layout = add_control_layout(m_rythm->getRGF());
        f_layout->addLayout(form_layout);


        mainLayout->addLayout(f_layout, 1, 2);
    }

    {
        QVBoxLayout *d_layout = new QVBoxLayout;
        d_layout->addWidget(chartView_d);


        mainLayout->addLayout(d_layout, 1, 3);
    }


    mainLayout->addWidget(chartView_e_pf, 2, 1);
    mainLayout->addWidget(chartView_f_pf, 2, 2);
    mainLayout->addWidget(chartView_d_pf, 2, 3);


    setLayout(mainLayout);

    m_rythm->start();
}

Chart::~Chart()
{
}


QLayout *Chart::add_control_layout(revolve::brain::cpg::RythmGenerationNeuron *neuron)
{
    static const char number_format = 'f';
    static const int number_precision = 2;


    QGridLayout *grid_layout = new QGridLayout;

    QSlider *amplitude_slider = new QSlider(Qt::Horizontal, this);
    QSlider *offset_slider = new QSlider(Qt::Horizontal, this);
    QSlider *weight_slider = new QSlider(Qt::Horizontal, this);
    QSlider *phase_slider = new QSlider(Qt::Horizontal, this);

    QLabel *amplitude_value_label = new QLabel("amplitude", this);
    QLabel *offset_value_label = new QLabel("offset", this);
    QLabel *weight_value_label = new QLabel("weight", this);
    QLabel *phase_value_label = new QLabel("phase", this);

    amplitude_slider->setMinimum(0);
    offset_slider->setMinimum(0);
    weight_slider->setMinimum(0);
    phase_slider->setMinimum(0);

    amplitude_slider->setMaximum(1000);
    offset_slider->setMaximum(1000);
    weight_slider->setMaximum(1000);
    phase_slider->setMaximum(1000);

    QDoubleSpinBox *amplitude_spin = new QDoubleSpinBox(this);
    QDoubleSpinBox *offset_spin = new QDoubleSpinBox(this);
    QDoubleSpinBox *weight_spin = new QDoubleSpinBox(this);
    QDoubleSpinBox *phase_spin = new QDoubleSpinBox(this);

    amplitude_spin->setSingleStep(0.05);
    offset_spin->setSingleStep(0.05);
    weight_spin->setSingleStep(0.05);
    phase_spin->setSingleStep(0.05);

    amplitude_spin->setMinimum(neuron->AMPLITUDE_MIN);
    amplitude_spin->setMaximum(neuron->AMPLITUDE_MAX);
    offset_spin->setMinimum(neuron->OFFSET_MIN);
    offset_spin->setMaximum(neuron->OFFSET_MAX);
    weight_spin->setMinimum(neuron->WEIGHT_MIN);
    weight_spin->setMaximum(neuron->WEIGHT_MAX);
    phase_spin->setMinimum(neuron->C_MIN);
    phase_spin->setMaximum(neuron->C_MAX);


    grid_layout->addWidget(amplitude_value_label, 1, 1);
    grid_layout->addWidget(amplitude_spin       , 1, 2);
    grid_layout->addWidget(amplitude_slider     , 1, 3);
    grid_layout->addWidget(offset_value_label   , 2, 1);
    grid_layout->addWidget(offset_spin          , 2, 2);
    grid_layout->addWidget(offset_slider        , 2, 3);
    grid_layout->addWidget(weight_value_label   , 3, 1);
    grid_layout->addWidget(weight_spin          , 3, 2);
    grid_layout->addWidget(weight_slider        , 3, 3);
    grid_layout->addWidget(phase_value_label    , 4, 1);
    grid_layout->addWidget(phase_spin           , 4, 2);
    grid_layout->addWidget(phase_slider         , 4, 3);


    // Sliders connections
    connect(amplitude_slider, &QSlider::valueChanged, [neuron, amplitude_spin] (int value) {
        float new_value = neuron->setAmplitudePercentage(value/1000.0);
        amplitude_spin->blockSignals(true);
        amplitude_spin->setValue(new_value);
        amplitude_spin->blockSignals(false);
    });
    connect(offset_slider, &QSlider::valueChanged, [neuron, offset_spin] (int value) {
        float new_value = neuron->setOffsetPercentage(value/1000.0);
        offset_spin->blockSignals(true);
        offset_spin->setValue(new_value);
        offset_spin->blockSignals(false);
    });
    connect(weight_slider, &QSlider::valueChanged, [neuron, weight_spin] (int value) {
        float new_value = neuron->setWeightPercentage(value/1000.0);
        weight_spin->blockSignals(true);
        weight_spin->setValue(new_value);
        weight_spin->blockSignals(false);
    });
    connect(phase_slider, &QSlider::valueChanged, [neuron, phase_spin] (int value) {
        float new_value = neuron->setCPercentage(value/1000.0);
        phase_spin->blockSignals(true);
        phase_spin->setValue(new_value);
        phase_spin->blockSignals(false);
    });

    // Spin connections
    connect(amplitude_spin,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [neuron, amplitude_slider] (double value)
    {
        amplitude_slider->blockSignals(true);
        amplitude_slider->setValue(neuron->calculateAmplitudePercentage(value)*1000);
        amplitude_slider->blockSignals(false);
        neuron->setAmplitude(value);
    });
    connect(offset_spin,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [neuron, offset_slider] (double value)
    {
        offset_slider->blockSignals(true);
        offset_slider->setValue(neuron->calculateOffsetPercentage(value)*1000);
        neuron->setOffset(value);
    });
    connect(weight_spin,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [neuron, weight_slider] (double value)
    {
        weight_slider->blockSignals(true);
        weight_slider->setValue(neuron->calculateWeightPercentage(value)*1000);
        weight_slider->blockSignals(false);
        neuron->setWeight(value);
    });
    connect(phase_spin,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [neuron, phase_slider] (double value)
    {
        phase_slider->blockSignals(true);
        phase_slider->setValue(neuron->calculateCPercentage(value)*1000);
        phase_slider->blockSignals(false);
        neuron->setC(value);
    });

    // Set initial value to spins, sliders should be updated automagically with the signals
    amplitude_spin->setValue(neuron->getAmplitude());
    offset_spin->setValue(neuron->getOffset());
    weight_spin->setValue(neuron->getWeight());
    phase_spin->setValue(neuron->getC());

    return grid_layout;
}

void Chart::setUpdateTimerDelay(int delay)
{
    m_rythm->setUpdateTimerDelay(delay);
}


#include "chart.moc"
#include "patterntochart.h"
#include "patterntochart.h"
#include "patterntochart.h"
