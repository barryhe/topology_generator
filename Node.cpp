#include "Node.h"
#include "Domain.h"

Node::Node(int num_edges, std::vector<std::string> & hostNames, Domain * pDomain) {
	this->num = num_edges;
	for (unsigned i = 0; i < hostNames.size(); ++i) {
		hosts.push_back(hostNames[i]);
	}

	mDomain = pDomain;
}

void Node::addNeighbor(Node * neighbor) {
	neighbors.insert(neighbor);
}