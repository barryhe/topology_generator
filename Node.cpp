#include "Node.h"
#include "Domain.h"
#include <iostream>

Node::Node(int num_edges, std::string rid, std::vector<std::string> & hostNames, Domain * pDomain) {
	this->num = num_edges;
	for (unsigned i = 0; i < hostNames.size(); ++i) {
		hosts.push_back(hostNames[i]);
	}
	this->id = rid;

	mDomain = pDomain;
}

void Node::addNeighbor(Node * neighbor) {
	neighbors.insert(neighbor);
}