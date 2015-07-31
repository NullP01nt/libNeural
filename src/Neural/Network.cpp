#include <Neural/Network.hpp>
#include <iostream>
#include <cassert>

namespace Neural {
double Network::recentAverageSmoothingFactor_ = 100.0;

Network::Network(const std::vector<unsigned> &topology) {
	unsigned num_layers = topology.size();
	biasnode_.setState(1.0);
	for(unsigned lIdx = 0; lIdx<num_layers; lIdx++) {
		layers_.push_back(Layer());

		for(unsigned n = 0; n < topology[lIdx]; n++) {
			layers_[lIdx].push_back(Node());
			std::cout << "[" << lIdx << ":" << layers_[lIdx][n].getID() << "]" << std::endl;
			if(lIdx>=1) {
				for(unsigned np=0; np < layers_[lIdx-1].size(); np++) {
					layers_[lIdx][n].addInputLink(layers_[lIdx-1][np]);
				}
				layers_[lIdx][n].addInputLink(biasnode_);
			}
		}
	}
}

void Network::generateOutput(const std::vector<double> &inputs) {
	assert(inputs.size()==layers_[0].size());

	for(unsigned lIdx=0; lIdx < layers_.size(); lIdx++) {
		for(unsigned n = 0; n < layers_[lIdx].size(); n++) {
			if(lIdx==0) {
				layers_[lIdx][n].setState(inputs[n]);
			} else {
				layers_[lIdx][n].feedForward();
			}
		}
	}
}

void Network::BackProp(const std::vector<double> &outputs) {

	assert(outputs.size()==layers_[layers_.size()-1].size());

	for(unsigned lIdx=(layers_.size()-1); lIdx>0; lIdx--) {
		for(unsigned nIdx=0; nIdx < layers_[lIdx].size(); nIdx++) {
			double state = layers_[lIdx][nIdx].getState();
			double error;

			if(lIdx==(layers_.size()-1)) {
				error = state * (1.0-state) * (outputs[nIdx]-state);
			} else {
				double sum = 0.0;
				for(unsigned nIx=0; nIx < layers_[lIdx+1].size(); nIx++) {
					sum+= layers_[lIdx+1][nIx].getIncomingWeight(layers_[lIdx][nIdx]) * layers_[lIdx+1][nIx].getError();
				}
				error = state * (1.0-state) * sum;
			}
			layers_[lIdx][nIdx].adjustWeights(error);
		}
	}
}

void Network::ReadResults(std::vector<double> &outputs) const {
	if(outputs.size()>0)
		outputs.clear();
	for(unsigned oIdx=0; oIdx < layers_.back().size(); oIdx++) {
		outputs.push_back(layers_.back()[oIdx].getState());
	}
}
	
void Network::learnPattern(const std::vector<double> &inputs, const std::vector<double> &targets) {
	generateOutput(inputs);
	BackProp(targets);
}

}; // end_namespace
