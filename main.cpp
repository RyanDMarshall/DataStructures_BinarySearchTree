#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "csvstream.h"
#include "map"
#include "set"

using namespace std;

map<string, string> map_classifier(int& word_count, int& post_count);
//map<string, double> map_probability(int word_count, int post_count);


set<string> unique_words(const string &str);

int main() {

    cout << setprecision(3);

    int word_count = 0;
    int post_count = 0;
    map<string, string> classifier = map_classifier(word_count, post_count);

    return 0;
}

map<string, string> map_classifier(int& word_count, int& post_count) {

	map<string, string> classifier;

  csvstream train_small("train_small.csv");
  csvstream test_small("test_small.csv", ',');
  csvstream w16_projects_exam("w16_projects_exam.csv");
  csvstream sp16_projects_exam("sp16_projects_exam.csv");
  csvstream w14_f15_instructor_student("w14-f15_instructor_student.csv");
  csvstream w16_instructor_student("w16_instructor_student.csv");

 	csvstream::row_type row;

 	string all_word;
 	string all_class;

 	set<string> total_word;
 	set<string> total_class;
	
 	while (train_small >> row || test_small >> row 
 	|| w16_projects_exam >> row || sp16_projects_exam >> row) {

 		++post_count;

 		all_word.append(" ");
 		all_class.append(" ");
 		all_word.append(row["content"]);
 		all_class.append(row["tag"]);
	}

	total_word = unique_words(all_word);
	total_class = unique_words(all_class);

  set<basic_string<char> >::iterator word_iter = total_word.begin();    
  set<basic_string<char> >::iterator classify_iter = total_class.begin();

  while (word_iter != total_word.end()) {
  	cout << *word_iter << endl;

  	++word_iter;
  }

  cout << endl << endl;

  while (classify_iter != total_class.end()) {
  	cout << *classify_iter << endl << endl;

  	++classify_iter;
  }

	word_count = total_word.size();

	return classifier;
}

/*map<string, double> map_probability() {

	map<string, int> counter = map_counter();
	map<string, double> probability;

	return probability;
}*/

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