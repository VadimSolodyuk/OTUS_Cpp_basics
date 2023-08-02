#include "../include/Min.h"

#include <limits>


Min::Min() : m_min{std::numeric_limits<double>::max()} {}

void Min::update(double next) {
		if (next < m_min) {
			m_min = next;
		}
	}

double Min::eval() const {return m_min;}

const char * Min::name() const {return "min";}