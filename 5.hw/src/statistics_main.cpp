#include "../include/Max.h"
#include "../include/Min.h"
#include "../include/Mean.h"
#include "../include/Std.h"

#include <iostream>

void inputData (IStatistics *array[], size_t count, std::istream& is) {
	double val = 0;
	while (is >> val) {
		for (size_t i = 0; i < count; ++i) {
			(*array[i]).update(val);
		}
	}
}

// Handle invalid input data
int handleInput (std::istream& is) {
	if (!is.eof() && !is.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}
	return 0;
}

// Print results if any
void print (IStatistics *array[], size_t count, std::ostream& os) {
	for (size_t i = 0; i < count; ++i) {
		os << (*array[i]).name() << " = " << (*array[i]).eval() << std::endl;
	}
}

// Clear memory - delete all objects created by new
void clearMemory (IStatistics *array[], size_t count) {
	for (size_t i = 0; i < count; ++i) {
		delete array[i];
	}
}


int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};

	inputData 	(statistics, statistics_count, std::cin);
	handleInput (std::cin);
	print 		(statistics, statistics_count, std::cout);
	clearMemory	(statistics, statistics_count);
	
	return 0;

};