#include <iostream>
#include "Link.hpp"
#include "Node.hpp"

namespace Neural {
Link::Link(Node& left, Node& right) : left_neuron_(left), right_neuron_(right), weight_(0.5) {
	std::cout << "Link [" << left_neuron_.id() <<", "<<right_neuron_.id()<<"]\t";
	std::cout << left_neuron_.output() << "\t";
	std::cout << right_neuron_.output() << std::endl;
}
};
