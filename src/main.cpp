#include <iostream>
#include "Neural/Network.hpp"
#include "Neural/Node.hpp"

int main(void) {
	std::vector<unsigned> topo = {2, 4, 1};
	std::vector<double> inputs = { 1.0, 0.0 };
	std::vector<double> outputs;
	Neural::Network mynet(topo);
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	for(unsigned od = 0; od < outputs.size(); od++) {
		std::cout << outputs[od] << std::endl;
	}
	std::cout << std::endl;
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	for(unsigned od = 0; od < outputs.size(); od++) {
		std::cout << outputs[od] << std::endl;
	}
	return 0;
}
