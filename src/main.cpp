#include <iostream>
#include "Neural/Network.hpp"
#include "Neural/Node.hpp"
#include "TrainingData.hpp"
#include <string>
#include <cassert>


void printVector(const std::string pref, const std::vector<double> &data) {
	std::cout << pref <<":";
	for(unsigned i = 0; i < data.size(); i++) {
		std::cout << " " << data[i];
	}
	std::cout << std::endl;
}

int main(void) {

	std::vector<std::string> datasets = std::vector<std::string>();
	datasets.push_back("util/DS_AND.txt");
	datasets.push_back("util/DS_OR.txt");
	datasets.push_back("util/DS_NAND.txt");
	datasets.push_back("util/DS_NOR.txt");
	datasets.push_back("util/DS_XOR.txt");
	datasets.push_back("util/DS_XNOR.txt");

	for(std::string ds : datasets) {
		std::cout << ds << std::endl;
		TrainingData td(ds);
		std::vector<unsigned> topo;
		td.getTopology(topo);

		Neural::Network mynet(topo);

		std::vector<double> inputs, targets;//, outputs;
		unsigned trainingPass = 0;

		while(!td.isEOF()) {
			trainingPass++;
			std::cout << trainingPass << ";";
			if(td.getNextInputs(inputs) != topo[0]) {
				std::cout << -1 << std::endl;
				break;
			}
			mynet.feedForward(inputs);
//			mynet.getResults(outputs);
			td.getNextTargets(targets);
			assert(targets.size()==topo.back());
			mynet.backProp(targets);
			std::cout << mynet.getRecentAvgError() << std::endl;
		}
	}
/*
	TrainingData td("trainingData.txt");
	std::vector<unsigned> topo;
	td.getTopology(topo);

	Neural::Network mynet(topo);


	std::vector<double> inputs, targets, outputs;
	unsigned trainingPass = 0;

	while(!td.isEOF()) {
		trainingPass++;
		std::cout << std::endl << "Pass " << trainingPass;
		if(td.getNextInputs(inputs) != topo[0])
			break;

		printVector(": Inputs", inputs);
		mynet.feedForward(inputs);

		mynet.getResults(outputs);
		printVector("Outputs", outputs);

		td.getNextTargets(targets);
		printVector("Targets", targets);
		assert(targets.size()==topo.back());

		mynet.backProp(targets);

		std::cout << "Net recent avg error: " << mynet.getRecentAvgError() << std::endl;
	}

	std::cout << std::endl << "Done" << std::endl;
*/
	return 0;
}
