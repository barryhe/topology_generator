#include "Domain.h"
#include "Node.h"
#include "Manager.h"
#include <iostream>

Domain::Domain(std::string did, int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, 
				std::vector<std::string> & nodeNames,
				std::vector<std::string> & hostNames, 
				Manager *pManager) {

	this->id = did;

	// initialization of non border nodes
	// num_hosts - numborders = num_servers
	for (int i = 0; i < num_nodes - num_borders; ++i) {
		int upper = (i + 1) * (num_hosts); 

		std::vector<std::string> hosts; 
		for (int j = i * num_hosts; j < upper; ++j) {
			hosts.push_back(hostNames[j]); 
		}

		Node * node = new Node(num_edges, nodeNames[i], hosts, this);

		nodes.push_back(node); 
		non_borders.push_back(node);
	}

	for (int i = num_nodes - num_borders; i < num_nodes; ++i) {
		std::vector<std::string> hosts;
		Node * node = new Node(num_edges, nodeNames[i], hosts, this);

		nodes.push_back(node); 
		borders.push_back(node);
	}

	mManager = pManager;
}

Domain::~Domain() {
	for (Node * n : nodes) {
		delete n;
	}
}

void Domain::runRegularGraph() {

}

