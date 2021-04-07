#include "header.h"
/*
int BinarySearch(const int* a, int len, int el) {
    int beg = 0;
    int end = len;  // [..)
    while (beg < end) {
        int mid = (beg + end) / 2;
        if (a[mid] >= el)
            end = mid;
        else
            beg = mid + 1;
    }
    if (beg == len + 1)
        return -1;
    else
        return beg;
}*/

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

int run2_1() {
    std::cout << "Задача 2.1\n";

    int n = 0, m = 0;
    std::cin >> n >> m;
    int* a = new int[n];
    int* b = new int[n];

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    int prev_res = -1;
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
        if (prev_res < 0) {
            prev_res = BinarySearch(a, n, b[i]);
        }
        else {
            if (b[i] < b[i - 1]) {
                prev_res = BinarySearch(a, prev_res, b[i]);
            }
            else {
                int tmp = BinarySearch(a + prev_res, n - prev_res - 1, b[i]);
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
        if (i != m - 1)
            std::cout << ' ';
        else
            std::cout << std::endl;
    }

    delete[] a;
    delete[] b;
    return 0;
}