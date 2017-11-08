#include <cassert>
#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "network.hpp"
#include "constants.hpp"

using namespace std;


int main(int argc, char* argv[]) 
{
	Network network;
	unsigned int time_sim(0);
	
	//network.run2neurons(time_sim);
	//network.run(time_sim);
	
	//network.saveTimeSpikes();

	network.simulation(C::time_simulation);
	
	
	return 0;
}
