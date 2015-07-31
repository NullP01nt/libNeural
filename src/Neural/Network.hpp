#pragma once
#include <vector>
#include "const.hpp"
#include "Node.hpp"

namespace Neural {
typedef std::vector<Node> Layer;

class Network {
public:
	Network(const std::vector<unsigned> &nettopology);

	void generateOutput(const std::vector<double> &inputs);
	void BackProp(const std::vector<double> &targets);
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

}; // end_namespace
