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
	if(inputs.size()!=layers_[0].size()) {
		return;
	}

	for(unsigned l=0; l < layers_.size(); l++) {
		if(l==0) {
			for(unsigned in = 0; in < layers_[0].size(); in++)
				layers_[0][in].setState(inputs[in]);
		} else {
			for(unsigned n = 0; n < layers_[l].size(); n++) {
				layers_[l][n].feedForward();
			}
		}
	}
}

void Network::ReadResults(std::vector<double> &outputs) const {
	outputs.clear();
	for(unsigned o=0; o < layers_.back().size(); o++) {
		outputs.push_back(layers_.back()[o].getState());
	}
}

}; // end_namespace
