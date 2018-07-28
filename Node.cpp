#include "Node.h"

Node::Node(int num_edges, std::vector<std::string> & hostNames) {
	this->num = num_edges;
	for (unsigned i = 0; i < hostNames.size(); ++i) {
		hosts.push_back(hostNames[i]);
	}
}

void Node::addNeighbor(Node * neighbor) {
	neighbors.insert(neighbor);
}