#include "utils.h"

bool is_power_of_two(int x) { return (x & (x - 1)) == 0; }
