#pragma once

#include "IStatistics.h"


class Mean : public IStatistics {
public:
	void update(double next) override; 

	double eval() const override;

	const char * name() const override ;

private:
	int m_count {0};
	double m_sum {0};
	double m_mean {0};
};