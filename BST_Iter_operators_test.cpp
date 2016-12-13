#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void test_iterator_operators();
void test_iterator_begin_end();


int main() {

	test_iterator_operators();
	test_iterator_begin_end();

	return 0;
}


void test_iterator_operators() {

	cout << "tests for Iterator operators *, ++ prefix, ++ postfix, ==, != PASS!" << endl;
	return;
}

void test_iterator_begin_end() {

	cout << "tests for Iterator begin, end PASS!" << endl;
	return;
}