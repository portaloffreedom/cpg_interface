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
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtCharts/QValueAxis>
#include "xyseriesiodevice.h"
#include "rythmgeneratortimed.h"
#include "rythmtochart.h"

QT_CHARTS_USE_NAMESPACE

Chart::Chart(QWidget *parent)
    : QWidget(parent)
    , m_series_e(nullptr)
    , m_series_f(nullptr)
    , m_chart_e(nullptr)
    , m_chart_f(nullptr)
{
    m_chart_e = new QChart;
    m_chart_f = new QChart;
    QChartView *chartView_e = new QChartView(m_chart_e, this);
    QChartView *chartView_f = new QChartView(m_chart_f, this);
    chartView_e->setMinimumSize(400,400);
    chartView_f->setMinimumSize(400,400);
    m_series_e = new QLineSeries;
    m_series_f = new QLineSeries;
    m_chart_e->addSeries(m_series_e);
    m_chart_f->addSeries(m_series_f);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 2000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Value level");

    m_chart_e->setAxisX(axisX, m_series_e);
    m_chart_e->setAxisY(axisY, m_series_e);
    m_chart_e->legend()->hide();
    m_chart_e->setTitle("Data from the neuron e");

    axisX = new QValueAxis;
    axisX->setRange(0, 2000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Value level");
    m_chart_f->setAxisX(axisX, m_series_f);
    m_chart_f->setAxisY(axisY, m_series_f);
    m_chart_f->legend()->hide();
    m_chart_f->setTitle("Data from the neuron f");


    m_rythm = new RythmGeneratorTimed(this);
    RythmToChart *to_chart = new RythmToChart(m_series_e, m_series_f, m_rythm, this);


    QHBoxLayout *mainLayout = new QHBoxLayout;

    {
        QVBoxLayout *e_layout = new QVBoxLayout;
        e_layout->addWidget(chartView_e);
        QFormLayout *form_layout = add_control_layout(m_rythm->getRGE());
        e_layout->addLayout(form_layout);

        mainLayout->addLayout(e_layout);
    }

    {
        QVBoxLayout *f_layout = new QVBoxLayout;
        f_layout->addWidget(chartView_f);
        QFormLayout *form_layout = add_control_layout(m_rythm->getRGF());
        f_layout->addLayout(form_layout);

        mainLayout->addLayout(f_layout);
    }



    setLayout(mainLayout);

//     QAudioFormat formatAudio;
//     formatAudio.setSampleRate(8000);
//     formatAudio.setChannelCount(1);
//     formatAudio.setSampleSize(8);
//     formatAudio.setCodec("audio/pcm");
//     formatAudio.setByteOrder(QAudioFormat::LittleEndian);
//     formatAudio.setSampleType(QAudioFormat::UnSignedInt);

//     QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
//     m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

//     m_device = new XYSeriesIODevice(m_series, this);
//     m_device->open(QIODevice::WriteOnly);
//
//     m_audioInput->start(m_device);


    m_rythm->start();
}

Chart::~Chart()
{
    m_audioInput->stop();
    m_device->close();
}


QFormLayout *Chart::add_control_layout(revolve::brain::cpg::RythmGenerationNeuron *neuron)
{
    static const char number_format = 'f';
    static const int number_precision = 2;


    QFormLayout *form_layout = new QFormLayout;

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

    form_layout->addRow(amplitude_value_label,amplitude_slider);
    form_layout->addRow(offset_value_label,offset_slider);
    form_layout->addRow(weight_value_label,weight_slider);
    form_layout->addRow(phase_value_label,phase_slider);

    connect(amplitude_slider, &QSlider::valueChanged, [neuron, amplitude_value_label] (int value) {
        float new_value = neuron->setAmplitudePercentage(value/10.0);
        amplitude_value_label->setText(QString("amplitude: ") + QString::number(new_value, number_format, number_precision));
    });
    connect(offset_slider, &QSlider::valueChanged, [neuron, offset_value_label] (int value) {
        float new_value = neuron->setOffsetPercentage(value/10.0);
        offset_value_label->setText(QString("offset: ") + QString::number(new_value, number_format, number_precision));
    });
    connect(weight_slider, &QSlider::valueChanged, [neuron, weight_value_label] (int value) {
        float new_value = neuron->setWeightPercentage(value/10.0);
        weight_value_label->setText(QString("weight: ") + QString::number(new_value, number_format, number_precision));
    });
    connect(phase_slider, &QSlider::valueChanged, [neuron, phase_value_label] (int value) {
        float new_value = neuron->setCPercentage(value/10.0);
        phase_value_label->setText(QString("phase: ") + QString::number(new_value, number_format, number_precision));
    });

    return form_layout;
}


#include "chart.moc"
