#include <cmath>
#include <string>

#include "Math.hpp"

char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

char operators[5] = {'+', '-', '*', '/', '^'};

template <typename T> bool isFound(T *array, T value, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}

int checkForDecimalPointIndex(std::string numStr) {
  for (int i = 0; i < numStr.length(); i++) {
    if (numStr[i] == '.') {
      return i;
    }
  }
  return -1;
}

double getNumBeforeDecimalPoint(std::string numStr) {
  long long int numLength = numStr.length();
  long long int num = 0;

  std::string newNumStr = numStr.substr(0, checkForDecimalPointIndex(numStr));
  if (newNumStr[0] == '.' || newNumStr[0] == '0') {
    return 0;
  }

  for (int i = 0; i < newNumStr.length(); i++) {
    if (numLength == 1 || i == numLength - 1) {
      int currentNum = newNumStr[i] - '0';
      num += currentNum;
    } else {
      double currentNum = newNumStr[i] - '0';
      currentNum *= pow(10, newNumStr.length() - i - 1);
      num += currentNum;
    }
  }
  return num;
}

double getNumAfterDecimalPoint(std::string numStr) {
  std::string decimalNumStr;
  if (checkForDecimalPointIndex(numStr) == -1) {
    return -1;
  } else {
    decimalNumStr = numStr.substr(checkForDecimalPointIndex(numStr) + 1,
                                  numStr.length() - 1);
  }

  long double numLength = decimalNumStr.length();
  long double decimalNum = 0;

  for (int i = 0; i < decimalNumStr.length(); i++) {
    if (numLength == 1 || i == numLength - 1) {
      int currentNum = decimalNumStr[i] - '0';
      decimalNum += currentNum;
    } else {
      double currentNum = decimalNumStr[i] - '0';
      currentNum *= pow(10, decimalNumStr.length() - i - 1);
      decimalNum += currentNum;
    }
  }

  decimalNum /= pow(10, numLength);

  return decimalNum;
}

std::string getNumStr(int startIndex, std::string equation) {

  int numLength = 0;
  for (int i = startIndex; i < equation.length(); i++) {
    if (equation[i] != '(' && equation[i] != ')' && equation[i] != '*' &&
        equation[i] != '/' && equation[i] != '+' && equation[i] != '-' &&
        equation[i] != ' ' && equation[i] != '^') {
      numLength++;
    } else {
      break;
    }
  }

  std::string numStr = equation.substr(startIndex, numLength);

  return numStr;
}

long double getNum(int startIndex, std::string equation) {
  std::string numStr = getNumStr(startIndex, equation);

  long double num = 0;
  num += getNumBeforeDecimalPoint(numStr);
  if (!(getNumAfterDecimalPoint(numStr) == -1)) {
    num += getNumAfterDecimalPoint(numStr);
  }

  return num;
}

Solver::Solver() {}

void Solver::setEquation(std::string e) {
  if (e == "") {
    std::cout << __FILE__ << ": Equation string is empty! Aborting!\n";
  } else {
    equation = e;
  }
}

std::string Solver::getEquation() { return equation; }

void Solver::parse() {
  bool foundNum;
  bool foundOp;
  bool foundNegative;

  // WARNING: NEGATIVE NUMBER RECOGNITION STILL IN TESTING. NOT COMPLETE.

  for (int i = 0; i < equation.length(); i++) {
    if (isFound(numbers, equation[i], 11) && !foundNum) {
      foundNum = true;
      equationVec.push_back(getNumStr(i, equation));
    } else if (!isFound(numbers, equation[i], 11) && foundNum) {
      foundNum = false;
    } else if (equation[i] == '-' && isFound(numbers, equation[i + 1], 11)) {

      // isFound(operators, equation[i], 5) && !foundOp
      foundNegative = true;
      std::cout << "Found negative\n";
    } else if (isFound(operators, equation[i], 5) && !foundOp &&
               !foundNegative) {
      std::cout << "Found Operator\n";
      foundOp = true;
      foundNegative = false;
    } else if (!isFound(operators, equation[i], 5) && foundOp) {
      foundOp = false;
    }

    // equationVec.push_back(std::string(1, equation[i]));
  }
  for (int i = 0; i < equationVec.size(); ++i) {
    std::cout << equationVec[i] << '\n';
  }
}

// I got an idea on how to do this
void Solver::solve() {}

long double Solver::getTotal() { return total; }
