#pragma once
#include "const.hpp"
#include <vector>
#include <tuple>

namespace Neural {

class Node;
typedef std::tuple<Node&, double, double> InputLink;	// ref, weight, deltaWeight;

class Node {
public:
	Node();

	void addInputLink(Node&);
	void addInputLink(Node&, const double weight);

	void feedForward(void);
	void adjustWeights(const double currentError);
	double getIncomingWeight(Node& n);

	unsigned getID(void) { return id; };
	double getState(void) const { return state; };
	void setState(const double newState) { state = newState; };
	double getError(void) { return error; };

private:
// Static
	static double XferFunction(const double x);
	static double XferFunctionD(const double x);

	static unsigned counter;

// Member
	unsigned id;
	double state;
	double error;

	std::vector<InputLink> inputs;
	
	double getRandomWeight(void);

}; // end_class


}; // end_namespace
