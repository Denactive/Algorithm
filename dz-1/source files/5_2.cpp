#include "Header.h"
#include <vector>
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
	
	//std::vector<std::pair<date, date>> a;
    //std::pair<date, date>* a = new std::pair<date, date>[n]; // 18-ти летия 
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
			//a[size] = std::pair<date, date>(tmp, death);
            a[size] = tmp;
            tmp.y += 62;
            if (date_cmp(death, tmp))
                b[size] = death;
            else
                b[size] = tmp;
            size++;
		}
	}
    /*
    std::cout << "\n--------------------------\nbefore sort: " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << a[i].first.d << ' ' << a[i].first.m << ' ' << a[i].first.y << " - ";
        std::cout << a[i].second.d << ' ' << a[i].second.m << ' ' << a[i].second.y << std::endl;
    }
    merge_sort<std::pair<date, date>, DatePairComparator>(a, size);
    std::cout << "after sort: " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << a[i].first.d << ' ' << a[i].first.m << ' ' << a[i].first.y << " - ";
        std::cout << a[i].second.d << ' ' << a[i].second.m << ' ' << a[i].second.y << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    */
    std::cout << "\n--------------------------\nbefore sort: " << std::endl;
    std::cout << "18:\n";
        for (int i = 0; i < size; ++i)
            std::cout << a[i].d << ' ' << a[i].m << ' ' << a[i].y << std::endl;
    std::cout << "80 / d:\n";
    for (int i = 0; i < size; ++i)
        std::cout << b[i].d << ' ' << b[i].m << ' ' << b[i].y << std::endl;
   
    merge_sort<date, DateComparator>(a, size);
    merge_sort<date, DateComparator>(b, size);
    std::cout << "after sort: " << std::endl;
    std::cout << "18:\n";
    for (int i = 0; i < size; ++i)
        std::cout << a[i].d << ' ' << a[i].m << ' ' << a[i].y << std::endl;
    std::cout << "80 / d:\n";
    for (int i = 0; i < size; ++i)
        std::cout << b[i].d << ' ' << b[i].m << ' ' << b[i].y << std::endl;
    std::cout << "--------------------------" << std::endl;

    int current_alive = 0;
    int max_alive = 0;

    int i[2] = { 0, 0 };
    while (i[0] < size && i[1] < size) {
        std::cout << current_alive << ' ' << max_alive << '\n';
        if (date_cmp(a[i[0]], b[i[1]])) {
            current_alive++;
            i[0]++;
            if (current_alive > max_alive)
                max_alive = current_alive;
            continue;
        }
        if (a[i[0]].d == b[i[1]].d && a[i[0]].m == b[i[1]].m && a[i[0]].y == b[i[1]].y) {
            i[0]++;
            i[1]++;
        }
        else {
            current_alive--;
            i[1]++;
        }
        if (current_alive > max_alive)
            current_alive = max_alive;
    }
    std::cout << max_alive;
	std::cout << "\ncorrect is: " << sa << std::endl;
    delete[] a;
}

void test5_2() {
	int test_amount = 2;
	std::string cases[] = {
		"3 2 5 1980 13 11 2055\n1 1 1982 1 1 2030\n2 1 1920 2 1 2000\n",
        "12 2 5 1980 13 11 2055\n\
            1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n1 1 1982 1 1 2030\n\
            1 2 1982 1 1 2030\n2 1 1982 1 1 2030\n3 1 1982 1 1 2030\n1 3 1982 1 1 2030\n1 1 1982 1 1 2030\n\
            2 1 1920 2 1 2000\n",

	};
	std::string answers[] = {
		"3\n",
        "7\n",

	};
	for (int i = 0; i < test_amount; i++)
		run5_2(cases[i], answers[i]);
}