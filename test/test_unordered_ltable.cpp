#include <gtest.h>
#include "UnorderedListBasedTable.h"
#include "Polynomial.h"

TEST(unordered_list_table, can_copy_table) {
	UnorderedLBTable<int, char> table1;
	UnorderedLBTable<int, char> table2;
	EXPECT_NO_THROW(table2 = table1);
}

TEST(unordered_list_table, can_insert_value) {
	UnorderedLBTable<int, char> table;
	EXPECT_NO_THROW(table.Insert(5, 'c'));
}

TEST(unordered_list_table, can_search_by_value) {
	UnorderedLBTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.SearchByValue('c'));
}

TEST(unordered_list_table, can_search_by_key) {
	UnorderedLBTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.SearchByKey(5));
}

TEST(unordered_list_table, can_remove_element_from_table) {
	UnorderedLBTable<int, char> table;
	table.Insert(5, 'c');
	EXPECT_NO_THROW(table.Remove(5));
}

TEST(unordered_list_table, is_inserted_value_correct) {
	UnorderedLBTable<int, char> table;
	Record<int, char> rec(5, 'c');
	table.Insert(5, 'c');
	EXPECT_EQ(table.SearchByKey(5), 'c');
}

TEST(unordered_list_table, is_removed_value_correct) {
	std::vector<Record<int, char>> data;
	data.push_back(Record<int, char>(1, 'a'));
	data.push_back(Record<int, char>(2, 'b'));
	data.push_back(Record<int, char>(3, 'c'));

	UnorderedLBTable<int, char> table(data);

	table.Remove(2);
	EXPECT_EQ(table.SearchByKey(2), NULL);
}

TEST(unordered_list_table, can_insert_polynomial) {
	UnorderedLBTable<int, Polynomial<int>> table;

	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;
	obj1.push(m1);

	EXPECT_NO_THROW(table.Insert(1, obj1));
}

TEST(unordered_list_table, is_insert_polynomial_correct) {
	UnorderedLBTable<int, Polynomial<int>> table;

	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;
	obj1.push(m1);

	table.Insert(1, obj1);

	EXPECT_TRUE(*table.SearchByKey(1).monoms.Begin() == m1);
}

//etc.