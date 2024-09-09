#include "graph.h"
#include <random>

int main() {
	// Generation of a random graph
	std::random_device rd;
	std::default_random_engine eng(rd());
	uint size = 10;
	float prob = .3;
	bool GPUEnabled = 0;
	Graph graph(size, GPUEnabled);
	graph.randGraph(prob, true, 5, eng);
	graph.print(true);

    return 0;
}
