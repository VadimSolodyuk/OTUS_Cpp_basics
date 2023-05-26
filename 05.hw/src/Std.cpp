#include "../include/Std.h"
#include <cmath>
#include <cstddef>

void Std::update(double next) {
	if (!m_size) {
		m_size++;
		m_double = new double [m_size];
		m_double [m_size-1] = next;		
	} else {
		m_size++;
		double *old = m_double;
		m_double = new double [m_size];
		for (size_t i = 0; i < (m_size-1); i++) {
		m_double[i] = old[i];
		}
		delete [] old;
		m_double [m_size-1] = next;
	}
		
	m_sum += next;
	m_mean = m_sum / m_size;

	double forVariance{0};
	for (size_t i = 0; i < m_size; i++) {
		forVariance += pow(m_double[i] - m_mean, 2);
	}	
	m_std = sqrt(forVariance / m_size);				
}

double Std::eval() const {return m_std;}

const char *Std::name() const {return "std";}