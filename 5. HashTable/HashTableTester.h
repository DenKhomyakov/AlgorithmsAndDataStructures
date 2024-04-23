#pragma once

#include <iostream>

#include "HashTable.h"

class HashTableTester
{
public:
	HashTableTester() = default;
	~HashTableTester() = default;

	void Test(const int tableSize);

protected:
	void CheckInsert(HashTable hashTable);
	void CheckRemove(HashTable hashTable, int key);
	void CheckAssign(HashTable firstHashTable, HashTable secondHashTable);
	void CheckResize(HashTable hashTable, int newSize);

private:
	void Insert();
	void Remove();
	void Assign();
	void Resize();

private:
	int m_maxN;
};