#include <iostream> 
#include <string>
#include <sstream>

int main(int argc, char** argv) {

	int num_domains = -1; 
	int num_nodes = -1; 
	int num_hosts = -1; 
	int num_edges = -1; 
	int num_border = -1; 

	for (int i = 0; i < argc; ++i) {
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
			ss >> num_border;
		} else if (curr.substr(0, 3) == "-h=") {
			ss << curr.substr(3);
			ss >> num_hosts; 
		} else {
			std::cout << "Error: invalid option detected. Type './topo_generator --help' for more information" std::endl;
		}
	}
	if (num_hosts == -1 || num_border == -1 || num_edges == -1 || num_nodes == -1 || num_domains == -1) {
		std::cout << "Error: invalid number detected. Type './topo_generator --help' for more information" std::endl;
	}

	

}