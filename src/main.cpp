#include <iostream>
#include "Neural/Network.hpp"
#include "Neural/Node.hpp"
#include "TrainingData.hpp"
#include <string>


void printVector(const std::string pref, const std::vector<double> &data) {
	std::cout << "\t" << pref <<":";
	for(unsigned i = 0; i < data.size(); i++) {
		std::cout << "\t" << data[i];
	}
	std::cout << std::endl;
}

int main(void) {
	TrainingData td("trainingData.txt");
	std::vector<unsigned> topo;
	td.getTopology(topo);

	Neural::Network mynet(topo);

	std::vector<double> inputs, targets, outputs;
	unsigned trainingPass = 0;
	unsigned numIn, numTgt;

	while(!td.isEOF()) {
		++trainingPass;
		std::cout << std::endl << "Pass " << trainingPass << std::endl;

		numIn = td.getNextInputs(inputs);
		numTgt = td.getNextTargets(targets);

		if(numIn != topo[0])
			break;

		if(numTgt != topo.back())
			break;

		printVector("Inputs", inputs);
		printVector("Targets", targets);
		mynet.learnPattern(inputs, targets);
		mynet.ReadResults(outputs);
		printVector("Outputs", outputs);
	}

	std::cout << std::endl << "Done" << std::endl;

	return 0;
}
