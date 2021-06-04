#include "Header.h"

template <typename T>
struct AVLTreeNode {
	T key;
	int count;
	int height;
	std::shared_ptr<AVLTreeNode> left;
	std::shared_ptr<AVLTreeNode> right;

	AVLTreeNode(int new_key)
		: key(new_key)
		, left(NULL)
		, right(NULL)
		, height(1)
		, count(0)
	{
	}
};

template<typename T, typename Comparator = std::less<T>>
class AVLTree {
public:
	AVLTree(std::shared_ptr<AVLTreeNode<T>> root = NULL)
		: root(root)
	{
	}

	/*~AVLTree() {
		std::cout << "d-tor\n";
		auto v = in_order();
		for (int i = 0; i < v.size(); ++i)
			delete v[i];
	}*/

	std::vector<std::shared_ptr<AVLTreeNode<T>>> in_order() {
		std::stack<std::shared_ptr<AVLTreeNode<T>>> iterations;
		std::vector<std::shared_ptr<AVLTreeNode<T>>> passed;
		std::shared_ptr<AVLTreeNode<T>> cur = root;

		while (!iterations.empty() || cur) {

			while (cur) {
				iterations.push(cur);
				cur = cur->left;
			}

			if (!iterations.empty()) {
				passed.push_back(iterations.top());
				iterations.pop();

				cur = passed.back()->right;
			}
		}
		return passed;
	}

	void add(int key) {
		root = do_add(key, root);
	}

	std::shared_ptr<AVLTreeNode<T>> do_add(int key, std::shared_ptr<AVLTreeNode<T>> node) {
		if (!node)
			return balance(std::make_shared<AVLTreeNode<T>>(key));

		if (cmp(key, node->key))
			node->left = do_add(key, node->left);
		else
			node->right = do_add(key, node->right);

		return balance(node);
	}

	void delete_key(int key) {
		root = do_delete(root, key);
	}

	std::shared_ptr<AVLTreeNode<T>> do_delete(std::shared_ptr<AVLTreeNode<T>> node, int key) {
		if (!node)
			return NULL;
		if (node->key < key) {
			node->right = do_delete(node->right, key);
		}
		else
		{
			if (node->key > key)
				node->left = do_delete(node->left, key);
			else
			{
				std::shared_ptr<AVLTreeNode<T>> left = node->left;
				std::shared_ptr<AVLTreeNode<T>> right = node->right;

				if (!right)
					return left;
				if (!left)
					return right;

				// replacing
				if (left->height >= right->height) {
					std::shared_ptr<AVLTreeNode<T>> max_sub_tree = left;
					while (max_sub_tree->right)
						max_sub_tree = max_sub_tree->right;
					max_sub_tree->left = removeMax(left);
					max_sub_tree->right = right;

					return balance(max_sub_tree);
				}
				else {
					std::shared_ptr<AVLTreeNode<T>> min_sub_tree = right;
					while (min_sub_tree->left)
						min_sub_tree = min_sub_tree->left;
					min_sub_tree->right = removeMin(right);
					min_sub_tree->left = left;

					return balance(min_sub_tree);
				}
			}
		}
		return balance(node);
	}

	std::shared_ptr<AVLTreeNode<T>> removeMin(std::shared_ptr<AVLTreeNode<T>> node)
	{
		if (!node->left)
			return node->right;
		node->left = removeMin(node->left);
		return balance(node);
	}

	std::shared_ptr<AVLTreeNode<T>> removeMax(std::shared_ptr<AVLTreeNode<T>> node)
	{
		if (!node->right)
			return node->left;
		node->right = removeMax(node->right);
		return balance(node);
	}

	int get_k_stat(int k) {
		return do_k_stat(root, k);
	}

private:
	void update_node_count(std::shared_ptr<AVLTreeNode<T>> node) {
		if (!node)
			return;

		node->count = 1;
		if (node->left)
			node->count += node->left->count;
		if (node->right)
			node->count += node->right->count;
	}

	int height_diff(std::shared_ptr<AVLTreeNode<T>> node) {
		if (!node || !node->right && !node->left)
			return 0;
		if (!node->right)
			return -node->left->height;
		if (!node->left)
			return node->right->height;
		return node->right->height - node->left->height;
	}

	void update_node_height(std::shared_ptr<AVLTreeNode<T>> node) {
		if (!node)
			return;
		int height_left = 0;
		int height_right = 0;
		if (node->left)
			height_left = node->left->height;
		if (node->right)
			height_right = node->right->height;
		node->height = std::max(height_left, height_right) + 1;
	}

	std::shared_ptr<AVLTreeNode<T>> small_left(std::shared_ptr<AVLTreeNode<T>> a) {
		std::shared_ptr<AVLTreeNode<T>> b = a->right;
		a->right = b->left;
		b->left = a;
		update_node_height(a);
		update_node_height(b);

		update_node_count(a);
		update_node_count(b);
		return b;
	}

	std::shared_ptr<AVLTreeNode<T>> small_right(std::shared_ptr<AVLTreeNode<T>> b) {
		std::shared_ptr<AVLTreeNode<T>> a = b->left;
		b->left = a->right;
		a->right = b;
		update_node_height(b);
		update_node_height(a);

		update_node_count(b);
		update_node_count(a);
		return a;
	}

	std::shared_ptr<AVLTreeNode<T>> balance(std::shared_ptr<AVLTreeNode<T>> a) {
		update_node_height(a);

		if (height_diff(a) == 2) {
			if (height_diff(a->right) < 0)
				a->right = small_right(a->right);
			return small_left(a);
		}

		if (height_diff(a) == -2) {
			if (height_diff(a->left) > 0)
				a->left = small_left(a->left);
			return small_right(a);
		}

		update_node_count(a);
		return a;
	}

	int do_k_stat(std::shared_ptr<AVLTreeNode<T>> node, int k) {
		if (!node)
			return -1;
		if (k >= node->count)
			return -1;

		int leftCount = 0;
		if (node->left) {
			leftCount = node->left->count;
			if (leftCount > k)
				return do_k_stat(node->left, k);
		}

		if (leftCount == k)
			return node->key;

		if (node->right) {
			k = k - leftCount - 1;
			return do_k_stat(node->right, k);
		}
		else {
			return node->key;
		}

		// error
		return -1;
	}

	std::shared_ptr<AVLTreeNode<T>> root;
	Comparator cmp;
};

void run4_2() {

	auto tree = std::make_shared<AVLTree<int>>();
	//auto tree = new AVLTree<int>();

	int N;
	int a = 0;
	int k = 0;

	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> a >> k;
		if (a >= 0)
			tree->add(a);
		else
			tree->delete_key(-a);

		std::cout << tree->get_k_stat(k);

		if (i < N - 1)
			std::cout << '\n';
	}
}