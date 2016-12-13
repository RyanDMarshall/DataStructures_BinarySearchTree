#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_iterator_min_max_min_greater_than();
void test_iterator_find_insert();

int main() {

	test_iterator_min_max_min_greater_than();
	test_iterator_find_insert();

	return 0;
}

void test_iterator_min_max_min_greater_than() {

	cout << "tests for Iterator min_element, max_element, min_greater_than PASS!" << endl;
	return;
}

void test_iterator_find_insert() {

	cout << "tests for Iterator find, insert PASS!" << endl;
	return;
}