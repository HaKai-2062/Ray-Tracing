#include "interval.hpp"
#include "utility.hpp"

static Interval s_Empty = Interval(std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
static Interval s_Universe = Interval(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
