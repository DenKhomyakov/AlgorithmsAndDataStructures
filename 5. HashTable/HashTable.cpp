#include <iostream>

#include "HashTable.h"

using std::cout;
using std::endl;

int HashTable::Function(int k, int i)
{
	return (k + m_c * i + m_d * i * i) % m_N;
}

HashTable::HashTable(int tableSize)
{
	m_N = tableSize;
	m_count = 0;

	m_items = new HashTableItem * [m_N];

	for (int i = 0; i < m_N; i++)
	{
		m_items[i] = nullptr;
	}
}

HashTable::HashTable(const HashTable& other)
{
	m_N = other.m_N;
	m_count = other.m_count;

	m_items = new HashTableItem * [m_N];

	for (int i = 0; i < m_N; i++)
	{
		if (other.m_items[i] == nullptr)
		{
			m_items[i] = nullptr;
		}
		else
		{
			m_items[i] = new HashTableItem;
			m_items[i]->m_key = other.m_items[i]->m_key;
			m_items[i]->m_value = other.m_items[i]->m_value;
		}
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < m_N; i++)
	{
		HashTableItem* item = m_items[i];

		if (item != nullptr)
		{
			delete item;
		}
	}

	delete[] m_items;
}

bool HashTable::ProcessTable(int (*Routine)(HashTable&, int, int, int), int key, int value = 0)
{
	int i = 0;
	int k = key;

	while (i <= m_N)
	{
		k = Function(k, i);

		int result = Routine(*this, k, key, value);

		if (result == 1)
		{
			return true;
		}
		else if (result == 0)
		{
			return false;
		}

		i++;
	}

	return false;
}

int InsertRoutine(HashTable& other, int k, int key, int value)
{
	if (other.m_items[k] == nullptr)
	{
		HashTableItem* item = new HashTableItem;
		item->m_key = key;
		item->m_value = value;

		other.m_items[k] = item;
		other.m_count++;

		return 1;
	}
	if (other.m_items[k]->m_key = key)
	{
		other.m_items[k]->m_value = value;

		return 1;
	}

	return -1;
}

int RemoveRoutine(HashTable& other, int k, int key, int value)
{
	if (other.m_items[k] == nullptr)
	{
		return 0;
	}
	if (other.m_items[k]->m_key == key)
	{
		delete other.m_items[k];

		other.m_items[k] = nullptr;
		other.m_count--;

		return 1;
	}

	return -1;
}

int CheckRoutine(HashTable& other, int k, int key, int value)
{
	if (other.m_items[k] == nullptr)
	{
		return 0;
	}
	if (other.m_items[k]->m_key == key)
	{
		return 1;
	}

	return -1;
}

bool HashTable::Insert(int key, int value)
{
	if (m_count < m_N)
	{
		return ProcessTable(InsertRoutine, key, value);
	}
	else
	{
		return false;
	}
}

bool HashTable::Remove(int key)
{
	return ProcessTable(RemoveRoutine, key);
}

bool HashTable::Check(int key)
{
	return ProcessTable(CheckRoutine, key);
}

void HashTable::Print()
{
	for (int i = 0; i < m_N; i++)
	{
		if (m_items[i] != nullptr)
		{
			cout << m_items[i]->m_key << " - " << m_items[i]->m_value << endl;
		}
	}
}

HashTable& HashTable::operator=(const HashTable& hashTable)
{
	if (this == &hashTable)
	{
		return *this;
	}

	for (int i = 0; i < m_N; i++)
	{
		HashTableItem* item = m_items[i];

		if (item != nullptr)
		{
			delete item;
		}
	}
	delete[] m_items;

	m_N = hashTable.m_N;
	m_count = hashTable.m_count;
	m_items = new HashTableItem * [m_N];

	for (int i = 0; i < m_N; i++)
	{
		if (hashTable.m_items[i] == nullptr)
		{
			m_items[i] = nullptr;
		}
		else
		{
			m_items[i] = new HashTableItem;
			m_items[i]->m_key = hashTable.m_items[i]->m_key;
			m_items[i]->m_value = hashTable.m_items[i]->m_value;
		}
	}

	return *this;
}

int& HashTable::operator[](int key)
{
	if (!Check(key))
	{
		throw "Bad key!\n";
	}

	int i = 0;
	int k = key;

	do
	{
		k = Function(k, i);

		i++;
	} while (m_items[k]->m_key != key);

	return m_items[k]->m_value;
}

bool HashTable::Resize(int newSize)
{
	if (newSize < m_count)
	{
		return false;
	}

	HashTable newHashTable(newSize);

	for (int i = 0; i < m_N; i++)
	{
		if (m_items[i] != nullptr)
		{
			newHashTable.Insert(m_items[i]->m_key, m_items[i]->m_value);
		}
	}

	*this = newHashTable;

	return true;
}

int HashTable::GetSize()
{
	return m_N;
}