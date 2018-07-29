#include <iostream> 
#include <string>
#include <sstream>
#include "Manager.h"

int main(int argc, char** argv) {

	int num_domains = 10; 
	int num_nodes = 20; 
	int num_hosts = 5; 
	int num_edges = 5; 
	int num_borders = 5; 
	bool log = false; 

	for (int i = 1; i < argc; ++i) {
		std::string curr (argv[i]); 
		std::stringstream ss; 
		if (curr == "--help") {
			std::cout << "Usage: " << std::endl;
			std::cout << "./topo_generator  " 
						<< std::endl << "\t-d=[# of domains] "
						<< std::endl << "\t-n=[# of nodes in each domain] "
						<< std::endl << "\t-h=[# of hosts per node] "
						<< std::endl << "\t-e=[# of edges] "
						<< std::endl << "\t-b=[# of border nodes]" << std::endl;
			return 0; 
		} else if (curr.substr(0, 3) == "-d=") {
			ss << curr.substr(3); 
			ss >> num_domains;
		} else if (curr.substr(0, 3) == "-n=") {
			ss << curr.substr(3); 
			ss >> num_nodes;
		} else if (curr.substr(0, 3) == "-e=") {
			ss << curr.substr(3); 
			ss >> num_edges;
		} else if (curr.substr(0, 3) == "-b=") {
			ss << curr.substr(3); 
			ss >> num_borders;
		} else if (curr.substr(0, 3) == "-h=") {
			ss << curr.substr(3);
			ss >> num_hosts; 
		} else if (curr.substr(0, 2) == "-l") {
			log = true;
		} else {
			std::cout << "Error: invalid option detected. Type './topo_generator --help' for more information" << std::endl;
			return 0;
		}
	}
	if (num_nodes < num_borders) {
		std::cout << "Error: num of border nodes must be smaller or equal to num of nodes within a domain. Type './topo_generator --help' for more information" << std::endl;
		return 0;
	}
	if (num_domains < 1 || num_nodes < 1 || num_edges < 1) {
		std::cout << "Error: invalid input number(s). Type './topo_generator --help' for more information" << std::endl;
		return 0;
	}

	bool success = false;
	while (!success) {
		Manager * networkManager = new Manager(num_domains, num_hosts, num_nodes, num_edges, num_borders, log); 

		success = networkManager->runTopology(); 

		if (!success) {
			std::cout << "Disconnected components exist in the topology. Generating again..." << std::endl;
		} 
		delete networkManager;	
	}

	return 0;
}