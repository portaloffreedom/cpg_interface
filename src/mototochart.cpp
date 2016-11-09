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

#include "mototochart.h"

MotoToChart::MotoToChart(QtCharts::QXYSeries* series_mn,
                         MotionNeuron* motion_neuron,
                         qint64 range,
                         QObject* parent)
    : ToChart(range, parent)
    , m_series_mn(series_mn)
    , m_motion_neuron(motion_neuron)
{
    connect(m_motion_neuron, &MotionNeuron::neuron_output,
            this, &MotoToChart::dataReady);
}

void MotoToChart::dataReady(float out)
{
    addPoint(m_series_mn, out);
}

#include "mototochart.moc"
