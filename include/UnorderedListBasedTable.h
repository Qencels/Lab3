#pragma once
#include "List.h"
#include "AbstractTable.h"
#include <vector>

template<typename keyType, typename valType>
class UnorderedLBTable : public Table<keyType, valType> {
private:
	List<Record<keyType, valType>> records;

public:
	UnorderedLBTable() : records(List<Record<keyType, valType>>()) {}
	UnorderedLBTable(const Record<keyType, valType>& record);
	UnorderedLBTable(const std::vector<Record<keyType, valType>>& recs) : records(recs) {}
	UnorderedLBTable(const UnorderedLBTable& table);
	UnorderedLBTable(UnorderedLBTable&& table) noexcept;

	UnorderedLBTable<keyType, valType>& operator=(const UnorderedLBTable& table);
	UnorderedLBTable<keyType, valType>& operator=(UnorderedLBTable&& table) noexcept;

	virtual ~UnorderedLBTable() {};

	virtual void Insert(const keyType& key, const valType& value);
	virtual void Remove(const keyType& key);

	virtual const valType& SearchByKey(const keyType& key);
	virtual const keyType& SearchByValue(const valType& val);

	const List<Record<keyType, valType>>& GetRecords() const noexcept { return records; }
};

template<typename keyType, typename valType>
UnorderedLBTable<keyType, valType>::UnorderedLBTable(const Record<keyType, valType>& record) {
	records.PushFront(record);
}

template<typename keyType, typename valType>
UnorderedLBTable<keyType, valType>::UnorderedLBTable(const UnorderedLBTable& table) {
	this->records = table.records;
}

template<typename keyType, typename valType>
UnorderedLBTable<keyType, valType>::UnorderedLBTable(UnorderedLBTable&& table) noexcept {
	this->records(table.records);
}

template<typename keyType, typename valType>
UnorderedLBTable<keyType, valType>& UnorderedLBTable<keyType, valType>::operator=(const UnorderedLBTable& table) {
	this->records.Clear();
	this->records = table.records;
	return *this;
}

template<typename keyType, typename valType>
UnorderedLBTable<keyType, valType>& UnorderedLBTable<keyType, valType>::operator=(UnorderedLBTable&& table) noexcept {
	this->records.Clear();
	this->records(table.records);
	return *this;
}

template<typename keyType, typename valType>
void UnorderedLBTable<keyType, valType>::Insert(const keyType& key, const valType& value) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.key == key) {
			i.target->value.val = value;
			return;
		}
	}

	records.PushBack(Record<keyType, valType>(key, value));
}

template<typename keyType, typename valType>
void UnorderedLBTable<keyType, valType>::Remove(const keyType& key) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.key == key) {
			records.Erase(i);
			return;
		}
	}
}

template<typename keyType, typename valType>
const valType& UnorderedLBTable<keyType, valType>::SearchByKey(const keyType& key) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.key == key) {
			return i.target->value.val;
		}
	}

	return valType();
}

template<typename keyType, typename valType>
const keyType& UnorderedLBTable<keyType, valType>::SearchByValue(const valType& val) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.val == val) {
			return i.target->value.key;
		}
	}

	return keyType();
}
