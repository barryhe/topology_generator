#include "Domain.h"
#include "Node.h"
#include "Manager.h"
#include <iostream>

Domain::Domain(std::string did, int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, 
				std::vector<std::string> & nodeNames,
				std::vector<std::string> & hostNames, 
				Manager *pManager) {

	this->id = did;
	this->mEdges = num_edges;

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
	/* reference from: http://people.tamu.edu/~li3939108/Introduction.pdf */
	std::vector<std::vector<Node*> > sets;

	// r + 1 empty sets to store vertices with degrees i
	for (int i = 0; i < mEdges + 1; ++i) {
		std::vector<Node*> temp;
		sets.push_back(temp);
	}

	// assign vertices to sets according to their degrees
	for (unsigned i = 0; i < nodes.size(); ++i) {
		sets[nodes[i]->getNeighborCount()].push_back(nodes[i]);
	}

	while (sets[mEdges].size() < nodes.size()) {
		if (sets[mEdges].size() == nodes.size() - 1) {
			break; 
		}

		int randomSet = rand() % mEdges; // get a random set wit degree 0 to r
		while (sets[randomSet].size() == 0) randomSet = (randomSet + 1) % mEdges; // guarantee get a node

		int randomVertex = rand() % sets[randomSet].size(); 
		Node * v1 = sets[randomSet][randomVertex]; 
		sets[randomSet].erase(sets[randomSet].begin() + randomVertex); // pop this node


		int left = mEdges - v1->getNeighborCount();

		/* due to the problem of the testing environment, we can tolerate
		 * some vertices with <= target num of edges. For most cases that 
		 * we need to compromise, there must be only one vertex left for 
		 * processing. 
		 */ 

		for (int i = 0; i < left; ++i) {
			if (sets[mEdges].size() == nodes.size() - 1) {
				break; 
			}
			randomSet = 0; 
			while (randomSet < mEdges) {
				if (sets[randomSet].size() > 0) {
					break; 
				}
				randomSet++;
			}

			randomVertex = rand() % sets[randomSet].size(); 
			Node * v2 = sets[randomSet][randomVertex];
			sets[randomSet].erase(sets[randomSet].begin() + randomVertex);

			v1->addNeighbor(v2);
			v2->addNeighbor(v1);

			sets[v2->getNeighborCount()].push_back(v2);
		}
		sets[mEdges].push_back(v1);
	}
}

