#include <gtest.h>
#include "OrderedListBasedTable.h"
#include "Polynomial.h"

TEST(ordered_list_table, can_copy_table) {
	OrderedListTable<int, char> table1;
	OrderedListTable<int, char> table2;
	EXPECT_NO_THROW(table2 = table1);
}

TEST(ordered_list_table, can_insert_value) {
	OrderedListTable<int, char> table;
	EXPECT_NO_THROW(table.Insert(5, 'c'));
}

TEST(ordered_list_table, can_search_by_value) {
	OrderedListTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.SearchByValue('c'));
}

TEST(ordered_list_table, can_search_by_key) {
	OrderedListTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.SearchByKey(5));
}

TEST(ordered_list_table, can_remove_element_from_table) {
	OrderedListTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.Remove(5));
}

TEST(ordered_list_table, is_inserted_value_correct) {
	OrderedListTable<int, char> table;
	Record<int, char> rec(5, 'c');
	table.Insert(5, 'c');
	EXPECT_EQ(table.SearchByKey(5), 'c');
}

TEST(ordered_list_table, is_order_after_insert_correct) {
	OrderedListTable<int, char> table;

	table.Insert(1, 'a');
	table.Insert(2, 'b');
	table.Insert(4, 'd');
	table.Insert(5, 'e');
	table.Insert(3, 'c');

	auto records = table.GetRecords();
	auto it = records.Begin();
	it++;
	it++;

	EXPECT_EQ(it.target->value.key, 3);
}

TEST(ordered_list_table, is_removed_value_correct) {
	std::vector<Record<int, char>> data;
	data.push_back(Record<int, char>(1, 'a'));
	data.push_back(Record<int, char>(2, 'b'));
	data.push_back(Record<int, char>(3, 'c'));

	OrderedListTable<int, char> table(data);

	table.Remove(2);
	EXPECT_EQ(table.SearchByKey(2), NULL);
}

TEST(ordered_list_table, can_insert_polynomial) {
	OrderedListTable<int, Polynomial<int>> table;

	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;
	obj1.push(m1);

	EXPECT_NO_THROW(table.Insert(1, obj1));
}

TEST(ordered_list_table, is_insert_polynomial_correct) {
	OrderedListTable<int, Polynomial<int>> table;

	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;
	obj1.push(m1);

	table.Insert(1, obj1);

	EXPECT_TRUE(*table.SearchByKey(1).monoms.Begin() == m1);
}

//etc.