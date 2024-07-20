#include "Math.hpp"

Solver::Solver() {}

void Solver::setEquation(std::string e) {
  if (e == "") {
    std::cout << __FILE__ << ": Equation string is empty! Aborting!\n";
  } else {
    equation = e;
  }
}

std::string Solver::getEquation() { return equation; }

// No idea how to do this
void Solver::solve() {}

long double Solver::getTotal() { return total; }
