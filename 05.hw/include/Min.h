#pragma once

#include "IStatistics.h"

#include <limits>


class Min : public IStatistics {
public:
	Min ();
	void update(double next) override; 

	double eval() const override;

	const char * name() const override ;

private:
	double m_min;
};