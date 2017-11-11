#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "neuron.hpp" 

using namespace std;
	
Neuron::Neuron()
	:
	membrane_potential(0.0),
	Iext(0.0),
	t_spike(0),
	n_spikes(0),
	clock(0),
	J(0), 
	poissonActivated(true)	
	
{
	delay_steps = static_cast<unsigned long>(ceil(C::delay/C::h));
	spike_buff.resize(delay_steps+1, 0.0);
	times_historical.resize(0);	
	assert(spike_buff.size() == delay_steps + 1);
}
	

///getters
	
double Neuron::getMembranePotential() const {
	return membrane_potential;
}

double Neuron::getExtCurrent() const {
	return Iext;
}

unsigned long Neuron::getClock() const {
	return clock;
}

unsigned long Neuron::getLastTimeSpike() const {
	if ( !times_historical.empty())
	 {
		return times_historical.back();
	}
}

double Neuron::getDelay() const {
	return C::delay;
}

int Neuron::getNbrSpikes() const {
	return n_spikes;
}


double Neuron::getPotentialTransmitted() const {
	return J;
}

unsigned long Neuron::getDelaySteps() const {
	return delay_steps;
}

///setters
		
void Neuron::setMembranePotential(double mem_pot) {
	membrane_potential = mem_pot;
}

void Neuron::setExtCurrent(double c) {
	Iext = c;
}	

void Neuron::setJ(double i) {
	J = i;
}

void Neuron::setPoisson(bool b) {
	poissonActivated = b;
}


	
///methods concerning the state of the neuron

bool Neuron::isSpiking() const {
	return getMembranePotential() >= C::Vth;
		 
}

bool Neuron::isRefractory(long c) const {
	return !times_historical.empty() && (c - times_historical.back()) < C::refractory_time;
}


///Evolution of the neuron

void Neuron::updatePotential() {
	
		membrane_potential = C::c1 * membrane_potential + C::c2 * Iext;
		membrane_potential += spike_buff[clock % delay_steps];
		
		///generate the background noise
		static random_device rd;
		static mt19937 gen(rd());
		static poisson_distribution<> poisson(2);
		
		membrane_potential += poisson(gen) *C::Je*poissonActivated;
}
	

void Neuron::update(unsigned long steps)
{	
	const auto t_stop = steps + clock;
	
	while(clock < t_stop)
	{
		if (isRefractory(clock))
		{
			setMembranePotential(0.0);
		} else {
			updatePotential();
			potential_historical.push_back(membrane_potential);
			
		
			if (isSpiking()) 
			{
				times_historical.push_back(clock);
				++ n_spikes;
			}
		}
		spike_buff[ clock % delay_steps] = 0.0;
		++clock;
	}
	
}


void Neuron::receive_spike(unsigned long arrival, double potential) {
	const size_t t_case = arrival%(spike_buff.size());
	
	assert(t_case < spike_buff.size());
	
	spike_buff[t_case] += potential;
}


double Neuron::convertMs(unsigned long c) {
	return c*C::h;
}
