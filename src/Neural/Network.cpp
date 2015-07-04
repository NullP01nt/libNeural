#include "Network.hpp"
#include <iostream>

namespace Neural {

double Network::recentAverageSmoothingFactor_ = 100.0;

Network::Network(const std::vector<unsigned> &nettopology) {
	std::cout << "Hello, Network!" << std::endl;
	unsigned num_layers = nettopology.size();
	for(unsigned l = 0; l<num_layers; l++) {
		std::cout << "Layer " << l <<":\t" << nettopology[l] << std::endl;
	}
}

}; //end_namespace
