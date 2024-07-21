#pragma once
#include <iostream>

class Solver {
public:
  Solver();
  void setEquation(std::string e);
  std::string getEquation();
  void solve();
  void parse();
  long double getTotal();

private:
  std::string equation;
  long double total;
};
