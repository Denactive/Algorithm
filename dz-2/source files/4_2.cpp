#include "Header.h"

template <typename T>
struct AVLTreeNode {
	T key;
	int count;
	int height;
	AVLTreeNode* left;
	AVLTreeNode* right;

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
	AVLTree(AVLTreeNode<T>* root = NULL)
		: root(root)
	{
	}

	void Add(int key) {
		root = doAdd(key, root);
	}

	AVLTreeNode<T>* doAdd(int key, AVLTreeNode<T>* node) {
		if (!node)
			return AVLBalance(new AVLTreeNode<T>(key));
		
		if (cmp(key, node->key))
			node->left = doAdd(key, node->left);
		else 
			node->right = doAdd(key, node->right);
		
		return AVLBalance(node);
	}

	void Delete(int key) {
		root = doDelete(root, key);
	}

	AVLTreeNode<T>* doDelete(AVLTreeNode<T>* root, int key) {
		if (!root)
			return NULL;

		if (key == root->key) {
			AVLTreeNode<T>* tmp;
			if (!root->right) {
				tmp = root->left;
			} else {
				AVLTreeNode<T>* top = root->right;
				if (!top->left) {
					top->left = root->left;
					AVLCount(top);
					tmp = root->right;
				}
				else {
					AVLTreeNode<T>* child = top->left;
					while (child->left) {
						top = child;
						child = child->left;
					}
					top->left = child->right;
					AVLCount(top);

					child->left = root->left;
					child->right = root->right;
					tmp = child;
				}
			}

			if (tmp) {
				if (tmp->left) AVLCount(tmp->left);
				if (tmp->right) AVLCount(tmp->right);
			}
			return AVLBalance(tmp);
		}
		else if (cmp(key, root->key)) {
			root->left = doDelete(root->left, key);
			AVLCount(root->left);
		}
		else {
			root->right = doDelete(root->right, key);
			AVLCount(root->right);
		}
		return AVLBalance(root);
	}
	void Print() {
		doPrint(5, root);
	}
	void doPrint(int spaces, AVLTreeNode<T>* node) {
		if (!node) return;
		spaces += 5;

		doPrint(spaces, node->right);
		for (int i = 0; i < spaces; i++) std::cout << " ";
		std::cout << "[" << node->key << "] c:" << node->count << " h:" << node->height << "\n";
		doPrint(spaces, node->left);

		spaces -= 5;
		return;
	}
	int findStatistics(int k) {
		return KStatistics(root, k);
	}
	int KStatistics(AVLTreeNode<T>* node, int k) {
		if (!node) { /*cout << "root null\n";*/ return -1; }
		if (k >= node->count) { /*cout << "k=" << k << " higher than " << node->count << "\n";*/ return -1; }
		int leftCount = 0;
		if (node->left) {
			leftCount = node->left->count;
			if (leftCount > k) return KStatistics(node->left, k);
		}
		if (leftCount == k) return node->key;
		if (node->right) {
			k = k - leftCount - 1;
			return KStatistics(node->right, k);
		}
		else {
			return node->key;
		}
		//cout << "error in Kstatistics\n";
		return -1;
	}

private:
	void AVLCount(AVLTreeNode<T>* root) {
		if (!root) return;
		if (root->left) AVLCount(root->left);
		if (root->right) AVLCount(root->right);
		root->count = (root->left ? root->left->count : 0) + (root->right ? root->right->count : 0) + 1;
	}

	int AVLDifference(AVLTreeNode<T>* root) {
		if (!root) return 0;
		return (root->right ? root->right->height : 0) - (root->left ? root->left->height : 0);
	}

	void NewHeight(AVLTreeNode<T>* root) {
		if (!root) return;
		int hLeft = root->left ? root->left->height : 0;
		int hRight = root->right ? root->right->height : 0;
		root->height = (hLeft > hRight ? hLeft : hRight) + 1; // Высота наибольшего поддерева + 1
		//if (root->left) NewHeight(root->left);
		//if (root->right) NewHeight(root->right);
	}

	// малый левый поворот
	AVLTreeNode<T>* LeftRotate(AVLTreeNode<T>* a) {
		AVLTreeNode<T>* b = a->right;
		a->right = b->left;
		b->left = a;
		NewHeight(a);
		NewHeight(b);

		AVLCount(a);
		AVLCount(b);
		return b;
	}
	// малый правый поворот
	AVLTreeNode<T>* RightRotate(AVLTreeNode<T>* b) {
		AVLTreeNode<T>* a = b->left;
		b->left = a->right;
		a->right = b;
		NewHeight(b);
		NewHeight(a);

		AVLCount(b);
		AVLCount(a);
		return a;
	}
	// Большой левый и правый повороты
	AVLTreeNode<T>* AVLBalance(AVLTreeNode<T>* a) {
		NewHeight(a);
		if (AVLDifference(a) == 2) { // если большое правое поддерево, выполняем большой малый поворот = МП(b)+МЛ(а)
			if (AVLDifference(a->right) < 0)
				a->right = RightRotate(a->right);
			return LeftRotate(a);
		}
		if (AVLDifference(a) == -2) { // если большое левое поддерево, выполняем большой правый поворот = МЛ(а)+МП(b)
			if (AVLDifference(a->left) > 0)
				a->left = LeftRotate(a->left);
			return RightRotate(a);
		}

		//NewHeight(a);
		AVLCount(a);
		return a;
	}

	AVLTreeNode<T>* root;
	Comparator cmp;
};


