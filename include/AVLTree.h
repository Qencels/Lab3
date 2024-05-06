#pragma once
#include "AbstractTable.h"

template <typename keyType, typename valType>
struct Node {
	int height;
	valType value;
	keyType key;

    Node* parent;
	Node* pLeft;
	Node* pRight;

	bool operator==(const Node& node);
	bool operator!=(const Node& node);

	Node(const keyType& k, const valType& val, Node* par = nullptr, Node* rightN = nullptr, Node* leftN = nullptr, int h = 1) {
		parent = par;
		key = k;
		value = val;
		height = h;
		pLeft = leftN;
		pRight = rightN;
	}
};

template <typename keyType, typename valType>
class AVLTree : public Table<keyType, valType> {
private:
	Node<keyType, valType>* root;

	Node<keyType, valType>* rMin(Node<keyType, valType>* node);
	Node<keyType, valType>* fMin(Node<keyType, valType>* node);

	Node<keyType, valType>* RightRotate(Node<keyType, valType>* node);
	Node<keyType, valType>* LeftRotate(Node<keyType, valType>* node);

	Node<keyType, valType>* Balancing(Node<keyType, valType>* node);

	Node<keyType, valType>* Copy(Node<keyType, valType>* node);

	int Height(Node<keyType, valType>* node) { return node ? node->height : 0; }
	int Diff(Node<keyType, valType>* node) { return Height(node->pRight) - Height(node->pLeft); }
	void UpdateHeight(Node<keyType, valType>* node);

	Node<keyType, valType>* InsertInit(Node<keyType, valType>* node, const keyType& k, const valType& val, Node<keyType, valType>* prevNode);
	Node<keyType, valType>* RemoveInit(Node<keyType, valType>* node, const keyType& k);

	void Clear(Node<keyType, valType>* node);

	virtual const keyType& SearchByValue(const valType& val) { return keyType(); } // unsupported

public:
	AVLTree() : root(nullptr) {}
	AVLTree(const Node<keyType, valType>& node) : root(new Node<keyType, valType>(node.key, node.value)) {}
	AVLTree(const AVLTree& tree);
	AVLTree(AVLTree&& tree) noexcept;

	AVLTree<keyType, valType>& operator=(const AVLTree& tree);
	AVLTree<keyType, valType>& operator=(AVLTree&& tree) noexcept;

	virtual void Insert(const keyType& key, const valType& val) { InsertInit(root, key, val, nullptr); }
	virtual void Remove(const keyType& key) { RemoveInit(root, key); }

	const Node<keyType, valType>* GetNode(const keyType& k);
    const Node<keyType, valType>* GetRoot() { return root; }

	~AVLTree();

	virtual const valType& SearchByKey(const keyType& key);
};

template <typename keyType, typename valType>
bool Node<keyType, valType>::operator==(const Node& node) {
	return (this->value == node.value) && (this->key == node.key) ;
}

template <typename keyType, typename valType>
bool Node<keyType, valType>::operator!=(const Node& node) {
	return (this->value != node.value) || (this->key != node.key);
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::RightRotate(Node<keyType, valType>* node) {

	Node<keyType, valType>* tmp = node->pLeft;
	Node<keyType, valType>* tmp2 = tmp->pRight;
	Node<keyType, valType>* oldP = node->parent;

	tmp->pRight = node;
	node->pLeft = tmp2;

	tmp->parent = oldP;
	node->parent = tmp;
	if(tmp2 != nullptr) tmp2->parent = node;

	UpdateHeight(node);
	UpdateHeight(tmp);

    if (oldP == nullptr) root = tmp;

	return tmp;

}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::LeftRotate(Node<keyType, valType>* node) {

	Node<keyType, valType>* tmp = node->pRight;
	Node<keyType, valType>* tmp2 = tmp->pLeft;
	Node<keyType, valType>* oldP = node->parent;

	node->pRight = tmp2;
	tmp->pLeft = node;

	node->parent = tmp;
	if (tmp2 != nullptr) tmp2->parent = node;
	tmp->parent = oldP;

	UpdateHeight(node);
	UpdateHeight(tmp);

    if (oldP == nullptr) root = tmp;

	return tmp;

}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::Balancing(Node<keyType, valType>* node) {
	if (Diff(node) > 1) {
		if (Diff(node->pRight) < 0) node->pRight = RightRotate(node->pRight);
		return LeftRotate(node);
	}
	if (Diff(node) < -1)
	{
		if (Diff(node->pLeft) > 0) node->pLeft = LeftRotate(node->pLeft);
		return RightRotate(node);
	}
	UpdateHeight(node);
	return node;
}

template <typename keyType, typename valType>
void AVLTree<keyType, valType>::UpdateHeight(Node<keyType, valType>* node) {
	int hLeft = Height(node->pLeft);
	int hRight = Height(node->pRight);
	node->height = (hLeft > hRight ? hLeft : hRight) + 1;
}

template <typename keyType, typename valType>
void AVLTree<keyType, valType>::Clear(Node<keyType, valType>* node) {
	if (node == nullptr) return;
	if (node) {
		node->parent = nullptr;
		Clear(node->pLeft);
		Clear(node->pRight);
		delete node;
	}
}

template <typename keyType, typename valType>
AVLTree<keyType, valType>::AVLTree(const AVLTree& tree) {
	this->root = Copy(tree.root);
}

template <typename keyType, typename valType>
AVLTree<keyType, valType>::AVLTree(AVLTree&& tree) noexcept {
	this->root = tree.root;
	tree.root = nullptr;
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::Copy(Node<keyType, valType>* node) {
	if (!node) return nullptr;
	if (node->pLeft == nullptr && node->pRight == nullptr) return new Node<keyType, valType>(node->key, node->value, node->parent);
	return new Node<keyType, valType>(node->key, node->value, node->parent, Copy(node->pRight), Copy(node->pLeft), node->height);
}

template <typename keyType, typename valType>
AVLTree<keyType, valType>& AVLTree<keyType, valType>::operator=(const AVLTree& tree) {
	Clear(root);
	this->root = Copy(tree.root);
	return *this;
}

template <typename keyType, typename valType>
AVLTree<keyType, valType>& AVLTree<keyType, valType>::operator=(AVLTree&& tree) noexcept {
	Clear(root);
	this->root = tree.root;
	tree.root = nullptr;

	return *this;
}

template<typename keyType, typename valType>
const Node<keyType, valType>* AVLTree<keyType, valType>::GetNode(const keyType& k) {
	Node<keyType, valType>* currentNode = root;
	while (currentNode) {
		if (currentNode->key == k) return currentNode;
		if (currentNode->key < k) {
			currentNode = currentNode->pRight;
			continue;
		}
		if (currentNode->key > k) {
			currentNode = currentNode->pLeft;
		}
	}
	return nullptr;
}

template <typename keyType, typename valType>
AVLTree<keyType, valType>::~AVLTree() {
	Clear(root);
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::InsertInit(Node<keyType, valType>* node, const keyType& k, const valType& val, Node<keyType, valType>* prevNode) {
	if (!root) { root = new Node<keyType, valType>(k, val); return root; }
	if (!node) return new Node<keyType, valType>(k, val, prevNode);
	if (k < node->key)
		node->pLeft = InsertInit(node->pLeft, k, val, node);
	else if (k > node->key)
		node->pRight = InsertInit(node->pRight, k, val, node);
	else
		node->value = val;
	return Balancing(node);
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::fMin(Node<keyType, valType>* node) {
	return node->pLeft ? fMin(node->pLeft) : node;
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::rMin(Node<keyType, valType>* node) {
	if (node->pLeft == 0)
		return node->pRight;
	node->pLeft = rMin(node->pLeft);
	return Balancing(node);
}

template <typename keyType, typename valType>
Node<keyType, valType>* AVLTree<keyType, valType>::RemoveInit(Node<keyType, valType>* node, const keyType& k) {
	if (!node) return nullptr;
    if (!root) return nullptr;

	if (k < node->key)
		node->pLeft = RemoveInit(node->pLeft, k);
	else if (k > node->key)
		node->pRight = RemoveInit(node->pRight, k);
	else
	{
		Node<keyType, valType>* q = node->pLeft;
		Node<keyType, valType>* r = node->pRight;
		node->parent = nullptr;
		node->pLeft = nullptr;
		node->pRight = nullptr;
		delete node;
		if (!r) return q;
		Node<keyType, valType>* min = fMin(r);
		min->pRight = rMin(r);
		min->pLeft = q;
		return Balancing(min);
	}

	return Balancing(node);
}

template <typename keyType, typename valType>
const valType& AVLTree<keyType, valType>::SearchByKey(const keyType& key) {
	Node<keyType, valType>* currentNode = root;
	while (currentNode) {
		if (currentNode->key == key) return currentNode->value;
		if (currentNode->key < key) {
			currentNode = currentNode->pRight;
			continue;
		}
		if (currentNode->key > key) {
			currentNode = currentNode->pLeft;
		}
	}

	return valType();
}
