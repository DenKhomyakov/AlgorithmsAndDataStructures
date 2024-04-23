#pragma once

#include <iostream>
#include <vector>

struct HashTableItem
{
	int m_key;
	int m_value;
};

class HashTable
{
private:
	int m_N;
	HashTableItem** m_items;
	const int m_c = 28 % 5;
	const int m_d = 28 % 7;
	int m_count;
	int Function(int k, int i);

public:
	HashTable(int tableSize);
	HashTable(const HashTable& other);

	~HashTable();

	bool Insert(int key, int value);
	bool Remove(int key);
	bool Check(int key);

	void Print();

	HashTable& operator=(const HashTable& hashTable);
	int& operator[](int key);

	bool Resize(int newSize);

	int GetSize();

private:
	friend int InsertRoutine(HashTable& other, int k, int key, int value);
	friend int RemoveRoutine(HashTable& other, int k, int key, int value);
	friend int CheckRoutine(HashTable& other, int k, int key, int value);

	bool ProcessTable(int (*Routine)(HashTable&, int, int, int), int, int);
};