#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

/* Класс "Бинарное дерево" */
class BinaryTree {
public:
	class Node;

	BinaryTree();																// Конструктор по умолчанию
	BinaryTree(const BinaryTree& other);										// Конструктор копирования

	~BinaryTree();																// Деструктор

	Node* GetRoot() const;														// Получение корня дерева

	void ClearTree();															// Очистка дерева

	void DeleteSubtree(Node*& node);											// Удаление поддеревьев узла

	bool isEmpty() const;														// Проверка дерева на пустоту

	BinaryTree CopySubtree(Node* from);											// Копирование поддерева узла

	int GetHeight(Node* node) const;											// Получение высоты дерева
	int GetHeight() const;

	int GetNumNodes(Node* node) const;											// Получение количества узлов дерева
	int GetNumNodes() const;

	int GetMinSearchKey(Node* node) const;										// Получение минимального ключа дерева
	int GetMinSearchKey() const;

	int GetMaxSearchKey(Node* node) const;										// Получение максимального ключа дерева
	int GetMaxSearchKey() const;

	Node* AddSearchNode(Node* node, const int key);								// Добавление узла в дерево
	void AddSearchNode(const int key);

	bool RemoveNode(Node*& node, const int key);								// Удаление узла из дерева по ключу
	bool RemoveNode(const int key);

	bool isBalanced(Node* node);												// Проверка дерева на сбалансированность
	bool isBalanced();

	int GetSumAllKeys(Node* node) const;										// Получение суммы всех ключей дереваФ
	int GetSumAllKeys() const;

	virtual int GetLevelByKey(Node* node, const int key) const;					// Получение уровня вершины по ключу
	int GetLevelByKey(const int ket) const;

	std::vector<int> GetAllKeys(Node* node) const;								// Получение вектора, содержащего все ключи дерева
	std::vector<int> GetAllKeys() const;

	void PrintTree() const;														// Вывод в консоль дерева в горизонтальном виде
	void FillTreeData(Node* node, std::vector<std::vector<int>>& treeData, int level, int left, int right) const;

	void PrintLeaves(Node* node) const;											// Вывод в консоль листьев дерева
	void PrintLeaves() const;

	BinaryTree& operator=(const BinaryTree& other);								// Оператор присваивания

private:
	Node* ProvokeFindParent(Node* node, const int key);
	int ProvokeGetLevelByKey(Node* node, const int data, int height) const;
	void ProvokeDeleteRoot(Node*& node);
	void ProvokeClearSubtree(Node* node);

protected:
	Node* ProvokeCopy(Node* from);

protected:
	Node* m_root = nullptr;
};

/* Класс "Узел бинарного дерева" */
class BinaryTree::Node {
private:
	int m_key;
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_height = 1;

public:
	Node();																		// Конструктор (по умолчанию)				
	Node(int key);																// Конструктор (с параметрами)

	~Node() = default;															// Деструктор

	int GetKey() const;															// Получение ключа
	void SetKey(const int key);													// Установление ключа

	int GetNumChildren();														// Получение количества прямых потомков узла

	Node*& GetLeft();															// Аксессор левого потомка
	const Node* GetLeft() const;

	Node*& GetRight();															// Аксессор правого потомка
	const Node* GetRight() const;

	void SetLeft(Node* left);													// Мутатор левого потомка
	void SetRight(Node* right);													// Мутатор правого потомка
};
