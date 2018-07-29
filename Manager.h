#include <vector>
#include <fstream>

class Manager {
public:
	Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, bool);
	~Manager();
	std::ofstream log;


	bool runTopology();
private:
	std::vector<class Domain *> domains;
	std::string getRandomId(); 
	int mDomains;
	int mHosts;
	int mNodes;
	int mEdges;
	int mBorders;

	bool doLog;
};