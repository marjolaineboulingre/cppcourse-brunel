#include <iostream>
#include <fstream>
#include <cassert>
#include "Constants.hpp"
#include "Network.hpp"


Network::Network() 
	: 
	listRandomNumbers(rd()),
	excitatories(0, C::n_excitatory - 1),
	inhibitories(C::n_excitatory-1, C::n_total-1)
{		
		connections.resize(C::n_total);
		
		for(int i=0; i < C::n_total; ++i)
		{
			connections[i].resize(C::n_total);
		}
}


void Network::createNetwork()
{
	///creation of the excitatories neurons
	for(int i=0; i < C::n_excitatory; ++i)
	{ 
		Neuron n;
		n.setJ(C::Je); 	///set the potential transmitted with the specific value for an excitatory neuron
		neurons_network.push_back(n);
	}
	
	///creatino of the inhibitories neuron
	for(int i=C::n_inhibitory ; i < C::n_total; ++i)
	{ 
		Neuron n;	
		n.setJ(C::Ji);	///set the potential transmitted with the specific value for an inhibitory neuron
		neurons_network.push_back(n);
	}
}



void Network::createConnections() {
	
	for(int target=0; target < C::n_total; ++target)
	{
		for(size_t i=0; i<C::c_excitatory; ++i)
			{
				auto source = excitatories(listRandomNumbers);
				connections[source][target] += 1;
			}
			
			for(size_t i = C::c_excitatory; i <C::c_total; ++i)
			{
				auto source = inhibitories(listRandomNumbers);
				connections[source][target] += 1;
			}
	}
}


void Network::update(unsigned long t) {	
	
	for(int n=0; n < C::n_total; ++n) 
	{
		neurons_network[n].update(1);
		
		if ( neurons_network[n].isSpiking())
		{
			spikes << t <<'\t' << n << std::endl;
				
			for(size_t i=0; i < connections[n].size(); ++i)
			{
				if(connections[n][i] > 0)
				{
					neurons_network[i].receive_spike(t, neurons_network[n].getPotentialTransmitted()*connections[n][i]);
				}
			}
		}
	}
	
	
}



void Network::simulation2neurons(unsigned long time) {
	
	Neuron n1;
	Neuron n2;
	
	int i_start = 1000 ;
	int i_stop = 4000;
	double Iext = 1.01;
	
	for(int t=0; t<=time; ++t)
	{
		if((t>=i_start) and (t<=i_stop)) 
		{
			n1.setExtCurrent(Iext);
		}
		else
		{
			n1.setExtCurrent(0.0);
		}
		n1.update(1);
		n2.update(1);
		
		if (n1.isSpiking()) {
			std::cout << "Spikes 1 at : " << n1.convertMs(n1.getLastTimeSpike()) << std::endl;
			n2.receive_spike( n1.getLastTimeSpike() + n1.getDelay(), n1.getMembranePotential());
		}
		
		if(n2.isSpiking()) {
			std::cout << "Spikes 2 at: " << n2.convertMs(n2.getLastTimeSpike()) << std::endl;
		
		}
	}	
}

void Network::simulation(unsigned long time) {
	
	unsigned long t(0);
	
	createNetwork();
	createConnections();

	std::cout << "start of the simulation" << std::endl;

	spikes.open("../spikes.gdf"); 
	
	while(t < time) 
	{
		update(t);
		++t;	
	}
	
	spikes.close();
	
	std::cout << "end of the simulation" << std::endl;
}

