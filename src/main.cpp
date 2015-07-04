#include <iostream>
#include "Neural/Network.hpp"

int main(void) {
	std::vector<unsigned> topo = {2, 4, 1};
	Neural::Network mynet(topo);
	return 0;
}
