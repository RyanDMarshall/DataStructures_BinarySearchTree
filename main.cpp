#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "csvstream.h"
#include "map"
#include "set"
using namespace std;

set<string> unique_words(const string &str) {
	istringstream source(str);
	set<string> words;
	string word;
	while (source >> word) {
		words.insert(word);
	}
	return words;
}

// build a search map for each label, each leaf contains the word and its occurence
void build_map(map<string, int>& map, string content) {
	set<basic_string<char>> input = unique_words(content);
	set<basic_string<char>>::iterator iter = input.begin();
	while(iter != input.end()) {
		if (map.find(*iter) == map.end()) {
			pair<string, int> insert_pair;
			insert_pair.first = *iter;
			insert_pair.second = 1;
			map.insert(insert_pair);
		}
		else {
			map.find(*iter)->second += 1;
		}
		//cout << "the word: " << map.find(*iter)->first << ", value: " << map.find(*iter)->second << endl;
		++iter;
	}
}

void trainer_by_subject(map<string, int> * all_map, 
	int& word_count, int& post_count, int& calculator_count, 
	int& euchre_count, int& exam_count, int& image_count, 
	int& recursion_count, int& statistics_count, char * train_file) {

	map<string, string> classifier;
	string trainer(train_file);
 	csvstream trainer_stream(trainer);
 	csvstream::row_type row;
 	string all_word;
 	string all_class;
 	set<string> total_word;
 	set<string> total_class;
	
 	while (trainer_stream >> row) {
 		++post_count;
 		if (row["tag"] == "calculator") {
 			++calculator_count;
 			build_map(*(all_map), row["content"]);
 		}
 		if (row["tag"] == "euchre") {
 			++euchre_count;
 			build_map(*(all_map + 1), row["content"]);
 		}
  		if (row["tag"] == "exam") {
 			++exam_count;
 			build_map(*(all_map + 2), row["content"]);
 		}
 		if (row["tag"] == "image") {
 			++image_count;
 			build_map(*(all_map + 3), row["content"]);
 		}
 		if (row["tag"] == "recursion") {
 			++recursion_count;
 			build_map(*(all_map + 4), row["content"]);
 		}
 		if (row["tag"] == "statistics") {
 			++statistics_count;
 			build_map(*(all_map + 5), row["content"]);
 		}
		all_word.append(row["content"]);
		all_word.append(" ");
		all_class.append(row["tag"]);
		all_class.append(" ");
		/*set<basic_string<char> > current_content = unique_words(row["content"]);
		set<basic_string<char> >::iterator current_iter = current_content.begin();
	 	while (current_iter != current_content.end()) {
 			pair<string, string> insert_pair;
 			insert_pair.first = *current_iter;
 			insert_pair.second = row["tag"];
 			classifier.insert(insert_pair);
 			++current_iter;
 		}*/
	}
	total_word = unique_words(all_word);
	total_class = unique_words(all_class);
	//What does this two line do
 	set<basic_string<char> >::iterator word_iter = total_word.begin();    
 	set<basic_string<char> >::iterator classify_iter = total_class.begin();
	word_count += total_word.size();
}

void trainer_by_author(map<string, int> all_map[], int& word_count, 
	int& post_count, int& student_count, int& instructor_count,
	char * train_file) {
	map<string, string> classifier;
	string trainer(train_file);
	csvstream trainer_stream(trainer);
 	csvstream::row_type row;
 	string all_word;
 	string all_class;
 	set<string> total_word;
 	set<string> total_class;
	
 	while (trainer_stream >> row) {
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
}

// This function counts the occurence of a word in all posts
double word_occur(map<string, int> * all_map, string word) {
	//cout << "the word is: " << word << endl;
	double occurence = 0;
	int count = 0;
	while (count < 6) {
		if ((all_map + count)->find(word) != (all_map + count)->end()) {
			occurence += (all_map + count)->find(word)->second;
		}
		//cout << "occurence: " << occurence << endl;
		++count;
	}
	return occurence;
}

double probability_calc(string test_post, map<string, int> * all_map, int label_count, int total_post, int map_number) {
	double probability_calc = 0;
	set<basic_string<char>> post = unique_words(test_post);
	set<basic_string<char>>::iterator iter = post.begin();
	//cout << "probability_calc->map number: " << map_number << endl;
	map<string, int> * map_ptr = all_map;
	while(iter != post.end()) {
		double top = 0;
		double bottom = 0;
		if ((all_map + map_number)->find(*iter) == (all_map + map_number)->end()) {
			if (word_occur(map_ptr, *iter) == 0) {
				top = 1;
			}
			else {
				top = word_occur(map_ptr, *iter);
			}
			bottom = total_post;
		}
		else {
			top = (all_map + map_number)->find(*iter)->second;
			bottom = label_count;
		}
		probability_calc += log(top / bottom);
		++iter;
	}
	if (label_count != 0) {
		probability_calc += log(double(label_count) / double(total_post));
	}
	//cout << "total probability: " << probability_calc << endl;
	return probability_calc;
}

string post_prediction(string test_post, map<string, int> * all_map, int calculator_count, 
	int euchre_count, int exam_count, int image_count, int recursion_count, 
	int statistics_count, int total_post) {
	int map_number = 0;
	int i = 0;
	double max_prob = probability_calc(test_post, all_map, calculator_count, total_post, i);
	while(i < 6) {
		double prob;
		if (i == 0) {
			prob = probability_calc(test_post, all_map, calculator_count, total_post, i);
			//cout << "probability for calculator: " << prob << endl;
		}
		else if (i == 1) {
			prob = probability_calc(test_post, all_map, euchre_count, total_post, i);
			//cout << "probability for euchre: " << prob << endl;
		}
		else if (i == 2) {
			prob = probability_calc(test_post, all_map, exam_count, total_post, i);
			//cout << "probability for exam: " << prob << endl;
		}
		else if (i == 3) {
			prob = probability_calc(test_post, all_map, image_count, total_post, i);
			//cout << "probability for image: " << prob << endl;
		}
		else if (i == 4) {
			prob = probability_calc(test_post, all_map, recursion_count, total_post, i);
			//cout << "probability for recursion: " << prob << endl;
		}
		else {
			prob = probability_calc(test_post, all_map, statistics_count, total_post, i);
			//cout << "probability for statistics: " << prob << endl;
		}
		if (prob > max_prob) {
			max_prob = prob;
			map_number = i;
		}
		++i;
	}
	switch(map_number) {
		case 0:
			return "calculator";
			break;
		case 1:
			return "euchre";
			break;
		case 2:
			return "exam";
			break;
		case 3:
			return "image";
			break;
		case 4:
			return "recursion";
			break;
		default:
			return "statistics";
			break;
	}
}

int predict_label(map<string, int> * all_map, 
	int word_count, int post_count, int calculator_count, 
	int euchre_count, int exam_count, int image_count, 
	int recursion_count, int statistics_count, int & test_post_count, char * test_file) {

	int predict_correct = 0;
	string tester(test_file);
 	csvstream tester_stream(tester);
 	csvstream::row_type row;

 	while (tester_stream >> row) {
 		test_post_count++;
 		string predict_label;
 		cout << "  correct = " << row["tag"] << ", predicted = ";
 		predict_label =  post_prediction(row["content"], all_map, calculator_count, 
 				euchre_count, exam_count, image_count, recursion_count,
 				statistics_count, post_count);
 		cout << predict_label << endl;

 		if (row["tag"] == predict_label) {
 			++predict_correct;
 		}

 		cout << "  content = " << row["content"] << endl << endl;
 	}
 	return predict_correct;
}

/*double probability_by_author(string word, int word_count, int post_count, 
    	int student_count, int instructor_count) {
	double probability_calc = 0;
	return probability_calc;
}*/

/*int word_counter_given_label(string word, string label) {
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
}*/

int main(int argc, char **argv) {

	char *train_file, *test_file, *debug;

	if (argc == 4 || argc == 3) {
		train_file = *(argv + 1);
		test_file = *(argv + 2);
		if (argc == 4) {
			debug = *(argv + 3);
			string debug_string(debug);
			if (debug_string != "--debug") {
				cout << "Usage: main TRAIN_FILE TEST_FILE [--debug]" << endl;
				exit(EXIT_FAILURE);
			}
		}
		// Do debug stuff like you should
	}
	else {
		cout << "Usage: main TRAIN_FILE TEST_FILE [--debug]" << endl;
		exit(EXIT_FAILURE);
	}

	cout << setprecision(3);
	int word_count = 0;
	int post_count = 0;
	int test_post_count = 0;
	int calculator_count = 0;
	int euchre_count = 0;
	int exam_count = 0;
	int image_count = 0;
	int recursion_count = 0;
	int statistics_count = 0;
	int student_count = 0;
	int instructor_count = 0;
	int predict_correct = 0;

	// create a set of map
	map<string, int> exam, stats, image, euchre, calculator, recursion;
	map<string, int> temp[] = {calculator, euchre, exam, image, recursion, stats};
	map<string, int> * all_map;
	all_map = temp;

	string trainer(train_file);
	string instructor = "instructor";
	string student = "student";

	if (trainer.find(instructor) != string::npos || trainer.find(student) != string::npos) {
		cout << "author" << endl;
		/*trainer_by_author(all_map, word_count,
		post_count, student_count, instructor_count, train_file);*/
	}
	else {
		trainer_by_subject(all_map, word_count, post_count, calculator_count, 
		euchre_count, exam_count, image_count, recursion_count, statistics_count, 
		train_file);
		cout << "trained on " << post_count << " examples" << endl << endl << "test data:" << endl;
		predict_correct = predict_label(all_map, word_count, post_count, calculator_count, 
		euchre_count, exam_count, image_count, recursion_count, statistics_count, 
		test_post_count, test_file);

	}

	cout << "performance: " << predict_correct << " / " << test_post_count 
	<< " documents predicted correctly" << endl << endl;


		/*string word_test, label_test;
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
		  post_count_by_author, student_count, instructor_count);*/

	/*cout << "Word Count = " << word_count << endl
			 << "Post Count = " << post_count << endl
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
			 << "Probability by author = " << prob_by_author << endl;*/
	return 0;
}