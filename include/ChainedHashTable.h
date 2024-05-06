#include "List.h"
#include "AbstractTable.h"

#define BUCKETS 10

template<typename keyType, typename valType>
class ChainedHashTable : public Table<keyType, valType> {
private:
	static const int hashBuckets = BUCKETS;
	List<Record<keyType, valType>> table[hashBuckets];

	virtual const keyType& SearchByValue(const valType& val) { return keyType(); } // not applicable

public:
	ChainedHashTable() { }
	ChainedHashTable(const ChainedHashTable& table);
	ChainedHashTable(ChainedHashTable&& table) noexcept;

	ChainedHashTable<keyType, valType>& operator=(const ChainedHashTable& table);
	ChainedHashTable<keyType, valType>& operator=(ChainedHashTable&& table) noexcept;

	int HashFunction(const keyType& key);

	virtual void Insert(const keyType& key, const valType& value);
	virtual void Remove(const keyType& key);
	virtual const valType& SearchByKey(const keyType& key);

    const List<Record<keyType, valType>>* GetRecords() const noexcept { return table; }

};

template<typename keyType, typename valType>
ChainedHashTable<keyType, valType>::ChainedHashTable(const ChainedHashTable& table) {
	for (int i = 0; i < hashBuckets; i++) {
		this->table[i] = table.table[i];
	}
}

template<typename keyType, typename valType>
ChainedHashTable<keyType, valType>::ChainedHashTable(ChainedHashTable&& table) noexcept {
	this->table = table.table;
	table.table = nullptr;
}

template<typename keyType, typename valType>
ChainedHashTable<keyType, valType>& ChainedHashTable<keyType, valType>::operator=(const ChainedHashTable& table) {
	for (int i = 0; i < hashBuckets; i++) {
		this->table[i] = table.table[i];
	}
	return *this;
}

template<typename keyType, typename valType>
ChainedHashTable<keyType, valType>& ChainedHashTable<keyType, valType>::operator=(ChainedHashTable&& table) noexcept {
	this->table = table.table;
	table.table = nullptr;
	return *this;
}

template<typename keyType, typename valType>
int ChainedHashTable<keyType, valType>::HashFunction(const keyType& key) {
	int res = -1;
	try {
		res = (int)key % hashBuckets;
	}
	catch (...) {
		throw std::runtime_error("Non-convertible to Int type!");
	}
	return res;
}

template<typename keyType, typename valType>
void ChainedHashTable<keyType, valType>::Insert(const keyType& key, const valType& value) {
	int hash = HashFunction(key);
	auto& cell = table[hash];

	bool keyExists = false;
	for (auto it = cell.Begin(); it != cell.End(); it++) {
		if (it.target->value.key == key) {
			keyExists = true;
			it.target->value.val = value;
			break;
		}
	}
	if (!keyExists) {
		cell.PushBack(Record<keyType, valType>(key, value));
	}
}

template<typename keyType, typename valType>
void ChainedHashTable<keyType, valType>::Remove(const keyType& key) {
	int hash = HashFunction(key);
	auto& cell = table[hash];

	for (auto it = cell.Begin(); it != cell.End(); it++) {
		if (it.target->value.key == key) {
			cell.Erase(it);
            return;
		}
	}
}

template<typename keyType, typename valType>
const valType& ChainedHashTable<keyType, valType>::SearchByKey(const keyType& key) {
	int hash = HashFunction(key);

	auto& cell = table[hash];

	for (auto it = cell.Begin(); it != cell.End(); it++) {
		if (it.target->value.key == key) {
			return it.target->value.val;
		}
	}

	return valType();
}


