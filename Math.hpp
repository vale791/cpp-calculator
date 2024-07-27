#pragma once
#include <iostream>
#include <vector>

class Solver {
public:
  Solver();
  void setEquation(std::string e);
  std::string getEquation();
  void solve();
  void parse();
  long double getTotal();
  bool checkEquationValidity();

private:
  std::vector<std::string> equationVec;
  std::string equation;
  long double total;
};
