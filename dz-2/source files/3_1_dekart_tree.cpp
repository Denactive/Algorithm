#include "Header.h"

template <typename T>
struct PriorityTreeNode {
	PriorityTreeNode(T key = 0, int prior = 0, PriorityTreeNode<T>* left = nullptr, PriorityTreeNode<T>* right = nullptr) 
		: key(key)
		, prior(prior)
		, left(left)
		, right(right)
	{
	}
	
	T key;
	int prior;
	PriorityTreeNode<T>* left;
	PriorityTreeNode<T>* right;
};

template <typename T, typename Comparator = std::less<T>>
class PriorityTree {
public:
	PriorityTree(PriorityTreeNode<T>* node = nullptr)
		: root(node)
	{
	}

	void add(T key, int prior) {
		PriorityTreeNode<T>* node = new PriorityTreeNode<T>(key, prior);
		do_add(root, node);
	}
	
	void do_add(PriorityTreeNode<T>*& root, PriorityTreeNode<T>* node) {
		if (!root) {
			root = node;
		} else {
			if (node->prior <= root->prior) {
				if (cmp(node->key, root->key))
					do_add(root->left, node);
				else
					do_add(root->right, node);
			}
			else {
				split(root, node->key, node->left, node->right);
				root = node;
			}
		}
	}

	void do_delete(PriorityTreeNode<T>*& root, T key) {
		if (!root)
			return;

		if (key == root->key) {
			root = merge(root->left, root->right);
		} else {
			if (cmp(key, root->key))
				do_delete(root->left, key);
			else
				do_delete(root->right, key);
		}
	}

	int height(PriorityTreeNode<T>* node = NULL) {
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

private:
	
	PriorityTreeNode<T>* merge(PriorityTreeNode<T>* left, PriorityTreeNode<T>* right) {
		if (!left || !right)
			return !left ? right : left;
		if (left->prior > right->prior) {
			left->right = merge(left->right, right);
			return left;
		}
		right->left = merge(left, right->left);
		return right;
	}
	
	void split(PriorityTreeNode<T>* node, int key, PriorityTreeNode<T>*& left, PriorityTreeNode<T>*& right) {
		if (!node) {
			left = 0;
			right = 0;
		}
		else {
			if (cmp(key, node->key)) {
				split(node->left, key, left, node->left);
				right = node;
			}
			else {
				split(node->right, key, node->right, right);
				left = node;
			}
		}
	}

	PriorityTreeNode<T>* root;
	Comparator cmp;
};

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
		
		return std::max( height(node->left), height(node->right) ) + 1;
	}

private:
	Node<T>* root;
	Comparator cmp;
};

void run3_1() {
	PriorityTree<int> pr_tree;
	BinaryTree<int> tree;

	int N = 0;
	int key = 0;
	int prior = 0;
	
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		std::cin >> key;
		std::cin >> prior;
		pr_tree.add(key, prior);
		tree.add(key);
	}

	std::cout << abs(pr_tree.height() - tree.height());
}
