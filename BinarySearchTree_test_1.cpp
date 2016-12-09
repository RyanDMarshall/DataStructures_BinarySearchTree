#include "BinarySearchTree.h"
#include <sstream>

using namespace std;


//insert doesn't work beyond 2 tiers, may cause error that is happening with empty function

int main() {
  BinarySearchTree<int> tree;
  tree.insert(2);
  tree.insert(1);
  tree.insert(3);
  tree.insert(5);
  tree.insert(4);
  BinarySearchTree<int> tree2;
  tree2 = tree;
  return 0;
}

/*#include "BinarySearchTree.h"
#include <sstream>

using namespace std;

void empty_test();
void size_test();
void height_test();


//insert doesn't work beyond 2 tiers, may cause error that is happening with empty function

int main() {
  //empty_test();
  size_test();
  height_test();

  cout << "BST test 1 passed" << endl;
  return 0;
}

void empty_test()
{
  // BinarySearchTree<int> tester;
  
  // assert(tester.empty());
  // cout << "empty test complete" << endl;
}

void size_test()
{
  BinarySearchTree<int> tester;
  tester.insert(1);
  tester.insert(2);
  tester.insert(3);
  tester.insert(4);
  tester.insert(5);
  tester.insert(6);
  tester.insert(7);
  tester.insert(8);
  tester.insert(9);
  tester.insert(10);

  assert(tester.size() == 10);


  BinarySearchTree<int> tester2;
  tester2.insert(10);
  tester2.insert(9);
  tester2.insert(8);
  tester2.insert(7);
  tester2.insert(6);
  tester2.insert(5);
  tester2.insert(4);
  tester2.insert(3);
  tester2.insert(2);
  tester2.insert(1);

  assert(tester2.size() == 10);

  cout << "size test complete" << endl;
}

void height_test()
{
  BinarySearchTree<int> tester;
  tester.insert(5);
  tester.insert(4);
  tester.insert(6);

  assert(tester.height() == 2);

  tester.insert(3);
  assert(tester.height() == 3);

  tester.insert(2);
  assert(tester.height() == 4);

  tester.insert(1);
  assert(tester.height() == 5);


  cout << "height test complete" << endl;
}*/
