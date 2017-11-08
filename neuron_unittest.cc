#include "gtest/gtest.h"
#include "neuron.hpp"
#include <cmath>


TEST(NeuronTest, Membrane) {
	
	Neuron neuron;
	neuron.setExtCurrent(1.0);
	neuron.setPoisson(false);
	neuron.update(1);
	
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMembranePotential());
}


TEST(NeuronTest, SpikeTime) {
	
	Neuron neuron;
	neuron.setPoisson(false);
	neuron.setExtCurrent(1.01);
	///Waiting for first spike (that occurs at 93,4 ms)
	neuron.update(923);
	EXPECT_EQ(0, neuron.getNbrSpikes());
	neuron.update(1);
	EXPECT_EQ(1, neuron.getNbrSpikes());
	EXPECT_LE(C::Vth, neuron.getMembranePotential());
	
	/*///Waiting for second spike (that occurs at 186,8ms)
	neuron.update(943);
	EXPECT_EQ(1, neuron.getNbrSpikes());
	neuron.update(1);
	EXPECT_EQ(2, neuron.getNbrSpikes());
*/
}

TEST(NeuronTest, IsRefractory) {
	
	Neuron neuron;
	
	ASSERT_FALSE (neuron.isRefractory(1.0));
}

/*TEST(TwoNeurons, WithPSSpike) {
	
	Neuron neuron1, neuron2;
	int delay = 15;
	neuron1.setExtCurrent(1.01);
	neuron2.setExtCurrent(1.01);
	
	for(auto i=0; i<1869+delay; i++)  {
		neuron1.update(1);
		
		if (neuron1.isSpiking()) { 
			
			neuron2.receive_spike(i + static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getMembranePotential());
		}
	}
	EXPECT_EQ(0, neuron2.getNbrSpikes());
	neuron2.update(1);
	EXPECT_EQ(0, neuron2.getMembranePotential());
	EXPECT_EQ(1, neuron2.getNbrSpikes());

}*/
			
			


int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


