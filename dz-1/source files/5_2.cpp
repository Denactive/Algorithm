#include "Header.h"
#include <string>

template <typename T, typename Comparator>
int merge_sort(T* arr, size_t len) {
    if (!arr) {
        std::cout << "Error | Unable to sort an empty arr\n";
        return 0;
    }
    if (len <= 1)
        return 0;

    size_t lsize = len / 2;
    size_t rsize = len - lsize;

    if (merge_sort<T, Comparator>(arr, lsize))
        return -1;
    if (merge_sort<T, Comparator>(arr + lsize, rsize))
        return -1;

    T* tmp = new T [len];
    if (!tmp)
        return -1;

    if (merge<T, Comparator>(arr, lsize, arr + lsize, rsize, tmp))
        return -1;

    if (!memcpy(arr, tmp, len * sizeof(T)))
        return -1;
    
    delete [] tmp;
    return 0;
}

template <typename T, typename Comparator>
int merge(T* l, size_t lsize, T* r, size_t rsize, T* res) {
    size_t lpos = 0;
    size_t rpos = 0;
    Comparator cmp;
    while (lpos < lsize && rpos < rsize) {
        if (cmp(l[lpos], r[rpos])) {
            res[lpos + rpos] = l[lpos];
            lpos++;
        }
        else {
            res[lpos + rpos] = r[rpos];
            rpos++;
        }
    }
    if (lpos == lsize) {
        if (!memcpy(res + lpos + rpos, r + rpos, (rsize - rpos) * sizeof(T)))
            return -1;
    }
    else {
        if (!memcpy(res + lpos + rpos, l + lpos, (lsize - lpos) * sizeof(T)))
            return -1;
    }
    return 0;
}

void run5_2(std::string s, std::string sa) {
	std::stringstream ss;
	ss << s;

	int n = 0;
	if (s.empty())
		std::cin >> n;
	else
		ss >> n;

    if (n == 0) {
        std::cout << 0;
        return;
    }
	
    date* a = new date [n]; // 18-ти летия 
    date* b = new date [n]; // смерти и 80-ти летия
    int size = 0;

	// добавление в вектор по восемнадцатилетию
	DateComparator date_cmp;
	for (int i = 0; i < n; i++) {
		date birth = { 0 };
		date death = { 0 };
		if (s.empty()) std::cin >> birth.d >> birth.m >> birth.y >> death.d >> death.m >> death.y;
		else ss >> birth.d >> birth.m >> birth.y >> death.d >> death.m >> death.y;
		date tmp = birth;
		tmp.y += 18;
		if (date_cmp(tmp, death)) {
			std::cout << "adding: " << tmp.d << ' ' << tmp.m << ' ' << tmp.y << " - "<< death.d << ' ' << death.m << ' ' << death.y << " to vector" << std::endl;
            a[size] = tmp;
            tmp.y += 62;
            if (date_cmp(death, tmp))
                b[size] = death;
            else
                b[size] = tmp;
            size++;
		}
	}
    
    merge_sort<date, DateComparator>(a, size);
    merge_sort<date, DateComparator>(b, size);

    int current_alive = 0;
    int max_alive = 0;

    int i[2] = { 0, 0 };
    while (i[0] < size && i[1] < size) {
        std::cout << current_alive << ' ' << max_alive << '\n';
        if (date_cmp(a[i[0]], b[i[1]])) {
            std::cout << "+ " << a[i[0]].d << ' '<< a[i[0]].m << ' ' << a[i[0]].y << std::endl;
            current_alive++;
            i[0]++;
            if (current_alive > max_alive)
                max_alive = current_alive;
            continue;
        }
        if (a[i[0]].d == b[i[1]].d && a[i[0]].m == b[i[1]].m && a[i[0]].y == b[i[1]].y) {
            std::cout << "= " << a[i[0]].d << ' ' << a[i[0]].m << ' ' << a[i[0]].y << std::endl;
            i[0]++;
            i[1]++;
        }
        else {
            std::cout << "- " << b[i[1]].d << ' ' << b[i[1]].m << ' ' << b[i[1]].y << std::endl;
            current_alive--;
            i[1]++;
        }
        if (current_alive > max_alive)
            current_alive = max_alive;
    }
    std::cout << max_alive;
	std::cout << "\ncorrect is: " << sa << std::endl;
    delete[] a;
    delete[] b;
}

void test5_2() {
    int test_amount = 12;
    std::string cases[] = {
        "3 2 5 1980 13 11 2055\n1 1 1982 1 1 2030\n2 1 1920 2 1 2000\n",
        "12 2 5 1980 13 11 2055\n\
            1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n\
            1 2 1982 1 1 2030\n2 1 1982 1 1 2030\n3 1 1982 1 1 2030\n1 3 1982 1 1 2030\n1 1 1982 1 1 2030\n\
            2 1 1920 2 1 2000\n",
        "3 0 0 0   0 0 5\n0 0 10   31 12 18\n0 0 1920   0 0 1920\n",
        "3 0 0 0   0 0 5\n0 0 0   31 12 17\n0 0 1920   0 0 1920\n",
        "3 0 0 0   0 0 5\n0 0 10   0 0 50\n0 0 1920   0 0 2000\n",
        "2 0 0 0   0 0 20\n0 0 2   0 0 50\n",
        "2 0 0 0   0 0 20\n31 12 0   0 0 50\n",
        "4 0 0 0   0 0 20\n5 0 0   5 0 50\n 0 0 0   0 0 21\n 0 0 0   0 0 21\n",
        "3 0 0 0   0 0 30\n0 0 5   5 0 50\n 0 0 58   0 0 80\n",
        "3 0 0 0   0 0 30\n0 0 5   5 0 50\n 0 0 32   0 0 80\n",
        "3 0 0 0   0 0 50\n0 0 5   5 0 50\n 0 0 31   0 0 80\n",
        "3 0 0 0   0 0 21\n0 0 1   0 0 23\n 0 0 2   0 0 22\n",


    };
    std::string answers[] = {
        "3\n",
        "8\n",
        "0 - no add case\n",
        "0 - умер до 18-летия\n",
        "1 - 2 интервала не пересекаются\n",
        "1 - пограничный случай. 1 стало 18 лет, другой помер\n",
        "2 - пограничный случай. 1 стало 18 лет, другой помер на денб позже\n",
        "4 - интервалы пересекаются\n",
        "2 - 2 интервала пересекутся, третий - нет\n",
        "2 - \n",
        "3 - \n",
        "3 - \n",

    };
    for (int i = 0; i < test_amount; i++) {
        std::cout << "\nTEST "<< i+1 <<" --------------------------" << std::endl;

        run5_2(cases[i], answers[i]);
    }
}