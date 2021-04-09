#include "header.h"

void print(int* a, int n);

template <typename T>
int partion(int* a, int len, Comparator<T> cmp) {
	// [p...ji]
	int p = rand() % len;
	std::swap(a[p], a[0]);
	std::cout << "pivot : " << p << "\n";
	int i = len - 1;
	int j = len - 1;  // j < i
	//  Х »тератор (индекс) i указывает на начало группы элементов, меньших либо равных опорному.
	//	Х »тератор j меньше i, итератор j указывает на последений нерассмотренный элемент.
	while (j != 0) {
		if (cmp(a[0], a[j])) {
			std::swap(a[i], a[j]);
			i--;
		}
		j--;
	}
	std::swap(a[0], a[i]);
	print(a, len);
	return i;
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

	int cnt = -1;
	Comparator<int> std_cmp;
	int r_border = n;
	int l_border = 0;

	std::cout << "before partition" << std::endl;
	print(a, n);

	while (cnt != k) {
		std::cout << "l: " << l_border << " len: " << r_border - l_border << std::endl;
		cnt = l_border + partion(a + l_border, r_border - l_border, std_cmp);
		if (k < cnt) {
			r_border = cnt;
		}
		if (k > cnt) {
			l_border = cnt;
		}
	} 

	std::cout << "after partition" << std::endl;
	print(a, n);

	std::cout << a[cnt] << std::endl;
	if (!sa.empty()) std::cout << "correct is: " << sa << std::endl;

	delete[] a;
}

void test6_4() {
	int test_amount = 4;
	std::string cases[] = {
		"8 2\n2 8 7 1 3 5 6 4\n",
		"10 4\n1 2 3 4 5 6 7 8 9 10\n",
		"10 0\n3 6 5 7 2 9 8 10 4 1\n",
		"10 9\n0 0 0 0 0 0 0 0 0 1\n",
		"8 2\n2 8 7 1 3 5 6 4\n",

	};
	std::string answers[] = {
		"3\n",
		"5\n",
		"1\n",
		"1\n",
		"unknown\n",
	};
	for (int i = 0; i < test_amount; i++)
		run6_4(cases[i], answers[i]);
}

void print(int* a, int n) {
	for (int i = 0; i < n; ++i)
		std::cout << a[i] << ' ';
	std::cout << std::endl;
}