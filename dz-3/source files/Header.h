#pragma once

#define BUILD_LISTGRAPH 1
#define BUILD_ROUTES 0
#define BUILD_OPTIMUM_ROUTE 0

void run_1();
void run_2();
void run_3();

int main() {
	if (BUILD_LISTGRAPH)
		run_1();
	if (BUILD_ROUTES)
		run_2();
	if (BUILD_OPTIMUM_ROUTE)
		run_3();
	return 0;
}

