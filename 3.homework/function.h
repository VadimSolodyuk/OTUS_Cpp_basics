#pragma once

#include <string>

int random_value();

int check_value(const int& random_value, bool& win);

void write_records(std::string records_table, std::string& user_name, int& attempts_count);

void read_records(std::string records_table);

