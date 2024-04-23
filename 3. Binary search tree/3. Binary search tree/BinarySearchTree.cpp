#include "BinarySearchTree.h"

/* Конструктор (по умолчанию) */
BinarySearchTree::BinarySearchTree() {
}

/* Деструктор */
BinarySearchTree::~BinarySearchTree() {
}

/* Копирование поддерева узла */
BinarySearchTree BinarySearchTree::CopySubtree(Node* copiedRoot) {
	BinarySearchTree copying;
	copying.m_root = ProvokeCopy(copiedRoot);

	return copying;
}

/* Получение минимального ключа дерева */
int BinarySearchTree::GetMinKey(BinaryTree::Node* node) const {
	if (!node) {
		return INT_MAX;
	}

	BinaryTree::Node* pointerNode = node;

	while (pointerNode->GetLeft()) {
		pointerNode = pointerNode->GetLeft();
	}

	return pointerNode->GetKey();
}

/* Получение максимального ключа дерева */
int BinarySearchTree::GetMaxKey(BinaryTree::Node* node) const {
	if (!node) {
		return INT_MIN;
	}

	BinaryTree::Node* pointerNode = node;

	while (pointerNode->GetRight()) {
		pointerNode = pointerNode->GetRight();
	}

	return pointerNode->GetKey();
}

/* Добавление узла в дерево */
BinaryTree::Node* BinarySearchTree::AddNode(BinaryTree::Node* node, const int key) {
	if (!node) {
		node = new BinaryTree::Node(key);

		return node;
	}
	if (node->GetKey() > key) {
		node->SetLeft(AddNode(node->GetLeft(), key));
	}
	else {
		node->SetRight(AddNode(node->GetRight(), key));
	}

	return node;
}

/* Удаление узла из дерева по ключу */
bool BinarySearchTree::RemoveNode(BinaryTree::Node*& node, const int key) {
	bool deletedNode = false;
	node = RemoveNode(node, key, deletedNode);

	return deletedNode;
}

BinaryTree::Node* BinarySearchTree::RemoveNode(BinaryTree::Node* node, const int key, bool& deletedNode) {
	if (!node) {
		return nullptr;
	}
	if (key < node->GetKey()) {
		node->SetLeft(RemoveNode(node->GetLeft(), key, deletedNode));
	}
	else if (key > node->GetKey()) {
		node->SetRight(RemoveNode(node->GetRight(), key, deletedNode));
	}
	else {
		deletedNode = true;

		if (!node->GetLeft()) {
			BinaryTree::Node* rightNode = node->GetRight();
			delete node;

			return rightNode;
		}
		else if (!node->GetRight()) {
			BinaryTree::Node* leftNode = node->GetLeft();
			delete node;

			return leftNode;
		}
		else {
			BinaryTree::Node* replacementNode = node->GetRight();
			BinaryTree::Node* parentNode = nullptr;

			while (replacementNode->GetLeft()) {
				parentNode = replacementNode;
				replacementNode = replacementNode->GetLeft();
			}

			if (!parentNode) {
				replacementNode->SetLeft(node->GetLeft());
				delete node;

				return replacementNode;
			}

			parentNode->SetLeft(replacementNode->GetRight());
			replacementNode->SetLeft(node->GetLeft());
			replacementNode->SetRight(node->GetRight());
			delete node;

			return replacementNode;
		}
	}

	return node;
}

/* Поиск узла дерева по ключу */
const BinaryTree::Node* BinarySearchTree::Search(const int key) const {
	return Search(m_root, key);
}

const BinaryTree::Node* BinarySearchTree::Search(BinaryTree::Node* node, const int key) const {
	if (!node) {
		return nullptr;
	}

	BinaryTree::Node* pointerNode = node;

	while (pointerNode) {
		if (key > pointerNode->GetKey()) {
			pointerNode = pointerNode->GetRight();
		}
		else if (key < pointerNode->GetKey()) {
			pointerNode = pointerNode->GetLeft();
		}
		else {
			return pointerNode;
		}
	}

	return nullptr;
}

/* Получение уровня вершины по ключу */
int BinarySearchTree::GetLevelByKey(BinaryTree::Node* node, const int key) const {
	if (!node) {
		return -1;
	}

	BinaryTree::Node* pointerNode = node;
	int level = 1;

	while (pointerNode) {
		if (pointerNode->GetKey() < key) {
			pointerNode = pointerNode->GetRight();

			level++;
		}
		else if (pointerNode->GetKey() > key) {
			pointerNode = pointerNode->GetLeft();

			level++;
		}
		else {
			return level;
		}
	}

	return -1;
}

/* Оператор присваивания */
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
	if (this == &other) {
		return *this;
	}

	ClearTree();

	if ((other.m_root)) {
		m_root = ProvokeCopy(other.m_root);
	}
	else {
		m_root = nullptr;
	}

	return *this;
}