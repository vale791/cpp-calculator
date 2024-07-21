#include <cmath>
#include <iostream>

#include "Math.hpp"

Solver solver;

int main() {
  std::string equation;

  double total = 0;
  double currentNumber = 0;

  std::cout << "CALCULATOR\n";
  std::cout << "Enter your equation:\n";

  std::getline(std::cin, equation);

  solver.parse();

  return 0;
}
