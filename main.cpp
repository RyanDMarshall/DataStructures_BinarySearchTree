#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "BinarySearchTree.h"
#include "csvstream.h"
#include "map"
#include "set"

using namespace std;

map<string, int> map_counter();

map<string, double> map_probability();

set<string> unique_words(const string &str);

int main() {

    cout << setprecision(3);

    map<string, double> probability_map = map_probability();


    return 0;
}

map<string, int> map_counter() {

	// Make counter read in data from all files, 
	// store every datum once, as well as how often they occur
	map<string, int> counter;

    csvstream train_small("train_small.csv");
    csvstream test_stream("test_small.csv", ',');
    csvstream w16_projects_exam("w16_projects_exam.csv");
    csvstream sp16_projects_exam("sp16_projects_exam.csv");
    csvstream w14_f15_instructor_student("w14-f15_instructor_student.csv");
    csvstream w16_instructor_student("w16_instructor_student.csv");

 	csvstream::row_type row;
	
 	while (train_small >> row || test_stream >> row || w16_projects_exam >> row
 	|| sp16_projects_exam >> row || w14_f15_instructor_student >> row 
 	|| w16_instructor_student >> row) {

      set<string> words = unique_words(row["content"]);
      set<basic_string<char> >::iterator iter = words.begin();

      while (iter != words.end()) {

      	//cout << *iter << endl;

      	/*if ((counter.insert(iter)).second) {
      		++(*(counter.find(*iter))).second;
      	}*/

      	++iter;
      }
	 }

	//cout << endl << counter.size() << endl;

    return counter;
}

map<string, double> map_probability() {

	map<string, int> counter = map_counter();
	map<string, double> probability;

	return probability;
}

set<string> unique_words(const string &str) {

	istringstream source(str);
	set<string> words;
	string word;

	// Read word by word from the stringstream and insert into the set

	while (source >> word) {
		words.insert(word);
	}

	return words;
}