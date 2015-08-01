#include <random>
#include <iostream>
#include <cmath>

#include <Neural/Node.hpp>

namespace Neural {

Node::Node(void) : m_id(counter++) {
	m_output = 0.0;
}

void Node::addInputLink(Node& n) {
	m_inputs.push_back(InputLink(n, getRandomWeight(), 0.0));
	std::cout << "\t" << n.getID() << "\t>>\t" << getID() << std::endl;
}

void Node::feedForward(void) {
	double sum=0.0;
	for(unsigned idx=0; idx<m_inputs.size(); idx++) {
		Node& n = std::get<0>(m_inputs[idx]);
		double weight = std::get<1>(m_inputs[idx]);
		sum += n.getOutput() * weight;
	}
	setOutput(XferFunction(sum));
}

double Node::getInputWeight(const Node& n) const {
	for(unsigned idx = 0; idx < m_inputs.size(); idx++) {
		if(n.getID() == std::get<0>(m_inputs[idx]).getID()) {
			return std::get<1>(m_inputs[idx]);
		}
	}
	return 0.0;
}

void Node::updateInputWeights(void) {
	for(unsigned idx=0; idx < m_inputs.size(); idx++) {
		Node &n = std::get<0>(m_inputs[idx]);
		double newDeltaWeight = Neural::eta * n.getOutput() * m_gradient + Neural::alpha * std::get<2>(m_inputs[idx]);

		std::get<2>(m_inputs[idx]) = newDeltaWeight;
		std::get<1>(m_inputs[idx]) += newDeltaWeight;
	}
}

double Node::XferFunction(const double x) {
	return tanh(x);
}

double Node::XferFunctionD(const double x) {
	return 1.0 - x * x;
}

unsigned Node::counter = 0;

double Node::getRandomWeight(void) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0,1);

	return dis(gen);
}

};
