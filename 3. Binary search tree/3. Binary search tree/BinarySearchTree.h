#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "BinaryTree.h"

/* Класс "Бинарное дерево поиска" */
class BinarySearchTree : public BinaryTree {
public:
	BinarySearchTree();																				// Конструктор (по умолчанию)

	~BinarySearchTree() override;																	// Деструктор

	BinarySearchTree CopySubtree(Node* copiedRoot);													// Копирование поддерева узла

	using BinaryTree::GetMinKey;																	// Получение минимального ключа дерева
	int GetMinKey(BinaryTree::Node* node) const override;

	using BinaryTree::GetMaxKey;																	// Получение максимального ключа дерева
	int GetMaxKey(BinaryTree::Node* node) const override;

	using BinaryTree::AddNode;																		// Добавление узла в дерево
	BinaryTree::Node* AddNode(BinaryTree::Node* node, const int key) override;

	using BinaryTree::RemoveNode;																	// Удаление узла из дерева по ключу
	bool RemoveNode(BinaryTree::Node*& node, const int key) override;

	const BinaryTree::Node* Search(const int key) const;											// Поиск узла дерева по ключу
	const BinaryTree::Node* Search(Node* node, const int key) const;

	using BinaryTree::GetLevelByKey;																// Получение уровня вершины по ключу
	int GetLevelByKey(Node* node, const int key) const override;

	BinarySearchTree& operator=(const BinarySearchTree& other);										// Оператор присваивания

protected:
	BinaryTree::Node* RemoveNode(BinaryTree::Node* node, const int key, bool& isDeleted);
};
