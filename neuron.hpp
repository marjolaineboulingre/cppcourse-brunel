#ifndef NEURON_H
#define NEURON_H


#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "Constants.hpp"

	
/*! \brief class representing a neuron
 */ 
	
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

		double J;									///Potential transmitted by the neuron when it spikes
		bool poissonActivated;						///Boolean for the activation of the background noise
	
	
	
	public:
	
		/*! \brief Neuron constructor
		 *
		 *  Initializes a neuron with its membrane potential, external current, 
		 * 	number of spikes, potential transmitted and colck at 0
		 * 	Initializes the poissonActivated at true to be able to generate the background noise
		 *  Resizes the buffer for the spikes
		 */
		Neuron();
		
		///default destructor
		~Neuron() = default;
		
		
		///getters
		
		/*! \return neuron's membrane potential  
		 */  
		double getMembranePotential() const;
		
		/*! \return external current
		 */
		double getExtCurrent() const;
		
		/*! \return neuron's last time spike
		 */
		unsigned long getLastTimeSpike() const;
		
		/*! \return neuron's clock
		 */
		unsigned long getClock() const;
		
		/*! \return delay
		 */
		 double getDelay() const;
		
		/*! \return delay_steps
		 */
		 unsigned long getDelaySteps() const;
		
		/*! \return number of times the neuron has spiked
		 */
		int getNbrSpikes() const;		
		
		/*! \brief get the potential transmitted to the neuron targeted after a spike is emitted
		 * 
		 * 	If the neuron is excitatory, return the constant value of the potential associated
		 * 	to an excitatory neuron
		 * 	If the neuron is inhibitory, return the constant value of the potential associated 
		 * 	to an inhibitory neuron
		 * 
		 */
		double getPotentialTransmitted() const;

		
		///setters
		
		/*! \brief set the value of the current
		 */
		void setJ(double i);
		
		/*! \brief set the value of the neuron's membrane potential
		 */
		void setMembranePotential(double mem_pot);
		
		/*! \brief set the external current
		 */
		void setExtCurrent(double c);
		
		/*! \brief set the index of the neuron
		 */
		
		/*! \brief set the value of poissonActivated
		 * 	
		 * 	if it is at false it will destroy the background noise
		 */
		void setPoisson(bool b);
		
		/*! \brief Tests if the neuron spikes
		 * 
		 * 	\return true if the neuron's membrane potential has reached the threshold
		 * 
		 */
		bool isSpiking() const;						
		
		/*! \brief Tests if the neuron is refractory
		 * 
		 * 	\return a boolean to say if the neuron is refractory or not:
		 * 	true if the refractory time has been trespassed,
		 * 	false otherwise
		 * 
		 * \param c				time when we test if the refractory time has been reached	
		 */
		bool isRefractory(long c) const;
					
		 /*! \brief Updates the neuron's membrane potential
		 * 
		 * 	Computes the new neuron's membrane potential according to the general formula
		 * 	Adds random background noise
		 * 	Adds transmitted potential from the ring buffer
		 */
		void updatePotential();	
		 
		 /*! \brief Updates the neuron
		  *	 
		  *  Updates the neuron's membrane potential 
		  *  and store the new potential in the historical of the potentials
		  *  If the neuron is spiking, stores the time when it spikes in the times_historical vector
		  *  and increases the number of spikes of the neuron
		  *  Reinitializes the buffer
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
		 * 	\return			the time converted in steps 
		 */ 
		double convertMs(unsigned long c); 					
		
		
	
};


#endif 
