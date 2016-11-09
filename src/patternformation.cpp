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

#include "patternformation.h"

PatternFormation::PatternFormation(QObject* parent)
    : QObject(parent)
    , weights({1})
    , pfe(nullptr)
    , pff(nullptr)
{
    using namespace revolve::brain;

    pfe = new cpg::PatternFormationNeuron(weights);
    pff = new cpg::PatternFormationNeuron(weights);
}

PatternFormation::~PatternFormation()
{
    delete pfe;
    delete pff;
}

void PatternFormation::neuron_activate(float e, float f)
{
    using namespace revolve::brain;
    cpg::real_t result_e, result_f;
    cpg::real_t delta_time = 0; //TODO

    // they give only one result variable
    result_e = pfe->update({e}, delta_time)[0];
    result_f = pff->update({f}, delta_time)[0];

    emit neuron_output(result_e, result_f);
}

revolve::brain::cpg::PatternFormationNeuron * PatternFormation::getPFE()
{
    return pfe;
}

revolve::brain::cpg::PatternFormationNeuron * PatternFormation::getPFF()
{
    return pff;
}


#include "patternformation.moc"
