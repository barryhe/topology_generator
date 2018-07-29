#include "Node.h"
#include "Manager.h"
#include "Domain.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <iomanip>  
#include <iostream>
#include <unordered_set>

#define charLength 4

Manager::Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders) {
	// initialize domains
	std::unordered_set<std::string> idSet;
	srand(time(NULL));

	// generating id's for domains
	for (int i = 0; i < num_domains; ++i) {
		std::vector<std::string> nodeNames; 
		std::vector<std::string> hostNames; 

		// generate id's for nodes
		for (int j = 0; j < num_nodes; ++j) {
			const std::string randId = getRandomId(); 
			if (idSet.find(randId) != idSet.end()) {
				idSet.insert(randId); 
				nodeNames.push_back("SWITCH_" + randId); 
			}
		} 

		// generate id's for hosts
		for (int j = 0; j < num_hosts; ++j) {
			const std::string randId = getRandomId(); 
			if (idSet.find(randId) != idSet.end()) {
				idSet.insert(randId); 
				hostNames.push_back("HOST_" + randId); 
			}
		}

		Domain * domain = new Domain(num_domains, num_hosts, num_nodes, num_edges, num_borders,
									nodeNames, hostNames, this);
		domains.push_back(domain); 
	}
}

Manager::~Manager() {
	for (Domain * d : domains) {
		delete d; 
	}
}

std::string Manager::getRandomId() {
	int id = rand() % 1000000;
	std::stringstream ss;
	for (int i = 0; i < charLength; ++i) {
		ss << (char)(rand() % 26 + 'a'); 
	}
	ss << '_';
	ss << std::setw(6) << std::setfill('0') << id;

	return ss.str();
}