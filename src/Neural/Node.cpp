#include "Node.hpp"

namespace Neural {

unsigned Node::counter = 0;

Node::Node() : id_(counter++) {

}

double Node::XferFunction(double x) {
	return x;
}

double Node::XferFunctionD(double x) {
	return x;
}


}; // end_namespace
