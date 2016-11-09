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

#ifndef PATTERNFORMATION_H
#define PATTERNFORMATION_H

#include "brain/cpg/PatternFormationNeuron.h"
#include <QObject>

class PatternFormation : public QObject
{
    Q_OBJECT
public:
    PatternFormation(QObject *parent = nullptr);
    ~PatternFormation();

public slots:
    void neuron_activate(float e, float f);

signals:
    void neuron_output(float e, float f);

private:
    std::vector<float> weights;

    revolve::brain::cpg::PatternFormationNeuron *pfe;
    revolve::brain::cpg::PatternFormationNeuron *pff;
};

#endif // PATTERNFORMATION_H
