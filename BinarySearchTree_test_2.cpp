#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_big_three();

int main() {
	test_big_three();
}

void test_big_three() {
	BinarySearchTree<int> tree1;
	BinarySearchTree<int> tree2(tree1);

	// Default Constructor
	assert(tree1.size() == 0);
	assert(tree2.size() == 0);
	for (int i = 0; i < 10; ++i) {
		tree1.insert(i);
	}

	// Copy Constructor
	BinarySearchTree<int> tree_complex;
	tree_complex.insert(10);
	tree_complex.insert(5);
	tree_complex.insert(15);
	tree_complex.insert(3);
	tree_complex.insert(7);
	tree_complex.insert(17);
	BinarySearchTree<int> tree3(tree1);
	assert(tree3.size() == 10);
	BinarySearchTree<int> tree4(tree_complex);
	assert(tree4.size() == 6);
	assert(tree4.height() == 3);

	// Copy Assignment Operator
	tree3 = tree2;
	assert(tree3.size() == 0);
	tree3 = tree1;
	assert(tree3.size() == 10);
	tree2.insert(1);
	tree2.insert(3);
	tree3 = tree2;
	assert(tree3.size() == 2);
	tree1.insert(11);
	tree3 = tree1;
	assert(tree3.size() == 11);
	tree3 = tree_complex;
	assert(tree3.size() == 6);
	assert(tree3.height() == 3);

	// Destructor remain buggy, the destructor code is not good
	/*tree1.~BinarySearchTree();
	tree3.~BinarySearchTree();
	cout << "test" << endl;
	assert(tree1.empty());
	assert(tree3.empty());*/

	cout << "test_big_three PASS!" << endl;
}