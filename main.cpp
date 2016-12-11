#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "csvstream.h"
#include "map"
#include "set"

using namespace std;

map<string, string> map_classifier(int& word_count, int& post_count, 
    	int& calculator_count, int& euchre_count, int& exam_count,
    	int& image_count, int& recursion_count, int& statistics_count);
map<string, double> map_probability(int& word_count, int& post_count, 
    	int& calculator_count, int& euchre_count, int& exam_count,
    	int& image_count, int& recursion_count, int& statistics_count);


set<string> unique_words(const string &str);

int main() {

    cout << setprecision(3);

    int word_count = 0;
    int post_count = 0;
    int calculator_count = 0;
    int euchre_count = 0;
    int exam_count = 0;
    int image_count = 0;
    int recursion_count = 0;
    int statistics_count = 0;

    map<string, string> classifier = map_classifier(word_count, 
    	post_count, calculator_count, euchre_count, exam_count, 
    	image_count, recursion_count, statistics_count);

    cout << "Word Count = " << word_count << endl
    		 << "Post Count = " << post_count << endl;
    		 // << "Calculator Count = " << calculator_count << endl
    		 // << "Euchre Count = " << euchre_count << endl
    		 // << "Exam Count = " << exam_count << endl
    		 // << "Image Count = " << image_count << endl
    		 // << "Recursion Count = " << recursion_count << endl
    		 // << "Statistics Count = " << statistics_count << endl;

    		     return 0;
}

map<string, string> map_classifier(int& word_count, int& post_count, 
    	int& calculator_count, int& euchre_count, int& exam_count,
    	int& image_count, int& recursion_count, int& statistics_count) {

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
 		if (row["tag"] == "calculator") {
 			++calculator_count;
 		}
 		if (row["tag"] == "euchre") {
 			++euchre_count;
 		}
  	if (row["tag"] == "exam") {
 			++exam_count;
 		}
 		if (row["tag"] == "image") {
 			++image_count;
 		}
 		if (row["tag"] == "recursion") {
 			++recursion_count;
 		}
 		if (row["tag"] == "statistics") {
 			++statistics_count;
 		}


 		all_word.append(row["content"]);
 		all_class.append(row["tag"]);
 		all_word.append(" ");
 		all_class.append(" ");

 		set<basic_string<char> > current_content = unique_words(row["content"]);
 		set<basic_string<char> >::iterator current_iter = current_content.begin();

 		while (current_iter != current_content.end()) {

 			pair<string, string> insert_pair;
 			insert_pair.first = *current_iter;
 			insert_pair.second = row["tag"];

 			classifier.insert(insert_pair);

 			++current_iter;
 		}
	}

	total_word = unique_words(all_word);
	total_class = unique_words(all_class);

  set<basic_string<char> >::iterator word_iter = total_word.begin();    
  set<basic_string<char> >::iterator classify_iter = total_class.begin();

	word_count = total_word.size();

	while (word_iter != total_word.end()) {
		cout << *word_iter << endl;
		++word_iter;
	} cout << endl << endl;
	while (classify_iter != total_class.end()) {
		cout << *classify_iter << endl;
		++classify_iter;
	} cout << endl << endl;

	return classifier;
}

/*map<string, double> map_probability(int& word_count, int& post_count, 
    	int& calculator_count, int& euchre_count, int& exam_count,
    	int& image_count, int& recursion_count, int& statistics_count) {

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