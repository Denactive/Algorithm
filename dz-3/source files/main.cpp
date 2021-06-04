#define BUILD_LISTGRAPH 1
#define BUILD_ROUTES 0
#define BUILD_OPTIMUM_ROUTE 0

#include "list_graph.h"
#include "dsu.h"
#include "8game.h"
#include "Shortcuts.h"

int main() {
	if (BUILD_LISTGRAPH)
		//run_1();
		test_1();
	if (BUILD_ROUTES)
		//run_2();
		test_2();
	if (BUILD_OPTIMUM_ROUTE)
		run_3();
	return 0;
}

