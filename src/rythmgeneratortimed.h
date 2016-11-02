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

#ifndef RYTHMGENERATORTIMED_H
#define RYTHMGENERATORTIMED_H

#include "brain/cpg/RythmGenerationNeuron.h"
#include <QObject>
#include <QTimer>

class RythmGeneratorTimed : public QObject
{
    Q_OBJECT
public:
    RythmGeneratorTimed(QObject *parent = nullptr);
    virtual ~RythmGeneratorTimed();

    void start();

    revolve::brain::cpg::RythmGenerationNeuron* getRGE();
    revolve::brain::cpg::RythmGenerationNeuron* getRGF();

signals:
    void neuron_output(float e, float f);

private:
    void generate_output();

// Class Variables
private:
    QTimer *timer;

    revolve::brain::cpg::RythmGenerationNeuron *rge;
    revolve::brain::cpg::RythmGenerationNeuron *rgf;
};

#endif // RYTHMGENERATORTIMED_H
