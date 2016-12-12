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

// build a search map for each label, each data point contains the word and its occurence
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
		++iter;
	}
}

string print_class_name(int i, int map_size) {
	if (map_size == 2) {
		if (i == 0) {
			return "student";
		}
		else {
			return "instructor";
		}
	}
	else {
		if (i == 0) {
			return "calculator";
		}
		else if (i == 1) {
			return "euchre";
		}
		else if (i == 2) {
			return "exam";
		}
		else if (i == 3) {
			return "image";
		}
		else if (i == 4) {
			return "recursion";
		}
		else {
			return "statistics";
		}
	}
}

int print_post_amount(int i, int map_size, int post_count,
	int calculator_count, int euchre_count, int exam_count, int image_count, int recursion_count,
	int statistics_count, int student_count, int instructor_count) {
	if (map_size == 2) {
		if (i == 0) {
			return student_count;
		}
		else {
			return instructor_count;
		}
	}
	else {
		if (i == 0) {
			return calculator_count;
		}
		else if (i == 1) {
			return euchre_count;
		}
		else if (i == 2) {
			return exam_count;
		}
		else if (i == 3) {
			return image_count;
		}
		else if (i == 4) {
			return recursion_count;
		}
		else {
			return statistics_count;
		}
	}
}

void print_debug_class(map<string, int> * all_map, int map_size, int post_count,
	int calculator_count, int euchre_count, int exam_count, int image_count, int recursion_count,
	int statistics_count, int student_count, int instructor_count) {
	int i = 0;
	cout <<  "classes:" << endl;

	while (i < map_size) {
		if ((all_map + i)->begin() != (all_map + i)->end()) {

			int label_count = print_post_amount(i, map_size, post_count, calculator_count, 
												euchre_count, exam_count, image_count, 
												recursion_count, statistics_count, 
												student_count, instructor_count);

			double log_prob = log(double(label_count) / double(post_count));
			cout << print_class_name(i, map_size) << ", " << label_count 
			<< " examples, log-prior = " << log_prob << endl;
		}
		++i;
	}
	cout << "classifier parameters:" << endl;
	i = 0;
	while (i < map_size) {
		if ((all_map + i)->begin() != (all_map + i)->end()) {
			map<string, int>::iterator iter = (all_map + i)->begin();

			int label_count = print_post_amount(i, map_size, post_count, calculator_count, 
												euchre_count, exam_count, image_count, 
												recursion_count, statistics_count, 
												student_count, instructor_count);

			for (unsigned int j = 0; j < (all_map + i)->size(); ++j) {
				cout << "  " << print_class_name(i, map_size) << ":" << iter->first;
				cout << ", count = " << iter->second << ", log-likelihood = ";
				cout << log(double(iter->second) / double(label_count)) << endl;
				++iter;
			}
		}
		++i;
	}
	cout << endl;
}

void trainer_by_subject(map<string, int> * all_map, 
	int& word_count, int& post_count, int& calculator_count, 
	int& euchre_count, int& exam_count, int& image_count, 
	int& recursion_count, int& statistics_count, char * train_file, bool is_debug) {

	map<string, string> classifier;
	string trainer(train_file);
 	csvstream trainer_stream(trainer);
 	csvstream::row_type row;
 	string all_word;
 	string all_class;
 	set<string> total_word;
 	set<string> total_class;

 	if (is_debug) {
 		cout << "training data:" << endl;
 	}
	
 	while (trainer_stream >> row) {
 		++post_count;

 		if (is_debug) {
 			cout << "  label = " << row["tag"];
 			cout << ", content = " << row["content"] << endl;
 		}

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
	}
	total_word = unique_words(all_word);
	total_class = unique_words(all_class);

	if (is_debug) {
		cout << "trained on " << post_count << " examples" << endl;
		cout << "vocabulary size = " << total_word.size() << endl << endl;
	}
	word_count += total_word.size();
}

void trainer_by_author(map<string, int> * all_map, int& word_count, 
	int& post_count, int& student_count, int& instructor_count,
	char * train_file, int map_size, bool is_debug) {
	map<string, string> classifier;
	string trainer(train_file);
	csvstream trainer_stream(trainer);
 	csvstream::row_type row;
 	string all_word;
 	string all_class;
 	set<string> total_word;
 	set<string> total_class;

 	if (is_debug) {
 		cout << "training data:" << endl;
 	}
	
 	while (trainer_stream >> row) {

 		if (is_debug) {
 			cout << "  label = " << row["tag"];
 			cout << ", content = " << row["content"] << endl;
 		}

 		++post_count;
 		if (row["tag"] == "student") {	
 			build_map(*(all_map), row["content"]);
 			++student_count;
 		}
 		if (row["tag"] == "instructor") {
 			build_map(*(all_map + 1), row["content"]);
 			++instructor_count;
 		}
		all_word.append(row["content"]);
		all_class.append(row["tag"]);
		all_word.append(" ");
		all_class.append(" ");

	}

	total_word = unique_words(all_word);
	total_class = unique_words(all_class);

	if (is_debug) {
		cout << "trained on " << post_count << " examples" << endl;
		cout << "vocabulary size = " << total_word.size() << endl << endl;
	}

	word_count += total_word.size();
}

// This function counts the occurence of a word in all posts
double word_occur(map<string, int> * all_map, string word, int map_size) {
	//cout << "the word is: " << word << endl;
	double occurence = 0;
	int count = 0;
	while (count < map_size) {
		if ((all_map + count)->find(word) != (all_map + count)->end()) {
			occurence += (all_map + count)->find(word)->second;
		}
		//cout << "occurence: " << occurence << endl;
		++count;
	}
	return occurence;
}

// This function calculates the probablity of each word
// Calls: word_occur
double probability_calc(string test_post, map<string, int> * all_map, int label_count, 
	int total_post, int map_number, int map_size) {
	double probability_calc = 0;
	set<basic_string<char>> post = unique_words(test_post);
	set<basic_string<char>>::iterator iter = post.begin();
	//cout << "probability_calc->map number: " << map_number << endl;
	map<string, int> * map_ptr = all_map;
	while(iter != post.end()) {
		double top = 0;
		double bottom = 0;
		if ((all_map + map_number)->find(*iter) == (all_map + map_number)->end()) {
			if (word_occur(map_ptr, *iter, map_size) == 0) {
				top = 1;
			}
			else {
				top = word_occur(map_ptr, *iter, map_size);
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

// This function calculates the result of each label (subject based)
// Calls: probability_calc
string post_prediction_subject(string test_post, map<string, int> * all_map, int calculator_count, 
	int euchre_count, int exam_count, int image_count, int recursion_count, 
	int statistics_count, int total_post, int map_size) {
	int map_number = 0;
	int i = 0;
	double max_prob = probability_calc(test_post, all_map, calculator_count, 
										total_post, i, map_size);
	while(i < map_size) {
		double prob;
		if (i == 0) {
			prob = max_prob;
		}
		else if (i == 1) {
			prob = probability_calc(test_post, all_map, euchre_count, 
									total_post, i, map_size);
		}
		else if (i == 2) {
			prob = probability_calc(test_post, all_map, exam_count, 
									total_post, i, map_size);
		}
		else if (i == 3) {
			prob = probability_calc(test_post, all_map, image_count, 
									total_post, i, map_size);
		}
		else if (i == 4) {
			prob = probability_calc(test_post, all_map, recursion_count, 
									total_post, i, map_size);
		}
		else {
			prob = probability_calc(test_post, all_map, statistics_count, 
									total_post, i, map_size);
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

// This function calculates the result of each label (author based)
// Calls: probability_calc
string post_prediction_author(string test_post, map<string, int> * all_map, int student_count, 
	int instructor_count, int total_post, int map_size) {
	int map_number = 0;
	int i = 0;
	double max_prob = probability_calc(test_post, all_map, student_count, 
										total_post, i, map_size);
	while(i < map_size) {
		double prob;
		if (i == 0) {
			prob = max_prob;
		}
		else {
			prob = probability_calc(test_post, all_map, instructor_count, 
									total_post, i, map_size);
		}

		// instructor comes before student, so prob >= max_prob
		if (prob >= max_prob) {
			max_prob = prob;
			map_number = i;
		}
		++i;
	}
	if (map_number == 0) {
		return "student";
	}
	else {
		return "instructor";
	}
}

// This function calculates the probabilty of each label and predict the result
// Calls: post_prediction_subject, post_prediction_author
int predict_label(map<string, int> * all_map, int word_count, int post_count, 
	int calculator_count, int euchre_count, int exam_count, int image_count, 
	int recursion_count, int statistics_count, int student_count, int instructor_count, 
	int & test_post_count, char * test_file, int map_size) {

	int predict_correct = 0;
	string tester(test_file);
 	csvstream tester_stream(tester);
 	csvstream::row_type row;

 	while (tester_stream >> row) {
 		test_post_count++;
 		string predict_label;
 		cout << "  correct = " << row["tag"] << ", predicted = ";

 		if (map_size == 6) {
	 		predict_label = post_prediction_subject(row["content"], all_map, calculator_count, 
	 						euchre_count, exam_count, image_count, recursion_count,
	 						statistics_count, post_count, map_size);
	 	}
	 	else {
	 		predict_label = post_prediction_author(row["content"], all_map, student_count, 
	 						instructor_count, post_count, map_size);
	 	}

 		cout << predict_label << endl;

 		if (row["tag"] == predict_label) {
 			++predict_correct;
 		}

 		cout << "  content = " << row["content"] << endl << endl;
 	}
 	return predict_correct;
}

int main(int argc, char **argv) {

	char *train_file, *test_file, *debug;
	bool is_debug = false;

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
			else {
				is_debug = true;
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
	int all_map_size = 0;

	// create a set of map
	map<string, int> exam, stats, image, euchre, calculator, recursion, instructor, student;
	map<string, int> temp_subject[] = {calculator, euchre, exam, image, recursion, stats};
	map<string, int> temp_author[] = {student, instructor};
	map<string, int> * all_map;

	string trainer(train_file);
	string instructor_string = "instructor";
	string student_string = "student";

	if (trainer.find(instructor_string) != string::npos || trainer.find(student_string) != string::npos) {
		all_map = temp_author;
		all_map_size = 2;
		trainer_by_author(all_map, word_count, post_count, student_count, 
						instructor_count, train_file, all_map_size, is_debug);

		if(!is_debug) {
			cout << "trained on " << post_count << " examples" << endl << endl;
		}
		else {
			print_debug_class(all_map, all_map_size, post_count, calculator_count, euchre_count, 
							exam_count, image_count, recursion_count, statistics_count, 
							student_count, instructor_count);
		}

		cout << "test data:" << endl;

		predict_correct = predict_label(all_map, word_count, post_count, calculator_count, 
		euchre_count, exam_count, image_count, recursion_count, statistics_count, student_count,
		instructor_count, test_post_count, test_file, all_map_size);
	}
	else {
		all_map = temp_subject;
		all_map_size = 6;
		trainer_by_subject(all_map, word_count, post_count, calculator_count, 
		euchre_count, exam_count, image_count, recursion_count, statistics_count, 
		train_file, is_debug);

		if(!is_debug) {
			cout << "trained on " << post_count << " examples" << endl << endl;
		}
		else {
			print_debug_class(all_map, all_map_size, post_count, calculator_count, euchre_count, 
							exam_count, image_count, recursion_count, statistics_count, 
							student_count, instructor_count);
		}
		cout << "test data:" << endl;

		predict_correct = predict_label(all_map, word_count, post_count, calculator_count, 
		euchre_count, exam_count, image_count, recursion_count, statistics_count, student_count,
		instructor_count, test_post_count, test_file, all_map_size);

	}

	cout << "performance: " << predict_correct << " / " << test_post_count 
	<< " documents predicted correctly" << endl;

	return 0;
}