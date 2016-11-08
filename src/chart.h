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

#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtCharts/QChartGlobal>

class XYSeriesIODevice;
class RythmGeneratorTimed;
class QAudioInput;
class QFormLayout;

namespace revolve {
namespace brain {
namespace cpg {

class RythmGenerationNeuron;

}}}

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QWidget
{
    Q_OBJECT
public:
    Chart(QWidget *parent = nullptr);
    ~Chart();

public slots:
    void setUpdateTimerDelay(int delay);

private:
    QFormLayout *add_control_layout(revolve::brain::cpg::RythmGenerationNeuron *neuron);

private:
    RythmGeneratorTimed *m_rythm;
    XYSeriesIODevice *m_device;
    QLineSeries *m_series_e;
    QLineSeries *m_series_f;
    QLineSeries *m_series_d;
    QLineSeries *m_series_phi_e;
    QLineSeries *m_series_phi_f;
    QChart *m_chart_e;
    QChart *m_chart_f;
    QChart *m_chart_d;
    QAudioInput *m_audioInput;
};

#endif // CHART_H
