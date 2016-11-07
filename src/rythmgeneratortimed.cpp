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

#include "rythmgeneratortimed.h"

RythmGeneratorTimed::RythmGeneratorTimed(int timer_wait, QObject *parent)
    : QObject(parent)
    , timer(nullptr)
    , interval(timer_wait)
    , rge(nullptr)
    , rgf(nullptr)
{
    using namespace revolve::brain;

    timer = new QTimer(this);
    rge = new cpg::RythmGenerationNeuron(1,1,1,0);
    rgf = new cpg::RythmGenerationNeuron(1,1,1,0);

    connect(timer, &QTimer::timeout, this, &RythmGeneratorTimed::generate_output);
    timer->setInterval(interval);
}

RythmGeneratorTimed::~RythmGeneratorTimed()
{
    delete rge;
    delete rgf;
}

void RythmGeneratorTimed::start()
{
    timer->start();
}

revolve::brain::cpg::RythmGenerationNeuron * RythmGeneratorTimed::getRGE()
{
    return rge;
}

revolve::brain::cpg::RythmGenerationNeuron * RythmGeneratorTimed::getRGF()
{
    return rgf;
}

void RythmGeneratorTimed::generate_output()
{
    using namespace revolve::brain;
    float output_e, output_f;

    cpg::real_t delta_time = 0.1;
    cpg::real_t phi_e = rge->getPhi();
    cpg::real_t phi_f = rgf->getPhi();

    std::vector<float> result_e = rge->update({phi_f}, delta_time);
    std::vector<float> result_f = rgf->update({phi_e}, delta_time);

    output_e = result_e[0];
    output_f = result_f[0];

    emit neuron_output(output_e, output_f, phi_e, phi_f);
}



#include "rythmgeneratortimed.moc"
