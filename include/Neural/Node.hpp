#pragma once
#include <vector>
#include <tuple>

#include <Neural/const.hpp>

namespace Neural {

class Node;
typedef std::tuple<Node&, double, double> InputLink;	// ref, weight, deltaWeight

class Node {
public:
	Node(void);

	void addInputLink(Node&);

	void feedForward(void);

	unsigned	getID(void) const { return m_id; }
	double		getOutput(void) const { return m_output; }
	void		setOutput(const double newOut) { m_output = newOut; }

	double	getGradient(void) const { return m_gradient; }
	void	setGradient(const double grad) { m_gradient = grad; }

	double getInputWeight(const Node& n) const;
	void updateInputWeights(void);

	static double XferFunction(const double x);
	static double XferFunctionD(const double x);

private:
	double getRandomWeight(void);
	static unsigned counter;

	unsigned m_id;
	double m_output;
	double m_gradient;

	std::vector<InputLink> m_inputs;
};

}
