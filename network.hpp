#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <random>
#include <algorithm>
#include "Neuron.hpp"
#include "Constants.hpp"


/*! \brief class representing a Network
 * Handles all the neurons of the network and the connections
 */ 

class Network {
	
	private:
		
		std::vector<Neuron> neurons_network;				///represents all the neurons of the network
		std::vector<std::vector<int>> connections;			///represents all the connections between the neurons in the network		
	
		std::ofstream spikes;								///ofstream file that stores of the times spiking of the neurons
		
		///to generate the connections between differents neurons
		std::random_device rd;
		std::mt19937 listRandomNumbers;
		std::uniform_int_distribution <> excitatories;		
		std::uniform_int_distribution <> inhibitories;
		
	public:

		/*! \brief Network constructor 
		 *
		 *  Initializes a new network
		 *  Resizes the vectors with the total number of neurons of the network
		 */	
		Network();
		
		///default destructor
		~Network() = default;
		
		
		/*! \brief create the network
		 * 
		 * 	Fills the fixed.size vector neurons_network with a random neuron in each of its boxes
		 * 	Initializes the tye of the neuron : the first C::n_excitatory neurons are exciatory and the others inhibitory
		 * 
		 */
		void createNetwork();
		
		
		/*! \brief create the connections between the neurons of the network
		 * 
		 *  Fills the fixed-size vetor of vector connections with uniformly distributed values
		 * 	In each box connections[i][j], the number represent the number of connections between the two neurons i and j
		 * 
		 */
		void createConnections(); 
		
		/*! \brief update the whole network
		 * 
		 * 	Updates each neuron of the network
		 * 	Handles the connections between each neurons
		 * 	Saves the time spiking of each neuron 
		 * 
		 * \param t			indicates the number of steps used by the update mehod of Neuron class
		 * 
		 */								
		void update(unsigned long t);
			
		/*! \brief run the simulation for two neurons
		 * 
		 *  Creates two neurons
		 *  Updates them during the time simulation
		 * 	Displays the time when each neuron spikes
		 * 
		 * \param time 		determines the duration of the simulation
		 * 
		 */
		void simulation2neurons(unsigned long time);
		
		/*! \brief run the simulation
		 * 
		 *  Creates a network and the connections associated to it
		 * 	Updates the network at each time step until it reaches the end of the time simulation:
		 * 	each neuron of the network will be updated,
		 * 	their connections will be handle
		 * 	their time spiking is saved
		 * 	
		 * \param time		duration of the simulation
		 * 
		 */  
		void simulation(unsigned long time);
};



#endif
