#include "header.h"

int BinarySearch(const int* a, int len, int el) {
    int beg = 0;
    int end = len;
    while (beg < end) {
        int mid = (beg + end) / 2;
        if (el <= a[mid]) {
            end = mid;
        }
        else {
            if (mid < len && a[mid + 1] > el) {
                beg = mid + 1;
                break;
            }
            beg = mid + 1;
        }
    }
    if (beg == len + 1)
        return -1;
    else
        return beg;
}

int run2_1(std::string s, std::string sa) {
    std::stringstream ss;
    ss << s;

    int n = 0, m = 0;
    if (s.empty())
        std::cin >> n >> m;
    else
        ss >> n >> m;

    int* a = new int[n];
    int* b = new int[n];

    if (s.empty())
        for (int i = 0; i < n; i++)
            std::cin >> a[i];
    else
        for (int i = 0; i < n; i++)
            ss >> a[i];

    int prev_res = -1;
    for (int i = 0; i < m; i++) {
        if (s.empty()) std::cin >> b[i]; else ss >> b[i];

        if (prev_res < 0) {
            prev_res = BinarySearch(a, n, b[i]);
        }
        else {
            if (b[i] < b[i - 1]) {
                prev_res = BinarySearch(a, prev_res, b[i]);
            }
            else {
                int tmp = BinarySearch(a + prev_res, n - prev_res, b[i]);
                if (tmp < 0)
                    prev_res = -1;
                else
                    prev_res += tmp;
            }
        }
        if (prev_res < 0)
            std::cout << n;
        else
            std::cout << prev_res;
        if (i != m - 1) std::cout << ' '; else std::cout << '\n';
    }
    std::cout << "correct is: " << sa << std::endl;
    delete[] a;
    delete[] b;
    return 0;
}

void test2_1() {
    int test_amount = 5;
    std::string cases[] = {
        "2 1\n1 2\n2\n",
        "4 3\n2 4 5 7\n4 6 1\n",
        "6 3\n-200 0 123 123 123 123\n-201 123 124\n",
        "3 2\n-200 0 123\n123 124\n",
        "3 2\n-200 0 123\n123 125\n",

    };
    std::string answers[] = {
        "1\n",
        "1 3 0\n",
        "0 2 6\n",
        "2 3\n",
        "2 3\n",
    };
    for (int i = 0; i < test_amount; i++)
        run2_1(cases[i], answers[i]);
}