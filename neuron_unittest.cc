#include "gtest/gtest.h"
#include "neuron.hpp"
#include <cmath>


TEST(NeuronTest, Membrane) {
	
	Neuron neuron;
	neuron.setExtCurrent(1.0);
	///We set the poissonActivated at false to destroy the background noise
	neuron.setPoisson(false);
	neuron.update(1);
	
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMembranePotential());
}


TEST(NeuronTest, SpikeTime) {
	
	Neuron neuron;
	neuron.setPoisson(false); ///poissonActivated at false to destroy the background noise
	neuron.setExtCurrent(1.01);
	
	///Waiting for first spike (that occurs at 93,4 ms)
	neuron.update(923);
	EXPECT_EQ(0, neuron.getNbrSpikes());
	
	///At 934 steps the neuron has spiked
	neuron.update(1);
	EXPECT_EQ(1, neuron.getNbrSpikes());
	EXPECT_LE(C::Vth, neuron.getMembranePotential());
}

TEST(NeuronTest, IsRefractory) {
	
	Neuron neuron;
	
	ASSERT_FALSE (neuron.isRefractory(1.0));
}

TEST(TwoNeurons, WithPSSpike) {
	
	Neuron neuron1, neuron2;
	neuron1.setPoisson(false);
	neuron2.setPoisson(false);
	neuron1.setExtCurrent(1.01);


	for(auto i=0; i<1869+ neuron1.getDelaySteps(); i++)  {
		
		neuron1.update(1);
		
		if (neuron1.isSpiking()) { 
			
			neuron2.receive_spike(i + neuron2.getDelaySteps(), neuron1.getPotentialTransmitted());
			
			neuron1.update(1);
			
			EXPECT_EQ(0.0, neuron1.getMembranePotential());
		}
		
	
	neuron2.update(1);
	
	}

	EXPECT_NEAR(0.2, neuron2.getMembranePotential(), 0.2);

}


TEST(NeuronTest, StandAloneSimulation) {
	Neuron neuron;
	neuron.setPoisson(false);
	neuron.setExtCurrent(1.01);
	neuron.update(4000);
	EXPECT_EQ(4, neuron.getNbrSpikes());
}


TEST(NeuronTest, PositiveInput) {
	Neuron neuron;
	neuron.setPoisson(false);
	neuron.setExtCurrent(1.0);
	
	neuron.update(10000);
	///The membrane potential should tend to 20 but never reach it
	///the neuron should never spike
	EXPECT_EQ(0, neuron.getNbrSpikes());
	EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getMembranePotential()));
	
	neuron.setExtCurrent(0.0);
	///The membrane potential should tend towards 0
	neuron.update(2000);
	EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);
	
}


///We run all the tests
int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


