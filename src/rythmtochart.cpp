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

#include "rythmtochart.h"

#include <QLineSeries>

RythmToChart::RythmToChart(QtCharts::QXYSeries* series_e,
                           QtCharts::QXYSeries *series_f,
                           RythmGeneratorTimed* rythm_generator_timed,
                           QObject* parent)
    : QObject(parent)
    , m_series_e(series_e)
    , m_series_f(series_f)
    , m_rythm_generator_timed(rythm_generator_timed)
{
    connect(m_rythm_generator_timed, &RythmGeneratorTimed::neuron_output,
            this, &RythmToChart::dataReady);
}

RythmToChart::~RythmToChart()
{
}

void addPoint(QtCharts::QXYSeries *series, float point)
{
    qint64 range = 2000;
    QVector<QPointF> oldPoints = series->pointsVector();
    QVector<QPointF> points;

    if (oldPoints.count() < range) {
        points = series->pointsVector();
    } else {
        for (int i = 1; i < oldPoints.count(); i++)
            points.append(QPointF(i - 1, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    points.append(QPointF(size, point));

    series->replace(points);
}

void RythmToChart::dataReady(float e, float f)
{
    addPoint(m_series_e, e);
    addPoint(m_series_f, f);
}


#include "rythmtochart.moc"
