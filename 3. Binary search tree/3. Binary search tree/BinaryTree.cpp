#include "BinaryTree.h"

/* Конструктор по умолчанию */
BinaryTree::Node::Node() {
	m_key = 0;
	m_left = nullptr;
	m_right = nullptr;
}

/* Конструктор (с параметрами) */
BinaryTree::Node::Node(int key) {
	m_key = key;
	m_left = nullptr;
	m_right = nullptr;
}

/* Получение ключа */
int BinaryTree::Node::GetKey() const {
	return m_key;
}

/* Установление ключа */
void BinaryTree::Node::SetKey(int key) {
	m_key = key;
}

/* Получение количества прямых потомков узла */
int BinaryTree::Node::GetNumChildren() {
	int numChildren = 0;

	if (m_left != nullptr) {
		numChildren++;
	}
	if (m_right != nullptr) {
		numChildren++;
	}

	return numChildren;
}

/* Аксессор левого потомка */
BinaryTree::Node*& BinaryTree::Node::GetLeft() {
	return m_left;
}

const BinaryTree::Node* BinaryTree::Node::GetLeft() const {
	return m_left;
}

/* Аксессор правого потомка */
BinaryTree::Node*& BinaryTree::Node::GetRight() {
	return m_right;
}

const BinaryTree::Node* BinaryTree::Node::GetRight() const {
	return m_right;
}

/* Мутатор левого потомка */
void BinaryTree::Node::SetLeft(BinaryTree::Node* left) {
	m_left = left;
}

/* Мутатор правого потомка */
void BinaryTree::Node::SetRight(Node* right) {
	m_right = right;
}

/* Конструктор по умолчанию */
BinaryTree::BinaryTree() {
	m_root = nullptr;
}

/* Конструктор копирования */
BinaryTree::BinaryTree(const BinaryTree& other) {
	m_root = ProvokeCopy(other.m_root);
}

/* Деструктор */
BinaryTree::~BinaryTree() {
	ClearTree();
}

/* Получение корня дерева */
BinaryTree::Node* BinaryTree::GetRoot() const {
	return m_root;
}

/* Очистка дерева */
void BinaryTree::ClearTree() {
	ProvokeClearSubtree(m_root);

	m_root = nullptr;
}

/* Удаление поддеревьев узла */
void BinaryTree::DeleteSubtree(Node*& node) {
	if (!node) {
		return;
	}

	ProvokeClearSubtree(node->GetLeft());
	ProvokeClearSubtree(node->GetRight());

	node->SetLeft(nullptr);
	node->SetRight(nullptr);
}

/* Проверка дерева на пустоту */
bool BinaryTree::isEmpty() const {
	return m_root == nullptr;
}

/* Копирование поддерева узла */
BinaryTree BinaryTree::CopySubtree(Node* copiedRoot) {
	BinaryTree copying;
	copying.m_root = ProvokeCopy(copiedRoot);

	return copying;
}

/* Получение высоты дерева */
int BinaryTree::GetHeight(Node* node) const {
	if (node == nullptr) {
		return 0;
	}

	int leftHeight = GetHeight(node->GetLeft());
	int rightHeight = GetHeight(node->GetRight());

	return std::max(leftHeight, rightHeight) + 1;
}

int BinaryTree::GetHeight() const {
	return GetHeight(m_root);
}

/* Получение количества узлов дерева */
int BinaryTree::GetNumNodes(Node* node) const {
	if (node == nullptr) {
		return 0;
	}

	return 1 + GetNumNodes(node->GetLeft()) + GetNumNodes(node->GetRight());
}

int BinaryTree::GetNumNodes() const {
	return GetNumNodes(m_root);
}

/* Получение минимального ключа дерева */
int BinaryTree::GetMinKey(Node* node) const {
	if (node == nullptr) {
		return INT_MAX;
	}

	int leftMin = GetMinKey(node->GetLeft());
	int rightMin = GetMinKey(node->GetRight());

	return std::min(node->GetKey(), std::min(leftMin, rightMin));
}

int BinaryTree::GetMinKey() const {
	return GetMinKey(m_root);
}

/* Получение максимального ключа дерева */
int BinaryTree::GetMaxKey(Node* node) const {
	if (node == nullptr) {
		return INT_MIN;
	}

	int maxKey = node->GetKey();
	int leftMaxKey = GetMaxKey(node->GetLeft());
	int rightMaxKey = GetMaxKey(node->GetRight());

	if (leftMaxKey > maxKey) {
		maxKey = leftMaxKey;
	}
	if (rightMaxKey > maxKey) {
		maxKey = rightMaxKey;
	}

	return maxKey;
}

int BinaryTree::GetMaxKey() const {
	return GetMaxKey(m_root);
}

/* Добавление узла в дерево */
void BinaryTree::AddNode(const int key) {
	m_root = AddNode(m_root, key);
}

BinaryTree::Node* BinaryTree::AddNode(Node* node, const int key) {
	if (!node) {
		node = new Node(key);
	}
	else if (rand() % 2) {
		node->SetLeft(AddNode(node->GetLeft(), key));
	}
	else {
		node->SetRight(AddNode(node->GetRight(), key));
	}

	return node;
}

/* Удаление узла из дерева по ключу */
bool BinaryTree::RemoveNode(BinaryTree::Node*& node, const int key) {
	/* Если ключ в корне */
	if (!node) {
		return false;
	}

	/* Если ключа не существует */
	Node* parentNode = ProvokeFindParent(node, key);

	if (node->GetKey() == key) {
		ProvokeDeleteRoot(node);

		return true;
	}
	else if (!parentNode) {
		return false;
	}

	Node* removableNode;
	bool isLeft = true;			// Необходимо для определения, какой дочерний узел нужно заменить на новый

	/* Определяем, какой узел дерева подлежит удалению */
	if (parentNode->GetLeft() && parentNode->GetLeft()->GetKey() == key) {
		removableNode = parentNode->GetLeft();
	}
	else {
		removableNode = parentNode->GetRight();
		isLeft = false;
	}

	Node* replacementNode = nullptr;

	/* Проверяем, есть ли у удаляемого узла только один дочерний узел (правый потомок) */
	if (!removableNode->GetLeft() && !removableNode->GetRight()) {
		if (isLeft) {
			parentNode->SetLeft(nullptr);
		}
		else {
			parentNode->SetRight(nullptr);
		}

		delete removableNode;
	}
	/* Проверяем, есть ли у удаляемого узла только один дочерний узел (левый потомок) */
	else if (!removableNode->GetLeft()) {
		replacementNode = removableNode->GetRight();

		if (isLeft) {
			parentNode->SetLeft(nullptr);
		}
		else {
			parentNode->SetRight(nullptr);
		}

		delete removableNode;
		isLeft ? parentNode->SetLeft(replacementNode) : parentNode->SetRight(replacementNode);
	}
	else if (!removableNode->GetRight()) {
		replacementNode = removableNode->GetLeft();
		if (isLeft) {
			parentNode->SetLeft(nullptr);
		}
		else {
			parentNode->SetRight(nullptr);
		}

		delete removableNode;
		isLeft ? parentNode->SetLeft(replacementNode) : parentNode->SetRight(replacementNode);
	}
	/* Проверяем, есть ли у удаляемого узла два дочерних элемента */
	else {
		Node* pointerNode = removableNode;

		while (pointerNode->GetLeft()->GetLeft()) {
			pointerNode = pointerNode->GetLeft();
		}

		replacementNode = pointerNode->GetLeft();
		pointerNode->SetLeft(pointerNode->GetLeft()->GetRight());
		replacementNode->SetLeft(removableNode->GetLeft());
		replacementNode->SetRight(removableNode->GetRight());

		if (isLeft) {
			parentNode->SetLeft(nullptr);
		}
		else {
			parentNode->SetRight(nullptr);
		}

		delete removableNode;
		isLeft ? parentNode->SetLeft(replacementNode) : parentNode->SetRight(replacementNode);
	}

	return true;
}

bool BinaryTree::RemoveNode(const int key) {
	return RemoveNode(m_root, key);
}

/* Проверка дерева на сбалансированность */
bool BinaryTree::isBalanced(Node* node) {
	if (node == nullptr) {
		return true;
	}

	int leftHeight = GetHeight(node->GetLeft());
	int rightHeight = GetHeight(node->GetRight());

	if (std::abs(leftHeight - rightHeight) > 1) {
		return false;
	}

	return isBalanced(node->GetLeft()) && isBalanced(node->GetRight());
}

bool BinaryTree::isBalanced() {
	return isBalanced(m_root);
}

/* Получение суммы всех ключей дерева */
int BinaryTree::GetSumAllKeys(Node* node) const {
	if (node == nullptr) {
		return 0;
	}

	return node->GetKey() + GetSumAllKeys(node->GetLeft()) + GetSumAllKeys(node->GetRight());
}

int BinaryTree::GetSumAllKeys() const {
	return GetSumAllKeys(m_root);
}

/* Получение уровня вершины по ключу */
int BinaryTree::GetLevelByKey(const int data) const {
	return GetLevelByKey(m_root, data);
}

int BinaryTree::GetLevelByKey(Node* node, const int data) const {
	return ProvokeGetLevelByKey(node, data, 1);
}

/* Получение вектора, содержащего все ключи дерева (в глубину) */
std::vector<int> BinaryTree::GetAllKeys(Node* node) const {
	std::vector<int> keys;

	if (node == nullptr) {
		return keys;
	}

	std::vector<int> leftKeys = GetAllKeys(node->GetLeft());
	std::vector<int> rightKeys = GetAllKeys(node->GetRight());

	keys.insert(keys.end(), leftKeys.begin(), leftKeys.end());
	keys.push_back(node->GetKey());
	keys.insert(keys.end(), rightKeys.begin(), rightKeys.end());

	return keys;
}

std::vector<int> BinaryTree::GetAllKeys() const {
	return GetAllKeys(m_root);
}

/* Вывод в консоль дерева в горизонтальном виде (в глубину) */
void BinaryTree::PrintTree() const {
	if (m_root == nullptr) {
		std::cout << "Дерево пустое" << std::endl;

		return;
	}

	int treeHeight = GetHeight(m_root);
	int treeWidth = (1 << treeHeight) - 1;
	std::vector<std::vector<int>> treeData(treeHeight, std::vector<int>(treeWidth, -1));

	FillTreeData(m_root, treeData, 0, 0, treeWidth - 1);

	for (int i = 0; i < treeHeight; ++i) {
		for (int k = 0; k < treeWidth; ++k) {
			if (treeData[i][k] == -1) {
				std::cout << " ";
			}
			else {
				std::cout << treeData[i][k];
			}
		}

		std::cout << std::endl;
	}
}

void BinaryTree::FillTreeData(Node* node, std::vector<std::vector<int>>& treeData, int level, int left, int right) const {
	if (node == nullptr) {
		return;
	}

	int middle = (left + right) / 2;
	treeData[level][middle] = node->GetKey();

	FillTreeData(node->GetLeft(), treeData, level + 1, left, middle - 1);
	FillTreeData(node->GetRight(), treeData, level + 1, middle + 1, right);
}

/* Вывод в консоль листьев дерева (в глубину) */
void BinaryTree::PrintLeaves(Node* node) const {
	if (node == nullptr) {
		return;
	}

	if (node->GetLeft() == nullptr && node->GetRight() == nullptr) {
		std::cout << node->GetKey() << " ";
	}

	PrintLeaves(node->GetLeft());
	PrintLeaves(node->GetRight());
}

void BinaryTree::PrintLeaves() const {
	PrintLeaves(m_root);
}

/* Получение размера дерева (количество узлов) */
int BinaryTree::GetSize() const {
	return m_size;
}

/* Оператор присваивания */
BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
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

/* Private */
BinaryTree::Node* BinaryTree::ProvokeFindParent(Node* node, const int key)
{
	if (!node || node->GetKey() == key) {
		return nullptr;
	}


	if (node->GetLeft() && node->GetLeft()->GetKey() == key) {
		return node;
	}
	if (node->GetRight() && node->GetRight()->GetKey() == key) {
		return node;
	}

	Node* leftParent = ProvokeFindParent(node->GetLeft(), key);

	if (leftParent != nullptr) {
		return leftParent;
	}

	return ProvokeFindParent(node->GetRight(), key);
}

int BinaryTree::ProvokeGetLevelByKey(Node* node, const int data, int height) const {
	if (!node) {
		return -1;
	}

	if (node->GetKey() == data) {
		return height;
	}

	int leftHeight = ProvokeGetLevelByKey(node->GetLeft(), data, height + 1);
	int rightHeight = ProvokeGetLevelByKey(node->GetRight(), data, height + 1);

	if (leftHeight == -1 && rightHeight == -1) {
		return -1;
	}
	else if (leftHeight == -1) {
		return rightHeight;
	}

	return leftHeight;
}

void BinaryTree::ProvokeDeleteRoot(BinaryTree::Node*& node) {
	if (!node) {
		return;
	}

	Node* replacementNode = nullptr;

	if (!node->GetLeft() && !node->GetRight()) {
		delete node;

		node = nullptr;
	}
	else if (!node->GetLeft()) {
		Node* tmp = node;

		node = node->GetRight();

		delete tmp;
	}
	else if (!node->GetRight()) {
		Node* temp = node;

		node = node->GetLeft();

		delete temp;
	}
	else {
		Node* pointerNode = node;

		while (pointerNode->GetLeft()->GetLeft()) {
			pointerNode = pointerNode->GetLeft();
		}

		replacementNode = pointerNode->GetLeft();
		pointerNode->SetLeft(pointerNode->GetLeft()->GetRight());
		replacementNode->SetLeft(node->GetLeft());
		replacementNode->SetRight(node->GetRight());

		Node* tmp = m_root;

		m_root = replacementNode;

		delete tmp;
	}
}

void BinaryTree::ProvokeClearSubtree(BinaryTree::Node* root) {
	if (!root) {
		return;
	}

	ProvokeClearSubtree(root->GetLeft());
	ProvokeClearSubtree(root->GetRight());

	delete root;
}

/* Protected */
BinaryTree::Node* BinaryTree::ProvokeCopy(Node* copiedRoot) {
	if (!copiedRoot) {
		return nullptr;
	}

	Node* copying = new Node(copiedRoot->GetKey());
	copying->SetLeft(ProvokeCopy(copiedRoot->GetLeft()));
	copying->SetRight(ProvokeCopy(copiedRoot->GetRight()));

	return copying;
}