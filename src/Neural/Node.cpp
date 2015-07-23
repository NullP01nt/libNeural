#include <Neural/Node.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

namespace Neural {

Node::Node() : id(counter++) {
	state = 0.0;
	error = 0.0;
}

void Node::addInputLink(Node& n) {
	addInputLink(n, getRandomWeight());
}

void Node::addInputLink(Node& n, const double w) {
	inputs.push_back(InputLink(n, w, 0.0));
}

void Node::feedForward(void) {
	double sum=0.0;
	// Run through all inputs,
	// Calculate weight*output of input neuron
	for(unsigned i=0; i<inputs.size(); i++) {
		Node& node		= std::get<0>(inputs[i]);
		double weight	= std::get<1>(inputs[i]);
		sum				+= node.getState() * weight;
	}
	setState(XferFunction(sum));
}

void Node::adjustWeights(const double currentError) {
	for(unsigned i = 0; i < inputs.size(); i++) {
		Node& node = std::get<0>(inputs[i]);
		double weight = std::get<1>(inputs[i]);
		double oldDeltaWeight = std::get<2>(inputs[i]);

		double newDeltaWeight = Neural::eta * node.getState() * currentError + Neural::alpha * oldDeltaWeight;
		weight += newDeltaWeight;
	}
}

double Node::getIncomingWeight(Node& n) {
	for(unsigned i = 0; i < inputs.size(); i++) {
		if(n.getID() == std::get<0>(inputs[i]).getID()) {
			return std::get<1>(inputs[i]);
		}
	}
	return 0.0;
}

double Node::XferFunction(double x) {
	return 1.0/(1.0+exp(-x));
}

double Node::XferFunctionD(double x) {
	return exp(x)/pow((1.0+exp(x)),2.0);
}

unsigned Node::counter = 0;

double Node::getRandomWeight(void) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0,1);

	return dis(gen);
}

}; // end_namespace
