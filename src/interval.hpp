#pragma once

#include "utility.hpp"

class Interval
{
public:
	Interval() = delete;
	Interval(float min, float max)
		: m_Min(min), m_Max(max) {}

	float Size() const { return m_Max - m_Min; }
	bool Contains(float x) const { return x >= m_Min && x <= m_Max; }
	bool Surrounds(float x) const { return x > m_Min && x < m_Max; }
	
public:
	static const Interval s_Empty, s_Universe;
	float m_Min, m_Max;
};
