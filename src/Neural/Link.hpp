#pragma once

namespace Neural {

class Node;
class Link {
public:
	Link();

	unsigned left_neuron_id(void) const { return left_neuron_id_; };
	unsigned right_neuron_id(void) const { return right_neuron_id_; };

private:
	unsigned left_neuron_id_;
	unsigned right_neuron_id_;

	double weight_;
	double delta_weight_;
}; // end_class

}; // end_namespace
