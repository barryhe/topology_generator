#include "Node.h"
#include "Domain.h"
#include <iostream>

Node::Node(int num_edges, std::string rid, std::vector<std::string> & hostNames, Domain * pDomain) {
	this->num = num_edges;
	for (unsigned i = 0; i < hostNames.size(); ++i) {
		hosts.push_back(hostNames[i]);
	}
	this->id = rid;
	this->border_nodes = 0;

	mDomain = pDomain;
}

void Node::addNeighbor(Node * neighbor) {
	if (neighbor->isBorder()) {
		this->border_nodes++;
	}
	neighbors.push_back(neighbor);
}