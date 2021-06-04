#include "Header.h"

template <typename T>
struct Node {
	Node() :left(nullptr), right(nullptr) {};
	Node(T value, Node* left = nullptr, Node* right = nullptr)
		: left(left)
		, right(right)
		, value(value)
	{
	}

	Node* left;
	Node* right;
	T value;
};

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
public:
	BinaryTree(Node<T>* base = nullptr)
		: root(base)
	{
	}

	void add(T value) {
		if (!root) {
			root = new Node<T>(value);
			return;
		}

		Node<T>* cur = root;
		Node<T>* prev = root;
		bool is_left = true;
		while (true) {
			if (!cur) {
				cur = new Node<T>(value);
				if (is_left)
					prev->left = cur;
				else
					prev->right = cur;
				return;
			}
			if (cmp(value, cur->value)) {
				prev = cur;
				cur = cur->left;
				is_left = true;
			}
			else {
				prev = cur;
				cur = cur->right;
				is_left = false;
			}
		}
	}

	int height(Node<T>* node = NULL) {
		if (!node)
			node = root;
		if (!node)
			return 0;
		if (!node->left && !node->right)
			return 1;
		if (!node->left)
			return height(node->right) + 1;
		if (!node->right)
			return height(node->left) + 1;

		return std::max(height(node->left), height(node->right)) + 1;
	}

	void print_in_order() {
		std::stack<Node<T>*> iterations;
		std::vector<Node<T>*> passed;
		Node<T>* cur = root;

		while (!iterations.empty() || cur) {

			// Идем налево, пока не останется левого узла
			while (cur) {
				iterations.push(cur);
				cur = cur->left;
			}

			// Доступ к узлу
			if (!iterations.empty()) {
				passed.push_back(iterations.top());
				iterations.pop();

				// Получаем новый узел, который подойдет к концу.
				cur = passed.back()->right;
			}
		}
		
		// print
		for (int i = 0; i < passed.size(); ++i) {
			std::cout << passed[i]->value;
			if (i < passed.size() - 1)
				std::cout << " ";
		}
	}

private:
	Node<T>* root;
	Comparator cmp;
};

void run2_1() {
	BinaryTree<int> tree;

	int N = 0;
	int key = 0;
	int prior = 0;

	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		std::cin >> key;
		tree.add(key);
	}

	tree.print_in_order();
}