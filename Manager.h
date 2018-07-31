#include <vector>
#include <fstream>
#include <unordered_set>

class Manager {
public:
	Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, bool);
	~Manager();
	std::ofstream log;


	bool runTopology();
private:
	std::unordered_set<std::string> idSet; // includes the id's of switches (border/non-borders) and hosts
	std::vector<class Domain *> domains;
	std::string getRandomId(); 
	int mDomains;
	int mHosts;
	int mNodes;
	int mEdges;
	int mBorders;

	bool doLog;
	int nextAvailablePort;

	int useNextPort();
};