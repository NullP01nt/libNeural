#include <Neural/Node.hpp>
#include <iostream>
#include <cmath>

namespace Neural {
unsigned Node::counter = 0;

Node::Node() : id_(counter++) {
	std::cout << "Node created [" << id_ << "]" << std::endl;
	output_ = 0.0;
}

void Node::AddInputLink(Neural::Link& link) {
	input_links_.push_back(link);
}

void Node::CalculateOutput(void) {
	double sum=0.0;
	// Run through all inputs,
	// Calculate weight*output of input neuron
	// sum += _;
	sum+= input_links_.back().left_neuron_.output()*input_links_.back().weight();
	output_ = XferFunction(sum);
}

double Node::XferFunction(double x) {
	return 1/(1+exp(-x));
}

double Node::XferFunctionD(double x) {
	return exp(x)/pow((1+exp(x)),2);
}
}; // end_namespace
