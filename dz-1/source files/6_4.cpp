#include "header.h"

// todo: my cmp
int partion(int* a, int len) {
	// [p...ji]
	int p = rand() % len;
	std::swap(a[p], a[0]);
	std::cout << "pivot : " << p << "\n";
	int i = len - 1;
	int j = len - 1;  // j < i
	//  Х »тератор (индекс) i указывает на начало группы элементов, меньших либо равных опорному.
	//	Х »тератор j меньше i, итератор j указывает на последений нерассмотренный элемент.
	while (j != -1) {
		if (a[j] > a[0]) {
			std::swap(a[i], a[j]);
			i--;
		}
		j--;
	}
	//std::swap(a[0], a[i + 1]);
	return i + 1;
}

void run6_4(std::string s, std::string sa) {
	std::stringstream ss;
	ss << s;

	int n = 0;
	int k = 0;
	if (s.empty())
		std::cin >> n >> k;
	else
		ss >> n >> k;

	int* a = new int[n];

	if (s.empty())
		for (int i = 0; i < n; i++)
			std::cin >> a[i];
	else
		for (int i = 0; i < n; i++)
			ss >> a[i];

	int cnt = 0;
	Comparator<int> std_cmp;
	
	cnt = partion(a, n);

	for (int i = 0; i < n; ++i)
		std::cout << a[i] << ' ';
	std::cout << std::endl;

	std::cout << cnt << std::endl;
	if (!sa.empty()) std::cout << "correct is: " << sa << std::endl;

	delete[] a;
}

void test6_4() {
	int test_amount = 5;
	std::string cases[] = {
		"8 2\n2 8 7 1 3 5 6 4\n",
		"8 2\n2 8 7 1 3 5 6 4\n",
		"8 2\n2 8 7 1 3 5 6 4\n",
		"8 2\n2 8 7 1 3 5 6 4\n",
		"8 2\n2 8 7 1 3 5 6 4\n",

	};
	std::string answers[] = {
		"unknown\n",
		"unknown\n",
		"unknown\n",
		"unknown\n",
		"unknown\n",
	};
	for (int i = 0; i < test_amount; i++)
		run6_4(cases[i], answers[i]);
}