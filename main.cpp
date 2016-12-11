#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "csvstream.h"
#include "map"
#include "set"

using namespace std;

map<string, string> trainer_by_subject(int& word_count, int& post_count, 
    	int& calculator_count, int& euchre_count, int& exam_count,
    	int& image_count, int& recursion_count, int& statistics_count);
map<string, string> trainer_by_author(int& word_count, int& post_count, 
    	int& student_count, int& instructor_count);

double probability_by_subject(string word, int word_count, int post_count, 
    	int calculator_count, int euchre_count, int exam_count,
    	int image_count, int recursion_count, int statistics_count);
double probability_by_author(string word, int word_count, int post_count, 
    	int student_count, int instructor_count);

int word_counter_given_label(string word, string label);
int total_word_counter(string word);

set<string> unique_words(const string &str);

int main() {

  cout << setprecision(3);

  int word_count_by_subject = 0;
  int post_count_by_subject = 0;
  int word_count_by_author = 0;
  int post_count_by_author = 0;
  int calculator_count = 0;
  int euchre_count = 0;
  int exam_count = 0;
  int image_count = 0;
  int recursion_count = 0;
  int statistics_count = 0;
  int student_count = 0;
  int instructor_count = 0;

  map<string, string> classifier_by_subject = 
  	trainer_by_subject(word_count_by_subject, post_count_by_subject, calculator_count, 
  	euchre_count, exam_count, image_count, recursion_count, statistics_count);

  map<string, string> classifier_by_author = trainer_by_author(word_count_by_author,
  	post_count_by_author, student_count, instructor_count);

 	string word_test, label_test;
 	cout << "Enter a word, dumbass:" << endl;
 	cin >> word_test;
 	cout << "Enter a god Damn label" << endl;
 	cin >> label_test;

 	double prob_by_subject = 0;
 	double prob_by_author = 0;

 	prob_by_subject = probability_by_subject(word_test, word_count_by_subject,
 		post_count_by_subject, calculator_count, euchre_count, exam_count, image_count, 
 		recursion_count, statistics_count);

 	prob_by_author = probability_by_author(word_test, word_count_by_author,
 	  post_count_by_author, student_count, instructor_count);

  cout << "Word Count By Subject = " << word_count_by_subject << endl
  		 << "Word Count By Author = " << word_count_by_author << endl
  		 << "Post Count By Subject = " << post_count_by_subject << endl
  		 << "Post Count By Author = " << post_count_by_author << endl
  		 << "Calculator Count = " << calculator_count << endl
  		 << "Euchre Count = " << euchre_count << endl
  		 << "Exam Count = " << exam_count << endl
  		 << "Image Count = " << image_count << endl
  		 << "Recursion Count = " << recursion_count << endl
  		 << "Statistics Count = " << statistics_count << endl
  		 << "Student Count = " << student_count << endl
  		 << "Instructor Count = " << instructor_count << endl
  		 << "Word Count Given Label = " << word_counter_given_label(word_test, label_test) << endl
  		 << "Total Word Count = " << total_word_counter(word_test) << endl
			 << "Probability by subject = " << prob_by_subject << endl
			 << "Probability by author = " << prob_by_author << endl;

  return 0;
}

map<string, string> trainer_by_subject(int& word_count, int& post_count, 
  	int& calculator_count, int& euchre_count, int& exam_count,
  	int& image_count, int& recursion_count, int& statistics_count) {

	map<string, string> classifier;

  csvstream w16_projects_exam("w16_projects_exam.csv");
 	csvstream::row_type row;

 	string all_word;
 	string all_class;

 	set<string> total_word;
 	set<string> total_class;
	
 	while (w16_projects_exam >> row) {

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

	word_count += total_word.size();

	return classifier;
}

map<string, string> trainer_by_author(int& word_count, 
	int& post_count, int& student_count, int& instructor_count) {

	map<string, string> classifier;

  csvstream w14_f15_instructor_student("w14-f15_instructor_student.csv");
 	csvstream::row_type row;

 	string all_word;
 	string all_class;

 	set<string> total_word;
 	set<string> total_class;
	
 	while (w14_f15_instructor_student >> row) {

 		++post_count;
 		if (row["tag"] == "student") {
 			++student_count;
 		}
 		if (row["tag"] == "instructor") {
 			++instructor_count;
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

	word_count += total_word.size();

	return classifier;
}

double probability_by_subject(string word, int word_count, int post_count, 
    	int calculator_count, int euchre_count, int exam_count,
    	int image_count, int recursion_count, int statistics_count) {

	double probability_calc = 0;

	return probability_calc;
}

double probability_by_author(string word, int word_count, int post_count, 
    	int student_count, int instructor_count) {

	double probability_calc = 0;

	return probability_calc;
}

int word_counter_given_label(string word, string label) {

	int word_counter = 0;

  csvstream w14_f15_instructor_student("w14-f15_instructor_student.csv");
	csvstream w16_projects_exam("w16_projects_exam.csv");
 	csvstream::row_type row;

 	set<string> current_string;

	while (w14_f15_instructor_student >> row || w16_projects_exam >> row) {
		if (row["tag"] == label) {
			current_string = unique_words(row["content"]);

			if (current_string.find(word) != current_string.end()) {
				++word_counter;
			}
		}
	}

	return word_counter;
}

int total_word_counter(string word) {

	int total_count = 0;
	vector<string> labels = {"students", "instructors", "calculator", 
	"euchre", "exam", "image", "recursion", "statistics"};

	for (int i = 0; i < int(labels.size()); ++i) {
		total_count += word_counter_given_label(word, labels.at(i));
	}

	return total_count;
}

set<string> unique_words(const string &str) {

	istringstream source(str);
	set<string> words;
	string word;

	while (source >> word) {
		words.insert(word);
	}

	return words;
}