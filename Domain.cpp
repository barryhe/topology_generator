#include "Domain.h"
#include "Node.h"
#include "Manager.h"
Domain::Domain(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, 
				std::vector<std::string> & nodeNames,
				std::vector<std::string> & hostNames, 
				Manager *pManager) {

}

Domain::~Domain() {
	for (Node * n : nodes) {
		delete n;
	}
}

std::string Domain::generateRandomId() {
	std::string res = "";
	return res; 
}