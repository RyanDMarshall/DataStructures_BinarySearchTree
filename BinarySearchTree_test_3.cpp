#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_traverse();
void test_invariant();

int main() {
	test_traverse();
	test_invariant();
}

void test_traverse() {
	BinarySearchTree<int> tree1;
	tree1.insert(5);
	tree1.insert(3);
	tree1.insert(7);
	ostringstream oss_preorder, oss_inorder;
	tree1.traverse_preorder(oss_preorder);
	tree1.traverse_inorder(oss_inorder);
	assert(oss_preorder.str() == "5 3 7 ");
	assert(oss_inorder.str() == "3 5 7 ");

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
	ostringstream oss_preorder2, oss_inorder2;
	tree2.traverse_preorder(oss_preorder2);
	tree2.traverse_inorder(oss_inorder2);
	assert(oss_preorder2.str() == "10 5 2 3 8 7 15 12 11 13 20 19 18 ");
	assert(oss_inorder2.str() == "2 3 5 7 8 10 11 12 13 15 18 19 20 ");

	cout << "test_traverse PASS!" << endl;
}

void test_invariant() {
	BinarySearchTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	assert(tree.check_sorting_invariant());

	BinarySearchTree<int>::Iterator iter = tree.begin();
	iter++;
	iter++;
	*iter = 1;
	cout << tree.to_string() << endl;
	assert(!tree.check_sorting_invariant());

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
	assert(tree2.check_sorting_invariant());

	cout << "test_traverse PASS!" << endl;

}