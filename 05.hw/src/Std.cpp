#include "../include/Std.h"

#include <cmath>

void Std::update(double next) {
		m_count ++;
		m_sum += next;
		m_mean = m_sum / m_count;
		m_sum_std += pow(next - m_mean, 2);
		m_std = sqrt(m_sum_std/m_count);
	}

double Std::eval() const {return m_std;}

const char *Std::name() const {return "std";}