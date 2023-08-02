#include "function.h"

#include <iostream>
#include <fstream>

#include <string>

const std::string records_table = "high_scores.txt";

int main() {

    // Ask about name
	std::cout << "Hello!\nWelcome to the game 'Guess the integer number up to 100'\nEnter your name:" << std::endl;
	std::string user_name; //user_name
	std::cin >> user_name;

    bool win = false;

    int attempts_count = check_value(random_value(), win);

    /*std::cout << "Number of attempts:" << attempts_count << std::endl;
    std::cout << "Win:" << win << std::endl;
    return 0;*/

    if (win) {
        read_records(records_table);
        write_records(records_table, user_name, attempts_count);
    }

}   