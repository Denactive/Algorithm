#define BUILD_LISTGRAPH 0
#define BUILD_ROUTES 0
#define BUILD_OPTIMUM_ROUTE 1

#include "list_graph.h"
#include "dsu.h"
#include "8game.h"
#include "Shortcuts.h"
#include "optimim_route.h"

int main() {
	if (BUILD_LISTGRAPH)
		//run_1();
		test_1();
	if (BUILD_ROUTES)
		//run_2();
		test_2();
	if (BUILD_OPTIMUM_ROUTE)
		//test_weighted_matrix();
		//run_3();
		test_3();
	return 0;
}

