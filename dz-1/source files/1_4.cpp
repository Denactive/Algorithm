#include "header.h"

void list_add(List& st, int val) {
    ListNode* node = new ListNode;
    node->value = val;
    if (st.num_nodes == 0) {
        st.beg = node;
        node->next = node;
        node->prev = node;
    }
    else {
        node->next = st.beg;
        node->prev = st.beg->prev;
        st.beg->prev->next = node;
        st.beg->prev = node;
    }
    st.num_nodes++;
}

int list_pop_node(List& st, ListNode* node) {
    if (node == st.beg)
        st.beg = st.beg->next;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    st.num_nodes--;
    int res = node->value;
    delete node;
    return res;
}

int list_pop(List& st, int i) {
    ListNode* node = st.beg;
    for (int j = 0; j < i - 1; j++) {
        node = node->next;
    }
    if (node == st.beg)
        st.beg = st.beg->next;
    int res = list_pop_node(st, node);
    return res;
}


void print_list(List& l) {
    ListNode* i = l.beg;
    do {
        std::cout << i->value << ' ';
        i = i->next;
    } while (i != l.beg);
    std::cout << std::endl;
}

void run1_4(std::string s, std::string sa) {
    std::stringstream ss;
    ss << s;

    int n = 0;
    int k = 0;
    if (s.empty())
        std::cin >> n >> k;
    else
        ss >> n >> k;

    List l;
    for (int j = 0; j < n; j++)
        list_add(l, j + 1);
    std::cout << "what is in list: ";
    print_list(l);

    for (auto i = l.beg; l.num_nodes != 1;) {
        //ListNode* next_iter_step = i->next->next->next;
        for (int j = 0; j < k; j++)
            i = i->next;
        std::cout << list_pop_node(l, i->prev);
    }
    std::cout << "\ncorrect is: " << sa << std::endl;
}

void test1_4() {
    int test_amount = 1;
    std::string cases[] = {
        "10 3\n",

    };
    std::string answers[] = {
        "3 6 9 2 7 1 8 5 10\n",

    };
    for (int i = 0; i < test_amount; i++)
        run1_4(cases[i], answers[i]);
}