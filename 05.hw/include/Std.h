#pragma once

#include "IStatistics.h"
#include <cstddef>


class Std : public IStatistics {
public:
	
	void update(double next) override; 

	double eval() const override;

	const char * name() const override ;

	~Std () {delete [] m_double;}

private:
	double *m_double;
	size_t m_size {0};
	
	double m_std {0};
	
};