#include <gtest.h>
#include "ChainedHashTable.h"

TEST(chained_hash_table, can_create_empty_table) {
	ChainedHashTable<int, char> table;
	EXPECT_NO_THROW();
}

TEST(chained_hash_table, can_copy_table) {
	ChainedHashTable<int, char> table1;
	ChainedHashTable<int, char> table2;
	EXPECT_NO_THROW(table1 = table2);
}

TEST(chained_hash_table, can_move_table) {
	ChainedHashTable<int, char> table1 = ChainedHashTable<int, char>();
	EXPECT_NO_THROW();
}

TEST(chained_hash_table, can_create_hash) {
	ChainedHashTable<int, char> table1;
	int key = 10;
	EXPECT_NO_THROW(table1.HashFunction(key));
}

TEST(chained_hash_table, can_insert_element) {
	ChainedHashTable<int, char> table1;
	EXPECT_NO_THROW(table1.Insert(5, 'c'));
}

TEST(chained_hash_table, can_remove_element) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	EXPECT_NO_THROW(table1.Remove(5));
}

TEST(chained_hash_table, can_search_element) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	EXPECT_NO_THROW(table1.SearchByKey(5));
}

TEST(chained_hash_table, is_inserted_element_correct) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	EXPECT_EQ(table1.SearchByKey(5), 'c');
}

TEST(chained_hash_table, is_removed_element_correct) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	table1.Insert(6, 'b');
	table1.Remove(6);
	EXPECT_EQ(table1.SearchByKey(6), 0);
}

TEST(chained_hash_table, is_buckets_system_correct) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	table1.Insert(15, 'b');
	EXPECT_EQ(table1.HashFunction(5), table1.HashFunction(15));
}

TEST(chained_hash_table, is_buckets_system_correct_second) {
	ChainedHashTable<int, char> table1;
	table1.Insert(5, 'c');
	table1.Insert(15, 'b');
	EXPECT_EQ(table1.SearchByKey(15), 'b');
}