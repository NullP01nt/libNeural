#include <Neural/Network.hpp>
#include <iostream>

namespace Neural {
double Network::recentAverageSmoothingFactor_ = 100.0;

Network::Network(const std::vector<unsigned> &topology) {
	unsigned num_layers = topology.size();
	biasnode_.setState(1.0);
	for(unsigned l = 0; l<num_layers; l++) {
		layers_.push_back(Layer());

		for(unsigned n = 0; n < topology[l]; n++) {
			layers_[l].push_back(Node());
			std::cout << "[" << l << ":" << layers_[l][n].getID() << "]" << std::endl;
			if(l>=1) {
				for(unsigned np=0; np < layers_[l-1].size(); np++) {
					layers_[l][n].addInputLink(layers_[l-1][np]);
				}
				layers_[l][n].addInputLink(biasnode_);
			}
		}
	}
}

void Network::generateOutput(const std::vector<double> &inputs) {
	for(unsigned i = 0; i < inputs.size(); i++) {
		std::cout << inputs[i] << std::endl;
	}
};

}; // end_namespace
