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

#ifndef RYTHMTOCHART_H
#define RYTHMTOCHART_H

#include "rythmgeneratortimed.h"
#include <QObject>
#include <QXYSeries>

class RythmToChart : public QObject
{
    Q_OBJECT
public:
    RythmToChart(QtCharts::QXYSeries* series_e,
                 QtCharts::QXYSeries* series_f,
                 QtCharts::QXYSeries* series_phi_e,
                 QtCharts::QXYSeries *series_phi_f,
                 RythmGeneratorTimed* rythm_generator_timed,
                 qint64 range,
                 QObject* parent = nullptr);
    ~RythmToChart();

public slots:
    void dataReady(float e, float f, float phi_e, float phi_f);

private:
    void addPoint(QtCharts::QXYSeries *series, float point) const;

private:
    qint64 m_range;
    QtCharts::QXYSeries *m_series_e;
    QtCharts::QXYSeries *m_series_f;
    QtCharts::QXYSeries *m_series_phi_e;
    QtCharts::QXYSeries *m_series_phi_f;
    RythmGeneratorTimed *m_rythm_generator_timed;
};

#endif // RYTHMTOCHART_H
