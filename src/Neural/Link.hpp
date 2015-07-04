#pragma once

namespace Neural {
class Node;
class Link {
public:
	Link(Node& left, Node& right);

	Node& left_neuron_;
	Node& right_neuron_;
	double weight(void) const { return weight_;};
//	Neural::Node left_neuron(void) const { return left_neuron_; };
//	Neural::Node right_neuron(void) const { return right_neuron_; };

private:
//	Neural::Node left_neuron_;
//	Neural::Node right_neuron_;

	double weight_;
	double delta_weight_;
}; // end_class
}; // end_namespace
