#include <iostream>
#include <string>
#include <cassert>

#include <NeuralNetwork.hpp>
#include <NeuralNode.hpp>
#include <TrainingData.hpp>


void printVector(const std::string pref, const std::vector<double> &data) {
	std::cout << pref <<":";
	for(unsigned i = 0; i < data.size(); i++) {
		std::cout << " " << data[i];
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

	return 0;
}
