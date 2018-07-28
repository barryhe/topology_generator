#include "Node.h"
#include "Manager.h"
#include "Domain.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <iomanip>  
#include <iostream>
#include <unordered_set>

Manager::Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders) {
	// initialize domains
	std::unordered_set<int> idSet;
	
}

Manager::~Manager() {
	for (Domain * d : domains) {
		delete d; 
	}
}

std::string Manager::getRandomId() {
	// srand(time(NULL));
	int id = rand() % 1000000;
	std::stringstream ss;
	ss << std::setw(6) << std::setfill('0') << id;

	return ss.str();
}