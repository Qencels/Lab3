#pragma once
#include "List.h"
#include "AbstractTable.h"
#include <vector>

template<typename keyType, typename valType>
class OrderedListTable : public Table<keyType, valType> {
private:
	List<Record<keyType, valType>> records;

public:
	OrderedListTable() : records(List<Record<keyType, valType>>()) {}
	OrderedListTable(const Record<keyType, valType>& record);
	OrderedListTable(const std::vector<Record<keyType, valType>>& recs) : records(recs) {}
	OrderedListTable(const OrderedListTable& table);
	OrderedListTable(OrderedListTable&& table) noexcept;

	OrderedListTable<keyType, valType>& operator=(const OrderedListTable& table);
	OrderedListTable<keyType, valType>& operator=(OrderedListTable&& table) noexcept;

	virtual ~OrderedListTable() {};

	virtual void Insert(const keyType& key, const valType& value);
	virtual void Remove(const keyType& key);

	virtual const valType& SearchByKey(const keyType& key);
	virtual const keyType& SearchByValue(const valType& val);

	const List<Record<keyType, valType>>& GetRecords() const noexcept { return records; }
};

template<typename keyType, typename valType>
OrderedListTable<keyType, valType>::OrderedListTable(const Record<keyType, valType>& record) {
	records.PushFront(record);
}

template<typename keyType, typename valType>
OrderedListTable<keyType, valType>::OrderedListTable(const OrderedListTable& table) {
	this->records = table.records;
}

template<typename keyType, typename valType>
OrderedListTable<keyType, valType>::OrderedListTable(OrderedListTable&& table) noexcept {
	this->records(table.records);
}

template<typename keyType, typename valType>
OrderedListTable<keyType, valType>& OrderedListTable<keyType, valType>::operator=(const OrderedListTable& table) {
	this->records.Clear();
	this->records = table.records;
	return *this;
}

template<typename keyType, typename valType>
OrderedListTable<keyType, valType>& OrderedListTable<keyType, valType>::operator=(OrderedListTable&& table) noexcept {
	this->records.Clear();
	this->records(table.records);
	return *this;
}

template<typename keyType, typename valType>
void OrderedListTable<keyType, valType>::Insert(const keyType& key, const valType& value) {

    auto it = records.Begin();
    if (records.IsEmpty()) { records.PushFront(Record<keyType, valType>(key, value)); return; }
    if (it.target->value.key == key) { it.target->value.val = value; return; }
    if (it.target->value.key > key) { records.PushFront(Record<keyType, valType>(key, value)); return; }
    while (it.target->pNext) {
        if (it.target->pNext->value.key == key) { it.target->pNext->value.val = value; return; }
        if (it.target->pNext->value.key > key) { records.PushAfter(it, Record<keyType, valType>(key, value)); return; }
        it++;
    }
    records.PushBack(Record<keyType, valType>(key, value));
}

template<typename keyType, typename valType>
void OrderedListTable<keyType, valType>::Remove(const keyType& key) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.key == key) {
			records.Erase(i);
			return;
		}
	}
}

template<typename keyType, typename valType>
inline const valType& OrderedListTable<keyType, valType>::SearchByKey(const keyType& key) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.key == key) {
			return i.target->value.val;
		}
	}

	return valType();
}

template<typename keyType, typename valType>
const keyType& OrderedListTable<keyType, valType>::SearchByValue(const valType& val) {
	for (auto i = records.Begin(); i != records.End(); i++) {
		if (i.target->value.val == val) {
			return i.target->value.key;
		}
	}

	return keyType();
}
