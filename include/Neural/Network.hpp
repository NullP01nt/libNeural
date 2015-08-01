#pragma once

#include <vector>

#include <Neural/Node.hpp>

namespace Neural {

typedef std::vector<Node> Layer;

class Network {
public:
	Network(const std::vector<unsigned> &topology);
	void feedForward(const std::vector<double> &inputs);
	void backProp(const std::vector<double> &targets);
	void getResults(std::vector<double> &results) const;

	double getRecentAvgError(void) const { return m_recentAvgError; }

private:
	std::vector<Layer> m_layers;
	Node	m_biasnode;
	double	m_error;
	double	m_recentAvgError;
	static	double m_recentAvgSmoothFactor;
};

};
