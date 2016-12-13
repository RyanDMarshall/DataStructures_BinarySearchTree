#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_iterator_min_max_min_greater_than();
void test_iterator_find();

int main() {

	test_iterator_min_max_min_greater_than();
	test_iterator_find();

	return 0;
}

void test_iterator_min_max_min_greater_than() {

	BinarySearchTree<int> tree;
	assert(tree.max_element() == tree.end());
	assert(tree.min_element() == tree.end());
	assert(tree.min_greater_than(1) == tree.end());

	tree.insert(1);
	assert(*tree.max_element() == 1);
	assert(*tree.min_element() == 1);
	assert(*tree.min_greater_than(0) == 1);
	assert(tree.min_greater_than(2) == tree.end());


	BinarySearchTree<int> tree2;
	tree2.insert(10);
	tree2.insert(5);
	tree2.insert(15);
	tree2.insert(2);
	tree2.insert(8);
	tree2.insert(12);
	tree2.insert(20);
	tree2.insert(3);
	tree2.insert(7);
	tree2.insert(11);
	tree2.insert(13);
	tree2.insert(19);
	tree2.insert(18);

	assert(*tree2.max_element() == 20);
	assert(*tree2.min_element() == 2);
	assert(*tree2.min_greater_than(1) == 2);
	assert(*tree2.min_greater_than(7) == 8);
	assert(*tree2.min_greater_than(12) == 13);
	assert(*tree2.min_greater_than(17) == 18);
	assert(*tree2.min_greater_than(19) == 20);
	assert(tree2.min_greater_than(20) == tree2.end());
	assert(tree2.min_greater_than(21) == tree2.end());

	cout << "tests for Iterator min_element, max_element, min_greater_than PASS!" << endl;
	return;
}

void test_iterator_find() {


	BinarySearchTree<int> tree;
	assert(tree.find(1) == tree.end());

	tree.insert(100);
	assert(tree.find(1) == tree.end());
	assert(*tree.find(100) == 100);

	BinarySearchTree<int> tree2;
	tree2.insert(10);
	tree2.insert(5);
	tree2.insert(15);
	tree2.insert(2);
	tree2.insert(8);
	tree2.insert(12);
	tree2.insert(20);
	tree2.insert(3);
	tree2.insert(7);
	tree2.insert(11);
	tree2.insert(13);
	tree2.insert(19);
	tree2.insert(18);

	assert(*tree2.find(2) == 2);
	assert(*tree2.find(5) == 5);
	assert(*tree2.find(8) == 8);
	assert(*tree2.find(11) == 11);
	assert(*tree2.find(12) == 12);
	assert(*tree2.find(18) == 18);
	assert(*tree2.find(20) == 20);
	assert(tree2.find(1) == tree.end());
	assert(tree2.find(100) == tree.end());

	cout << "tests for Iterator find PASS!" << endl;
	return;
}