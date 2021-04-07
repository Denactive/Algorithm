#include "Header.h"

void test_heap() {
	std::cout << "heap test\n";
	Comparator<int> idi_nahuy;
	Heap<int> h(idi_nahuy);
	for (int i = 0; i < 15; i++)
		h.insert(i);
	h.print();

	std::cout << "peek top: " << h.peek_top() << std::endl;
	h.print();

	for (int i = 0; i < 15; i++) {
		std::cout << "extract top: " << h.extract_top() << std::endl;
		h.print();
	}
}