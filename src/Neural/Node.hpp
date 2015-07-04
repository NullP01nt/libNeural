#pragma once

#include "Link.hpp"
#include <vector>

namespace Neural {

class Node {
public:
	Node(void);

	unsigned id(void) { return id_; };

	void CalculateOutput(void);

	double output(void) const { return output_; };
	void set_output(double out) { output_ = out; };

private:
// Static
	static double XferFunction(const double x);
	static double XferFunctionD(const double x);
	static unsigned counter;

// Member
	unsigned id_;
	double output_;
	std::vector<Link> input_links_;

}; // end_class

}; // end_namespace
