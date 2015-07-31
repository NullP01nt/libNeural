#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <iostream>

class TrainingData {
public:
	TrainingData(const std::string filename);
	bool isEOF(void) { return dataFile.eof(); }
	void getTopology(std::vector<unsigned> &topo);
	unsigned getNextInputs(std::vector<double> &in);
	unsigned getNextTargets(std::vector<double> &tgt);

private:
	std::ifstream dataFile;
};
