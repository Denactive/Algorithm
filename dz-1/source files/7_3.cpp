#include "Header.h"
#include <cmath>

class BitComparator {
public:
	bool operator()(const long long& l, int digit)
	{
		if ((l >> digit) % 2 == 1)
			return true;
		else
			return false;
	}
};

template <typename T, typename Comparator>
int partition(T* a, int len, int digit) {
	// [p...ji]
	Comparator cmp;
	int i = len - 1;
	int j = len - 1;  // j < i
	//  Х »тератор (индекс) i указывает на начало группы элементов, меньших либо равных опорному.
	//	Х »тератор j меньше i, итератор j указывает на последений нерассмотренный элемент.
	while (j > -1) {
		if (cmp(a[j], digit)) {
			std::swap(a[i], a[j]);
			i--;
		}
		j--;
	}
	return i + 1;
}

void MSD(long long* a, int n, int digit) {
	if (digit < 0) return;
	int border = partition<long long, BitComparator>(a, n, digit);
	if (border > 1) MSD(a, border, digit - 1);
	if (border < n - 1) MSD(&a[border], n - border, digit - 1);
}

void run7_3(std::string s, std::string sa) {
	std::stringstream ss;
	ss << s;
	long long n;
	//std::cin >> n;
	ss >> n;
	long long* a = new long long[n];
	long long max = 0;
	for (int i = 0; i < n; ++i) {
		//std::cin >> arr[i];
		ss >> a[i];
		if (a[i] > max)
			max = a[i];
	}

	int num_digits = 1;
	if (max != 0)
		num_digits = log(max) / log(2);

	MSD(a, n, num_digits);
	std::cout << "result: ";
	for (int i = 0; i < n; ++i) {
		std::cout << a[i];
		if (i != n - 1)
			std::cout << " ";
	}
	if (!sa.empty()) std::cout << "\ncorrect is: " << sa << std::endl;
	delete[] a;
}

void test7_3() {
    int test_amount = 3;
    std::string cases[] = {
        "3\n4 1000000 7\n",
		"10\n 1 0 16 15 89 89 10000 0 1 10000\n",
		"10\n0 1231214 4 435234 0 0 1 1 10000000000000 1\n",
    };
    std::string answers[] = {
        "4 7 1000000\n",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
    };
    for (int i = 0; i < test_amount; i++) {
        std::cout << "\nTEST " << i + 1 << " --------------------------" << std::endl;
        run7_3(cases[i], answers[i]);
    }
}