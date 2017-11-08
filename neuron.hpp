#ifndef NEURON_H
#define NEURON_H


#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "Constants.hpp"

	
	
class Neuron {
	
	private:
		
		double membrane_potential; 					///Membrane potential
		double Iext;								///External current
		unsigned long t_spike;						///time of last spike
		unsigned long n_spikes;						///number of spikes
		unsigned long clock;						///internal time of the neuron
		unsigned long delay_steps; 					///synaptic delay in steps
		
		std::vector<double> potential_historical;	///historical of the mebrane potential
		std::vector<int> times_historical;			///historical of the times spikes
		std::vector<double> spike_buff;				///Input buffer for spikes
		
		//bool isExcitatory;							///defines the type of the neuron (excitatory or inhibitory)
		double J;
		bool poissonActivated;
		
		size_t index;
	
	
	
	public:
	
		/*! \brief Neuron constructor
		 *
		 *  Initializes a neuron with 
		 */
		Neuron();
		
		///default destructor
		~Neuron() = default;
		
		
		///getters
		
		///get the neuron's membrane potential 
		double getMembranePotential() const;
		
		///get the external current
		double getExtCurrent() const;
		
		///get the neuron's last time spike
		unsigned long getLastTimeSpike() const;
		
		///get the neuron's clock
		unsigned long getClock() const;
		
		///get the delay
		double getDelay() const;
		
		///get the number of times the neuron has spiked
		int getNbrSpikes() const;
		
		/*! \brief get the neuron's type
		 *
		 * 	Return true if it's excitatory, false if it's inhibitory 
		 * 
		 */
		//bool getIsExcitatory() const;
		
		
		/*! \brief get the potential transmitted to the neuron targeted after a spike is emitted
		 * 
		 * 	If the neuron is excitatory, return the constant value of the potential associated
		 * 	to an excitatory neuron
		 * 	If the neuron is inhibitory, return the constant value of the potential associated 
		 * 	to an inhibitory neuron
		 * 
		 */
		double getPotentialTransmitted() const;
		
		/*! \brief get all the times when the neuron spikes
		 * 
		 * 	Returns a vector filled with all the times spike of the neuron
		 * 
		 */ 
		//std::vector<int> getTimesSpike() const;

		
		///setters
		
		void setJ(double i);
		
		void setMembranePotential(double mem_pot);
		
		void setExtCurrent(double c);
		
		void setIndex(size_t ind);
		
		//void setExcitatory(bool c);
		
		void setPoisson(bool b);
		
		/*! \brief Tests if the neuron spikes
		 * 
		 * 	Returns true if the neuron's membrane potential has reached the threshold
		 * 
		 */
		bool isSpiking() const;						
		
		/*! \brief Tests if the neuron is refractory
		 * 
		 * 	Returns a boolean to say if the neuron is refractory or not:
		 * 	returns true if the refractory time has been trespassed,
		 * 	returns false otherwise
		 * 
		 * \param c				time when we test if the refractory time has been reached	
		 */
		bool isRefractory(long c) const;
					
		 /*! \brief Updates the neuron's membrane potential
		 * 
		 * 	Computes the new neuron's membrane potential according to the general formula
		 * 	Adds random background noise
		 * 	Adds transmitted potential from the ring buffer
		 * 
		 */
		void updatePotential();
		
		
		 
		 /*! \brief Updates the neuron
		  *	 
		  *  Updates the neuron's membrane potential 
		  *  If the neuron is spiking, stores the time when it spikes in the times_historical vector
		  * 
		  * \param steps		determines how many times the function needs to update the neuron
		  * 
		  */
		void update(unsigned long steps);
		
		
		/*! \brief Receives an incoming skipe
		 * 
		 * 	Adds a transmission to the buffer spike_buff
		 * 	
		 * 
		 * \param arrival 		time arrival of the transmitted spike 
		 * \param potential		potential transmitted from the spiking neuron
		 * 
		 */ 
		void receive_spike(unsigned long arrival, double potential); 

		/*! \brief convert a time in ms in steps
		 * 
		 *  \param c 		time that need to be convert in steps
		 */ 
		double convertMs(unsigned long c); 					
		
		
	
};


#endif 
