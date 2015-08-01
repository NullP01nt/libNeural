#include <iostream>
#include <cassert>
#include <cmath>

#include <Neural/Network.hpp>
#include <Neural/Node.hpp>

namespace Neural {

Network::Network(void) {
	m_biasnode.setOutput(1.0);
}

Network::Network(const std::vector<unsigned> &topo) {
	m_biasnode.setOutput(1.0);

	unsigned numLayers = topo.size();
	for(unsigned lIdx = 0; lIdx < numLayers; lIdx++) {
		m_layers.push_back(Layer());
		unsigned numNodes = topo[lIdx];
		for(unsigned nIdx = 0; nIdx < numNodes; nIdx++) {
			m_layers[lIdx].push_back(Node());
			std::cout << "["<<lIdx<<":"<<m_layers[lIdx].back().getID()<<"]" << std::endl;
			if(lIdx>0) {
				unsigned numNodesPrev = topo[lIdx-1];
				for(unsigned pnIdx = 0; pnIdx < numNodesPrev; pnIdx++) {
					m_layers[lIdx][nIdx].addInputLink(m_layers[lIdx-1][pnIdx]);
				}
				m_layers[lIdx][nIdx].addInputLink(m_biasnode);
			}
		}
	}
}

void Network::feedForward(const std::vector<double> &inputs) {
	assert(inputs.size()==m_layers[0].size());

	for(unsigned lIdx=0; lIdx < m_layers.size(); lIdx++) {
		for(unsigned nIdx=0; nIdx < m_layers[lIdx].size(); nIdx++) {
			if(lIdx==0) {
				m_layers[lIdx][nIdx].setOutput(inputs[nIdx]);
			} else {
				m_layers[lIdx][nIdx].feedForward();
			}
		}
	}
}

void Network::backProp(const std::vector<double> &targets) {
	Layer &outputLayer = m_layers.back();
	
	assert(targets.size()==outputLayer.size());
	m_error = 0.0;

	// Calculate overall net error (RMS of output neuron errors)
	for(unsigned nIdx = 0; nIdx < outputLayer.size(); nIdx++) {
		double delta = targets[nIdx] - outputLayer[nIdx].getOutput();
		m_error += delta*delta; // sum error squares
	}
	m_error /= outputLayer.size(); // average
	m_error = sqrt(m_error); // RMS

	// Implement a recent average measurement
	m_recentAvgError = (m_recentAvgError * m_recentAvgSmoothFactor + m_error) / (m_recentAvgSmoothFactor+1.0);

	// Calculate output layer gradients
	for(unsigned nIdx = 0; nIdx < outputLayer.size(); nIdx++) {
		double delta = targets[nIdx] - outputLayer[nIdx].getOutput();
		double gradient = delta * Node::XferFunctionD(outputLayer[nIdx].getOutput());
		outputLayer[nIdx].setGradient(gradient);
	}

	// Calculate hidden layer gradients
	for(unsigned lIdx = m_layers.size() - 2; lIdx > 0; lIdx--) {
		Layer &currentLayer = m_layers[lIdx];
		Layer &nextLayer = m_layers[lIdx+1];

		for(unsigned nIdx = 0; nIdx < currentLayer.size(); nIdx++) {
			double sum = 0.0;
			for(unsigned idx=0; idx < nextLayer.size(); idx++) {
				sum += nextLayer[idx].getInputWeight(currentLayer[nIdx]) * nextLayer[idx].getGradient();
			}
			double gradient = sum * Node::XferFunctionD(currentLayer[nIdx].getOutput());
			currentLayer[nIdx].setGradient(gradient);
		}
	}

	// Update link weights
	for(unsigned lIdx=m_layers.size()-1; lIdx > 0; lIdx--) {
		for(unsigned nIdx=0; nIdx < m_layers[lIdx].size(); nIdx++) {
			m_layers[lIdx][nIdx].updateInputWeights();
		}
	}

}

void Network::getResults(std::vector<double> &results) const {
	results.clear();

	for(unsigned nIdx=0; nIdx < m_layers.back().size(); nIdx++) {
		results.push_back(m_layers.back()[nIdx].getOutput());
	}
}

double Network::m_recentAvgSmoothFactor = 100.0;
};
