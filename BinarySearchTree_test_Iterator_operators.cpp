#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_iterator_operators_begin_end();

int main() {

	test_iterator_operators_begin_end();

	cout << "All Iterator operator, begin, end tests PASS!" << endl;
	return 0;
}


void test_iterator_operators_begin_end() {

	BinarySearchTree<int> BST_empty;
	BinarySearchTree<int> BST_one;
	BinarySearchTree<int> BST_large;

	BST_one.insert(1);

	BST_large.insert(5);
	BST_large.insert(4);
	BST_large.insert(6);
	BST_large.insert(3);
	BST_large.insert(7);
	BST_large.insert(2);
	BST_large.insert(8);
	BST_large.insert(1);
	BST_large.insert(9);

	// Begin testing empty
	BinarySearchTree<int>::Iterator empty_front = BST_empty.begin();
	BinarySearchTree<int>::Iterator empty_back = BST_empty.end();

	assert(empty_front == empty_back);
	// End testing Empty

	// Begin testing one element
	BinarySearchTree<int>::Iterator one_front = BST_one.begin();
	BinarySearchTree<int>::Iterator one_back = BST_one.end();

	assert(one_front != one_back);
	one_front++;
	assert(one_front == one_back);

	one_front = BST_one.begin();
	one_back = BST_one.end();

	++one_front;
	assert(one_front == one_back);
	// End testing one element

	// Being testing large
	BinarySearchTree<int>::Iterator large_front = BST_large.begin();
	BinarySearchTree<int>::Iterator large_back = BST_large.end();

	assert(*large_front == 1);
	assert(*(++large_front) == 2);
	large_front++;
	assert(*large_front == 3);
	++large_front;
	assert(*large_front == 4);

	++++++++++++large_front;
	assert(large_front == large_back);

	large_front = BST_large.begin();
	BinarySearchTree<int>::Iterator large_front_temp = BST_large.begin();

	large_front_temp++;
	++large_front;
	assert(large_front == large_front_temp);

	++large_front_temp;
	assert(large_front != large_front_temp);
	// End testing large

	cout << "tests for Iterator operators *, ++ prefix, ++ postfix, ==, != PASS!" << endl;

	BinarySearchTree<int> BST_empty_two;
	BinarySearchTree<int> BST_two;
	BinarySearchTree<int> BST_big_number;
	BinarySearchTree<double> BST_less_than_one;

	BST_two.insert(2);

	BST_big_number.insert(1000000);

	for (double i = 0.1; i <= 1.0; i += .01) {
		BST_less_than_one.insert(i);
	}

	BinarySearchTree<int>::Iterator empty_iter;
	BinarySearchTree<double>::Iterator empty_iter_double;

	assert(BST_empty_two.begin() == empty_iter && BST_empty_two.end() == empty_iter);
	assert(*BST_two.begin() == 2 && BST_two.end() == empty_iter);
	assert(*BST_big_number.begin() == 1000000 && BST_big_number.end() == empty_iter);
	assert(*BST_less_than_one.begin() - 0.1 < 0.001 && BST_less_than_one.end() == empty_iter_double);

	cout << "tests for Iterator begin, end PASS!" << endl;
	return;
}

void test_iterator_begin_end() {



	cout << "tests for Iterator begin, end PASS!" << endl;
	return;
}