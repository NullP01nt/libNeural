#include <TrainingData.hpp>

TrainingData::TrainingData(const std::string filename) {
	dataFile.open(filename.c_str());
}

void TrainingData::getTopology(std::vector<unsigned> &topo) {
	std::string line, label;
	getline(dataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(isEOF() || label.compare("topo:") != 0) {
		abort();
	}

	while(!ss.eof()) {
		unsigned n;
		ss >> n;
		topo.push_back(n);
	}
}

unsigned TrainingData::getNextInputs( std::vector<double> &in) {
	std::string line, label;
	getline(dataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(isEOF() || label.compare("i:") != 0) {
		abort();
	}

	while(!ss.eof()) {
		double n;
		ss >> n;
		in.push_back(n);
	}
	return in.size();
}

unsigned TrainingData::getNextTargets( std::vector<double> &tgt) {
	std::string line, label;
	getline(dataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(isEOF() || label.compare("o:") != 0) {
		abort();
	}

	while(!ss.eof()) {
		double n;
		ss >> n;
		tgt.push_back(n);
	}
	return tgt.size();
}
