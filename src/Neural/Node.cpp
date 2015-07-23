#include <Neural/Node.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

namespace Neural {
unsigned Node::counter = 0;

Node::Node() : id(counter++) {
	state = 0.0;
	error = 0.0;
}

void Node::addInputLink(Node& n) {
	addInputLink(n, getRandomWeight());
}

void Node::addInputLink(Node& n, const double w) {
	inputs.push_back(std::pair<Node&, double>(n,w));
}

void Node::feedForward(void) {
	double sum=0.0;
	// Run through all inputs,
	// Calculate weight*output of input neuron
	sum+= inputs.back().first.getState() * inputs.back().second;
	setState(XferFunction(sum));
}

double Node::XferFunction(double x) {
	return 1/(1+exp(-x));
}

double Node::XferFunctionD(double x) {
	return exp(x)/pow((1+exp(x)),2);
}

double Node::getRandomWeight(void) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0,1);

	return dis(gen);
}

}; // end_namespace
