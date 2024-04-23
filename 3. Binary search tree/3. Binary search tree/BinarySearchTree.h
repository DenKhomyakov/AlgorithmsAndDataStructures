#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "BinaryTree.h"

/* ����� "�������� ������ ������" */
class BinarySearchTree : public BinaryTree {
public:
	BinarySearchTree();																				// ����������� (�� ���������)

	~BinarySearchTree() override;																	// ����������

	BinarySearchTree CopySubtree(Node* copiedRoot);													// ����������� ��������� ����

	using BinaryTree::GetMinKey;																	// ��������� ������������ ����� ������
	int GetMinKey(BinaryTree::Node* node) const override;

	using BinaryTree::GetMaxKey;																	// ��������� ������������� ����� ������
	int GetMaxKey(BinaryTree::Node* node) const override;

	using BinaryTree::AddNode;																		// ���������� ���� � ������
	BinaryTree::Node* AddNode(BinaryTree::Node* node, const int key) override;

	using BinaryTree::RemoveNode;																	// �������� ���� �� ������ �� �����
	bool RemoveNode(BinaryTree::Node*& node, const int key) override;

	const BinaryTree::Node* Search(const int key) const;											// ����� ���� ������ �� �����
	const BinaryTree::Node* Search(Node* node, const int key) const;

	using BinaryTree::GetLevelByKey;																// ��������� ������ ������� �� �����
	int GetLevelByKey(Node* node, const int key) const override;

	BinarySearchTree& operator=(const BinarySearchTree& other);										// �������� ������������

protected:
	BinaryTree::Node* RemoveNode(BinaryTree::Node* node, const int key, bool& isDeleted);
};
