#include <iostream>
#include "Neural/Network.hpp"
#include "Neural/Node.hpp"
#include <string>

void printVector(const std::string pref, const std::vector<double> &data) {
	std::cout << pref <<":";
	for(unsigned i = 0; i < data.size(); i++) {
		std::cout << "\t" << data[i];
	}
	std::cout << std::endl;
}

int main(void) {
	std::vector<unsigned> topo = {2, 4, 1};
	Neural::Network mynet(topo);

	std::vector<double> inputs = { 0.0, 0.0 };
	std::vector<double> outputs;
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	printVector("I", inputs);
	printVector("O", outputs);
	std::cout << std::endl;

	inputs[0]=0.0;
	inputs[1]=1.0;
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	printVector("I", inputs);
	printVector("O", outputs);
	std::cout << std::endl;
	
	inputs[0]=1.0;
	inputs[1]=0.0;
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	printVector("I", inputs);
	printVector("O", outputs);
	std::cout << std::endl;

	inputs[0]=1.0;
	inputs[1]=1.0;
	mynet.generateOutput(inputs);
	mynet.ReadResults(outputs);
	printVector("I", inputs);
	printVector("O", outputs);
	std::cout << std::endl;

	return 0;
}
