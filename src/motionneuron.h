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

#ifndef MOTIONNEURON_H
#define MOTIONNEURON_H

#include "brain/cpg/MotoNeuron.h"
#include <QObject>

class MotionNeuron : public QObject
{
    Q_OBJECT
public:
    MotionNeuron(QObject *parent = nullptr);
    ~MotionNeuron();

public slots:
    void neuron_activate(float e, float f);

signals:
    void neuron_output(float out);

private:
    revolve::brain::cpg::MotoNeuron *moto_neuron;
};

#endif // MOTIONNEURON_H
