#ifndef KETIDAKPASTIAN_GABUNGAN_H
#define KETIDAKPASTIAN_GABUNGAN_H

#include <string>
#include <utility> // For std::pair

// Type for value and uncertainty pair
using UncertainValue = std::pair<double, double>;

// Public function to calculate uncertainty for combined measurements
void calculateUncertaintyCombined();

// Internal utility functions (if needed by other parts of your project)
UncertainValue evaluateExpression(const std::string& expression);

#endif // UNCERTAINTY_H
