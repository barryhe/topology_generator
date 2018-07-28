#include "Node.h"
#include "Manager.h"
#include "Domain.h"

Manager::Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders) {

}

Manager::~Manager() {
	for (Domain * d : domains) {
		delete d; 
	}
}