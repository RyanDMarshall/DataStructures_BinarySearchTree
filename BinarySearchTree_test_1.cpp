#include "BinarySearchTree.h"
#include <sstream>

using namespace std;


void empty_test();
void size_test();
void height_test();

int main() {
  empty_test();
  size_test();
  height_test();
}

void empty_test() {
  BinarySearchTree<int> tree;
  assert(tree.empty());
  cout << "empty_test PASS!" << endl;
}

void size_test() {
  BinarySearchTree<int> tree;
  assert(tree.size() == 0);
  tree.insert(1);
  assert(tree.size() == 1);
  for(int i = 2; i < 10; ++i) {
    tree.insert(i);
  }
  assert(tree.size() == 9);
  BinarySearchTree<int> tree_big;
  for(int i = 1; i < 20; ++i) {
    tree_big.insert(2 * i);
  }
  assert(tree_big.size() == 19);
  cout << "size_test PASS!" << endl;
}

void height_test() {
  BinarySearchTree<int> tree;
  assert(tree.height() == 0);
  tree.insert(10);
  assert(tree.height() == 1);
  tree.insert(5);
  tree.insert(15);
  assert(tree.height() == 2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(7);
  tree.insert(17);
  assert(tree.height() == 4);
  tree.insert(8);
  tree.insert(9);
  tree.insert(2);
  assert(tree.height() == 5);
  BinarySearchTree<int> tree_big;
  for(int i = 1; i < 20; ++i) {
    tree_big.insert(2 * i);
  }
  assert(tree_big.size() == 19);
  cout << "height_test PASS!" << endl;
}
