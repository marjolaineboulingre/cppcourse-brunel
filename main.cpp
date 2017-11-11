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
	network.simulation(C::time_simulation);
	
	return 0;
}
