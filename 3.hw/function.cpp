#include "function.h"

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <ctime>

int random_value() {

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % 100; //const int max_value = 100;

	return random_value;
}

int check_value(const int& random_value, bool& win) {
	int attempts_count = 0;
	int current_value = 0;
	
	std::cout << "Enter your guess ( 0 <= number <=100 ):" << std::endl;

	do {
		
		std::cin >> current_value;

		++attempts_count;

		if (std::cin.fail()) {
		std::cout << "Game over! :(\n		Try again :)" << std::endl;
		break;
		}
		else if ((current_value < 0) || (current_value > 100)) {
			std::cout << "Bad attempt!\nEnter your guess ( 0 <= number <=100 ):" << std::endl;
		}
		else if (current_value > random_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < random_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			win = true;
			std::cout << "\nYOU WIN! :]\nAttempts = " << attempts_count << '\n' << std::endl;
			break;
		}

	} while(true);

	return attempts_count;
}

// Write new high score to the records table
void write_records(std::string records_table, std::string& user_name, int& attempts_count) {
	// We should open the output file in the append mode - we don't want
	// to erase previous results.
	std::ofstream out_records_table{records_table, std::ios_base::app};
	if (!out_records_table.is_open()) {
		std::cout << "Failed to open file for write: " << records_table << "!" << std::endl;
	}

	// Append new results to the table:
	out_records_table << user_name << ' ';
	out_records_table << attempts_count;
	out_records_table << std::endl;
	
}

// Read the high score file and print all results
void read_records(std::string records_table) {
	std::string user_name;
	int attempts_count;
	std::ifstream in_records_table{records_table};
	if (!in_records_table.is_open()) {
		std::cout << "Failed to open file for read: " << records_table << "!" << std::endl;
	}

	std::cout << "High scores table:" << std::endl;

	while (true) {
			
		in_records_table >> user_name; // Read the username first
		in_records_table >> attempts_count; // Read the high score next
		in_records_table.ignore(); // Ignore the end of line symbol

		if (in_records_table.fail()) {
			break;
		}

		// Print the information to the screen
		std::cout << user_name << '\t' << attempts_count << std::endl;
	}
}