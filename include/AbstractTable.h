#pragma once

template <typename keyType, typename valType>
class Table {
public:
	virtual void Insert(const keyType& key, const valType& value) = 0;
	virtual void Remove(const keyType& key) = 0;
	virtual const valType& SearchByKey(const keyType& key) = 0;
	virtual const keyType& SearchByValue(const valType& val) = 0;

	virtual ~Table() {}
};

template <typename keyType, typename valType>
struct Record {
	keyType key;
	valType val;

	bool operator==(const Record& record) { return ((this->val == record.val) && (this->key == record.key)); }
	bool operator!=(const Record& record) { return ((this->val != record.val) || (this->key != record.key)); }

	Record(const keyType& k, const valType& value) : key(k), val(value) {}
	Record() : key(keyType()), val(valType()) {}
};