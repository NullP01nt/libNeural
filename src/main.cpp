#include <iostream>
#include <Neural/Network.hpp>
#include <Neural/Node.hpp>
#include <Neural/Link.hpp>

int main(void) {
	std::vector<unsigned> topo = {2, 4, 1};
	Neural::Network mynet(topo);
	Neural::Node a;
	Neural::Node b;
	a.set_output(1.0);
	b.set_output(2.0);

//

	Neural::Link l(a,b);
	b.AddInputLink(l);
	std::cout << b.output() << std::endl;
	b.CalculateOutput();
	std::cout << b.output() << std::endl;
//	std::cout << a.output() << ", " << b.output() << std::endl;
	return 0;
}
