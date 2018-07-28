#include "Node.h"

Node::Node(int num_edges) {
	this->num = num_edges;
}

void Node::addNeighbor(Node * neighbor) {
	neighbors.insert(neighbor);
}