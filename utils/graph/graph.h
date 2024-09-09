#include <random>
#include <string>

#ifndef GRAPH_H
#define GRAPH_H

typedef unsigned int node;     // graph node
typedef unsigned int uint;

/**
 * Base structure (array 1D format) of a graph
 */
struct GraphStruct {
	uint nodeSize{0};             // num of graph nodes
	uint edgeSize{0};             // num of graph edges
	uint* cumDegs{nullptr};       // cumsum of node degrees
	node* neighs{nullptr};           // list of neighbors for all nodes (edges)
	float* weights{nullptr};

	~GraphStruct() {delete[] neighs; delete[] cumDegs;}

	// check whether node j is a neighbor of node i
	int isNeighbor(node i, node j) {
		for (unsigned k = 0; k < deg(i); k++) {
			if (neighs[cumDegs[i]+k] == j) {
				return k;				
			}
		}
	  	return -1;
	}

	// Getter for the weight associated to an edge
	float getWeight(node i, node j) {
		int position = isNeighbor(i, j);

		if(position == -1) {
			return -1;
		}
		else {
			return weights[cumDegs[i] + position];
		}
	}

	// return the degree of node i
	uint deg(node i) {
		return(cumDegs[i+1]-cumDegs[i]);
	}

	// Function that saves to file the contents of the current graph
	void graphWriter(std::string path) {
		FILE *fptr;

		// Open the file in writing mode
		fptr = fopen(path, "w");
		if(!fptr) {
			printf("There was an error while opening the file\n");
		}

		// Write down the size of the graph
		fprintf(fptr, "%d\n", nodeSize);

		// Write the adjacency lists
		for(node i = 0; i < nodeSize; ++i) {
			for (node j = 0; j < deg(i); j++) {
				fprintf(fptr, "%d,%f", neighs[cumDegs[i] + j], weights[cumDegs[i] + j]);
			}
			fprintf(fptr, "\n");
		}

		// Close the file
		fclose(fptr);
	}

};

/**
 * It manages a graph for CPU & GPU
 */
class Graph {
	float density{0.0f};	        // Probability of an edge (Erdos graph)
	GraphStruct * str{nullptr};     // graph structure
	uint maxDeg{0};
	uint minDeg{0};
	float meanDeg{0.0f};
	bool connected{true};
	bool GPUEnabled{true};

public:
	Graph(uint nn, bool GPUEnb) : GPUEnabled{GPUEnb} {setup(nn);}
	void setup(uint);	                             // CPU/GPU mem setup
	void randGraph(float, bool, int, std::default_random_engine&);  // generate an Erdos random graph
	void print(bool);
	void print_d(GraphStruct *, bool);
	GraphStruct* getStruct() {return str;}
	void memsetGPU(uint, std::string);                 // use UVA memory on CPU/GPU
};

#endif
