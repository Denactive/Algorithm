#include "Header.h"

void test_heap() {
	std::cout << "heap test\n";
	Comparator<int> std_cmp;
	Heap<int> h(std_cmp);
	for (int i = 0; i < 15; i++)
		h.insert(i);
	h.print();

	std::cout << "size: " << h.size() << std::endl;

	std::cout << "peek top: " << h.peek_top() << std::endl;
	h.print();

	for (int i = 0; i < 15; i++) {
		std::cout << "extract top: " << h.extract_top() << std::endl;
		h.print();
	}
	std::cout << "size: " << h.size() << std::endl;
}

void run4_3(std::string s, std::string sa) {
	std::stringstream ss;
	ss << s;

	int n = 0;
	if (s.empty())
		std::cin >> n;
	else
		ss >> n;

	size_t cnt = 0;
	Comparator<int> std_cmp;
	Heap<int> h(std_cmp);
	for (int i = 0; i < n; i++) {
		int arival = 0;
		int departure = 0;
		if (s.empty())
			std::cin >> arival >> departure;
		else
			ss >> arival >> departure;
		h.insert(departure);
		while (arival > h.peek_top())
			h.extract_top();
		if (cnt < h.size())
			cnt = h.size();
	}
	std::cout << cnt << std::endl;
	std::cout << "correct is: " << sa << std::endl;
}

void test4_3() {
	int test_amount = 6;
	std::string cases[] = {
		"1\n10 20\n",
		"2\n10 20\n20 25\n",
		"3\n10 20\n20 25\n21 30\n",
		"4\n10 20\n20 25\n21 30\n22 30\n",
		"5\n10 20\n20 30\n21 30\n22 30\n30 31\n",
		"5\n10 20\n20 25\n21 30\n22 30\n31 32\n",

	};
	std::string answers[] = {
		"1\n",
		"2\n",
		"2\n",
		"3\n",
		"4\n",
		"3\n",

	};
	for (int i = 0; i < test_amount; i++)
		run4_3(cases[i], answers[i]);
}