#pragma once
#include <vector>
#include "Node.hpp"

namespace Neural {
typedef std::vector<Node> Layer;

class Network {
public:
	Network(const std::vector<unsigned> &nettopology);
	void FeedForward(const std::vector<double> &inputs);
	void BackPropagate(const std::vector<double> &targets);
	void ReadResults(std::vector<double> &outputs) const;

	double error(void) const { return error_; };
	double recentAverageError(void) const { return recentAverageError_; };
private:
	std::vector<Layer> layers_;
	Neural::Node biasnode_;
	double error_;
	double recentAverageError_;
	static double recentAverageSmoothingFactor_;
}; // end_class

const double eta = 0.15;
const double alpha = 0.50;
}; // end_namespace
