#include <iostream>
#include <cassert>

#include "HashTableTester.h"

using std::cout;
using std::endl;

void HashTableTester::Test(const int tableSize)
{
	cout << "\t" << "Testing hash table" << "\n" << endl;

	m_maxN = tableSize;

	Insert();
	cout << endl;

	Remove();
	cout << endl;

	Assign();
	cout << endl;

	Resize();
}

void HashTableTester::Insert()
{
	HashTable hashTable(m_maxN);

	for (int i = 0; i < m_maxN; i++)
	{
		hashTable.Insert(i, i + 25);
	}

	CheckInsert(hashTable);
}

void HashTableTester::CheckInsert(HashTable hashTable)
{
	cout << "Checking the insert function:" << endl;

	for (int i = 0; i < m_maxN; i++)
	{
		assert(hashTable.Check(i));
	}
}

void HashTableTester::Remove()
{
	HashTable hashTable(m_maxN);

	for (int i = 0; i < m_maxN; i++)
	{
		hashTable.Insert(i, i + 100);
	}

	CheckInsert(hashTable);

	for (int i = 0; i < m_maxN; i++)
	{
		hashTable.Remove(i);
		CheckRemove(hashTable, i);
	}
}

void HashTableTester::CheckRemove(HashTable hashTable, int key)
{
	cout << "Checking the remove function:" << endl;

	assert(!hashTable.Check(key));
}

void HashTableTester::Assign()
{
	HashTable firstHashTable(m_maxN);

	for (int i = 0; i < m_maxN; i++)
	{
		firstHashTable.Insert(i, i + 10);
	}

	CheckInsert(firstHashTable);

	HashTable secondHashTable = firstHashTable;

	CheckAssign(firstHashTable, secondHashTable);
}

void HashTableTester::CheckAssign(HashTable firstHashTable, HashTable secondHashTable)
{
	cout << "Checking the assign function:" << endl;

	assert(firstHashTable.GetSize() == secondHashTable.GetSize());

	for (int i = 0; i < m_maxN; i++)
	{
		assert(firstHashTable[i] == secondHashTable[i]);
	}
}

void HashTableTester::Resize()
{
	HashTable hashTable(m_maxN);

	for (int i = 0; i < m_maxN; i++)
	{
		hashTable.Insert(i, i + 200);
	}

	CheckInsert(hashTable);

	hashTable.Resize(m_maxN + 25);

	CheckResize(hashTable, m_maxN + 25);
}

void HashTableTester::CheckResize(HashTable hashTable, int newSize)
{
	cout << "Checking the resize function:" << endl;

	assert(hashTable.GetSize() == newSize);
}