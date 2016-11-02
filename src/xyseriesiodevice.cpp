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

#include "xyseriesiodevice.h"
#include <QXYSeries>

#include "brain/cpg/CPGTypes.h"

XYSeriesIODevice::XYSeriesIODevice(QtCharts::QXYSeries* series, QObject* parent)
    : QIODevice(parent)
    , m_series(series)
{
}

qint64 XYSeriesIODevice::readData(char* data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char* data, qint64 maxSize)
{
    qint64 range = 2000;
    QVector<QPointF> oldPoints = m_series->pointsVector();
    QVector<QPointF> points;
    int resolution = 4;

    if (oldPoints.count() < range) {
        points = m_series->pointsVector();
    } else {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
        points.append(QPointF(
            k + size,
            (((revolve::brain::cpg::real_t)data[resolution * k] - 128)/128))
        );

    m_series->replace(points);
    return maxSize;
}

#include "xyseriesiodevice.moc"
