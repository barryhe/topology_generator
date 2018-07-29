#include "Node.h"
#include "Manager.h"
#include "Domain.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <iomanip>  
#include <iostream>
#include <unordered_set>
#include <queue>

#define charLength 4

Manager::Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, bool pLog) {
	mDomains = num_domains;
	mHosts	 = num_hosts;
	mNodes	 = num_nodes;
	mEdges	 = num_edges;
	mBorders = num_borders;

	doLog = pLog;
	log.open("log.txt");

	// initialize domains
	srand(time(NULL));

	// generating id's for domains
	for (int i = 0; i < num_domains; ++i) {
		const std::string domainId = "DOMAIN_" + getRandomId(); 
		std::vector<std::string> nodeNames; 
		std::vector<std::string> hostNames; 

		// generate id's for nodes
		for (int j = 0; j < num_nodes; ++j) {
			const std::string randId = "SWITCH_" + getRandomId(); 
			if (idSet.find(randId) == idSet.end()) {
				idSet.insert(randId); 
				nodeNames.push_back(randId); 
			}
		} 

		// generate id's for hosts
		for (int k = 0; k < num_nodes - num_borders; ++k) {
			for (int j = 0; j < num_hosts; ++j) {
				const std::string randId = "HOST_" + getRandomId(); 
				if (idSet.find(randId) == idSet.end()) {
					idSet.insert(randId); 
					hostNames.push_back(randId); 
				}
			}
		}
		Domain * domain = new Domain(domainId, num_domains, num_hosts, num_nodes, num_edges, num_borders,
									nodeNames, hostNames, this);
		domains.push_back(domain); 
	}
}

Manager::~Manager() {
	for (Domain * d : domains) {
		delete d; 
	}
	log.close();

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

bool Manager::runTopology() {
	// connect border nodes randomly first
	for (unsigned i = 0; i < domains.size(); ++i) {
		unsigned d = rand() % domains.size(); 
		while (d == i) {
			d = rand() % domains.size(); 
		}

		// get a random border node
		std::vector<Node *> borders_from_other_domains;
		for (unsigned j = 0; j < domains.size(); ++j) {
			if (j != i) {
				for (unsigned k = 0; k < domains[j]->getBorderNodes().size(); ++k) {
					int pAvailability = domains[j]->getBorderNodes()[k]->getBorderNeighborCounts();
					if (pAvailability < mEdges - 1) {
						borders_from_other_domains.push_back(domains[j]->getBorderNodes()[k]);
					}
				}
			}
		}
		for (unsigned j = 0; j < domains[i]->getBorderNodes().size(); ++j) {
			int pAvailability = domains[i]->getBorderNodes()[j]->getBorderNeighborCounts();
			// check my availability
			if (pAvailability >= mEdges - 1) {
				continue; 
			} 
			int rounds = (rand() % (mEdges - 1));

			while (rounds == 0) rounds = (rand() % (mEdges - 1));
			rounds -= pAvailability;

			for (int k = 0; k < rounds; ++k) {
				int curr = rand() % borders_from_other_domains.size();
				domains[i]->getBorderNodes()[j]->addNeighbor(borders_from_other_domains[curr]);
				borders_from_other_domains[curr]->addNeighbor(domains[i]->getBorderNodes()[j]);

				if (borders_from_other_domains[curr]->getBorderNeighborCounts() >= mEdges - 1) {
					borders_from_other_domains.erase(borders_from_other_domains.begin() + curr);
				}
			}
		}
	}

	/*
	if (doLog) {
		log << "--Check border nodes neighbors: " << std::endl;
		for (unsigned i = 0; i < domains.size(); ++i) {
			log << domains[i]->getId() << std::endl;
			for (unsigned j = 0; j < domains[i]->getNodes().size(); ++j) {
				log << "\t" << domains[i]->getNodes()[j]->getId() 
					<< " " << domains[i]->getNodes()[j]->getNeighbors().size();

				if (domains[i]->getNodes()[j]->isBorder()) {
					log << " Border " << std::endl;
				} else {
					log << " Non-border " << std::endl;
				}

				for (unsigned k = 0; k < domains[i]->getNodes()[j]->getNeighbors().size(); ++k) {
					log << "\t\t" << domains[i]->getNodes()[j]->getNeighbors()[k]->getId() << std::endl;
				}
			}
		}
		log.flush();

		log << std::endl << std::endl;
	}
	*/

	// connect nodes within domains next
	for (unsigned i = 0; i < domains.size(); ++i) {
		domains[i]->runRegularGraph(); 
	}

	if (doLog) {
		log << "--Check nodes neighbors: " << std::endl;
		for (unsigned i = 0; i < domains.size(); ++i) {
			log << domains[i]->getId() << std::endl;
			for (unsigned j = 0; j < domains[i]->getNodes().size(); ++j) {
				log << "\t" << domains[i]->getNodes()[j]->getId() 
					<< " " << domains[i]->getNodes()[j]->getNeighbors().size();

				if (domains[i]->getNodes()[j]->isBorder()) {
					log << " Border " << std::endl;
				} else {
					log << " Non-border " << std::endl;
				}

				for (unsigned k = 0; k < domains[i]->getNodes()[j]->getNeighbors().size(); ++k) {
					log << "\t\t" << domains[i]->getNodes()[j]->getNeighbors()[k]->getId() << std::endl;
				}
			}
		}
		log.flush();

		log << std::endl << std::endl;
	}

	// check connectivity & other criterion
	// and also output it to the result file
	// bfs traversing the whole network
	int count = 0; 
	std::unordered_set<Node *> visited;
	std::queue<Node *> queue;
	std::ofstream inet("inet_edges.txt");

	queue.push(domains[0]->getNodes()[0]);
	visited.insert(domains[0]->getNodes()[0]); 

	while (!queue.empty()) {
		Node * curr = queue.front();
		queue.pop();
		count++; 
		idSet.erase(curr->getId());

		if (!curr->isBorder()) {
			// if it's a non-border node, we output its edges to hosts as well
			for (unsigned i = 0; i < curr->getHosts().size(); ++i) {
				inet << curr->getId() << " " << curr->getHosts()[i] << std::endl;
				inet << curr->getHosts()[i] << " " << curr->getId() << std::endl;
			}
		}

		for (unsigned i = 0; i < curr->getNeighbors().size(); ++i) {
			Node * n = curr->getNeighbors()[i]; 
			if (visited.find(n) == visited.end()) {
				visited.insert(n);
				queue.push(n); 
			} 
			inet << curr->getId() << " " << n->getId() << std::endl;
		}
	}

	inet.flush();
	inet.close();

	if (count != mNodes * mDomains 
		|| idSet.size() - mHosts * mDomains * (mNodes - mBorders) != 0) {
		return false;
	}

	return true;
}