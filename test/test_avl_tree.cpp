#include <gtest.h>
#include "AVLTree.h"

TEST(avl_tree, can_create_empty_tree) {
	AVLTree<int, int> tree;
	EXPECT_NO_THROW();
}

TEST(avl_tree, can_create_tree_from_node) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree(node);
	EXPECT_NO_THROW();
}

TEST(avl_tree, can_search) {
	AVLTree<int, int> tree;
	EXPECT_NO_THROW(tree.SearchByKey(1));
}

TEST(avl_tree, is_create_from_node_correct) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree(node);
	EXPECT_EQ(tree.SearchByKey(1), 1);
}

TEST(avl_tree, can_copy_tree) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree1(node);
	AVLTree<int, int> tree2;
	EXPECT_NO_THROW(tree2 = tree1);
}

TEST(avl_tree, is_copy_correct) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree1(node);
	AVLTree<int, int> tree2(tree1);
	EXPECT_EQ(tree2.SearchByKey(1), 1);
}

TEST(avl_tree, can_insert_value) {
	AVLTree<int, int> tree;
	EXPECT_NO_THROW(tree.Insert(1, 1));
}

TEST(avl_tree, is_inserted_value_correct) {
	AVLTree<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_EQ(tree.SearchByKey(1), 1);
}

TEST(avl_tree, can_remove_value) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree(node);
	tree.Insert(2, 2);
	tree.Insert(3, 3);
	tree.Insert(4, 4);
	tree.Insert(5, 5);
	EXPECT_NO_THROW(tree.Remove(4));
}

TEST(avl_tree, is_remove_correct) {
	Node<int, int> node(1, 1);
	AVLTree<int, int> tree(node);
	tree.Insert(2, 2);
	tree.Insert(3, 3);
	tree.Insert(4, 4);
	tree.Insert(5, 5);
	tree.Remove(4);
	EXPECT_EQ(tree.SearchByKey(4), 0);
}

TEST(avl_tree, is_balance_correct) {
	Node<int, int> node(3, 3);
	AVLTree<int, int> tree(node);
	tree.Insert(2, 2);
	tree.Insert(4, 4);
	tree.Insert(5, 5);
	tree.Insert(6, 6);
	EXPECT_EQ(tree.GetNode(4)->height, 1);
}