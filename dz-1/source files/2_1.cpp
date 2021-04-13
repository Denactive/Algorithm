#include "header.h"

int BinarySearch(const int* a, int len, int el) {
    std::cout << "bin search "<< el <<" in array: ";
    print(a, len);
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
    int* b = new int[m];

    if (s.empty())
        for (int i = 0; i < n; i++)
            std::cin >> a[i];
    else
        for (int i = 0; i < n; i++)
            ss >> a[i];

    int prev_res = -1;
    for (int i = 0; i < m; i++) {
        if (s.empty()) std::cin >> b[i]; else ss >> b[i];

        /*
        // Реализация на бинарном поиске
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
        // В этом способе надо выводить std::cout << prev_res;
        */
        int k = 1;
        // длина экспоненциального массива 2(2к) - 1 не превышает длину массива
        // и правый элемент текущего экспоненциального массива (с индексом 2к-2) меньше требуемого
        while (2 * k - 1 < n && a[2*k - 2] < b[i])
            k *= 2;

        // если не смогли увеличить, то искать в текущем экспоненциальном массиве до конца
        // число элементов длина экспоненциального массива k минус разность длин экспоненциального
        // и данного массивов: k - (2k-1 - n)
        if (2 * k - 1 >= n)
            prev_res = BinarySearch(a + k - 1, n - k + 1, b[i]);
        else
        // иначе искать от левого элемента увеличенного экспоненциального массива (k - 1)
        // до его правого элемента (2k-2), т.е. на массиве длиной k
            prev_res = BinarySearch(a + k - 1, k, b[i]);

        if (prev_res < 0)
            std::cout << n;
        else
            std::cout << k - 1 + prev_res;
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