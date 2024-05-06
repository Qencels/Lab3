#pragma once
#include "AbstractTable.h"
#include <vector>

template <typename keyType, typename valType>
class UnorderedABTable : public Table<keyType, valType> {
private:
	std::vector<Record<keyType, valType>> records;

public:
    UnorderedABTable(std::size_t size = 0);
	UnorderedABTable(const Record<keyType, valType>& record);
	UnorderedABTable(const std::vector<Record<keyType, valType>>& recs);
	UnorderedABTable(const UnorderedABTable& table);
	UnorderedABTable(UnorderedABTable&& table) noexcept;

	UnorderedABTable<keyType, valType>& operator=(const UnorderedABTable& table);
	UnorderedABTable<keyType, valType>& operator=(UnorderedABTable&& table) noexcept;

	virtual ~UnorderedABTable() {};

	virtual void Insert(const keyType& key, const valType& value);
	virtual void Remove(const keyType& key);

	virtual const valType& SearchByKey(const keyType& key);
	virtual const keyType& SearchByValue(const valType& val);

    std::size_t Size() const noexcept { return records.size(); }

	const std::vector<Record<keyType, valType>>& GetRecords() const noexcept { return records; }

};

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>::UnorderedABTable(std::size_t size) {
	records.resize(size);
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>::UnorderedABTable(const Record<keyType, valType>& record) {
	records.push_back(Record<keyType, valType>(record.key, record.val));
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>::UnorderedABTable(const std::vector<Record<keyType, valType>>& recs) {
    for (std::size_t i = 0; i < recs.size(); i++) {
		this->records.push_back(Record<keyType, valType>(recs[i].key, recs[i].val));
	}
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>::UnorderedABTable(const UnorderedABTable& table) {
	this->records.assign(table.records.begin(), table.records.end());
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>::UnorderedABTable(UnorderedABTable&& table) noexcept {
	this->records.swap(table.records);
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>& UnorderedABTable<keyType, valType>::operator=(const UnorderedABTable& table) {
	this->records.assign(table.records.begin(), table.records.end());
	return *this;
}

template<typename keyType, typename valType>
UnorderedABTable<keyType, valType>& UnorderedABTable<keyType, valType>::operator=(UnorderedABTable&& table) noexcept {
	this->records.swap(table.records);
	return *this;
}

template<typename keyType, typename valType>
void UnorderedABTable<keyType, valType>::Insert(const keyType& key, const valType& value) {
	
    for (std::size_t i = 0; i < records.size(); i++) {
		if (records[i].key == key) {
			records[i].val = value;
			return;
		}
	}

	records.push_back(Record<keyType, valType>(key, value));
}

template<typename keyType, typename valType>
void UnorderedABTable<keyType, valType>::Remove(const keyType& key) {
	auto it = records.begin();
    for (std::size_t i = 0; i < records.size(); i++) {
		if (records[i].key == key) { 
			records.erase(it); 
			return;
		}
		it++;
	}
}

template<typename keyType, typename valType>
const valType& UnorderedABTable<keyType, valType>::SearchByKey(const keyType& key) {
    for (std::size_t i = 0; i < records.size(); i++) {
		if (records[i].key == key) return records[i].val;
	}
	return valType();
}

template<typename keyType, typename valType>
const keyType& UnorderedABTable<keyType, valType>::SearchByValue(const valType& val) {
    for (std::size_t i = 0; i < records.size(); i++) {
		if (records[i].val == val) return records[i].key;
	}
	return keyType();
}
