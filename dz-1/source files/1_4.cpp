#include "header.h"

void list_add(List& st, int val) {
    ListNode* node = new ListNode;
    if (st.num_nodes == 0) {
        st.beg = node;
    }
    node->value = val;
    node->next = st.beg;
    node->prev = st.beg->prev;
    st.beg->prev = node;
   
    st.num_nodes++;
}

int list_pop_node(List& st, ListNode* node) {
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
}

void run1_4(std::string s, std::string sa) {
    List l;
    list_add(l, 1);
    list_add(l, 2);
    list_add(l, 3);
    print_list(l);
    std::cout<<list_pop(l, 1);
    std::cout << list_pop(l, 0);
    std::cout << list_pop(l, 0);
}