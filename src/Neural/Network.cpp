#include <Neural/Network.hpp>
#include <iostream>

namespace Neural {
double Network::recentAverageSmoothingFactor_ = 100.0;

Network::Network(const std::vector<unsigned> &topology) {
	unsigned num_layers = topology.size();
	biasnode_.setState(1.0);
	for(unsigned l = 0; l<num_layers; l++) {
		std::cout << "Layer " << l <<":\t" << topology[l] << std::endl;
		layers_.push_back(Layer());

		for(unsigned n = 0; n < topology[l]; n++) {
			layers_.back().push_back(Node());
			std::cout << "Made a Neural Node!" << layers_.back().back().getID() << std::endl;
		}
	}
}
}; // end_namespace
