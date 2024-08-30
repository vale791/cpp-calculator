#include <cmath>
#include <string>

#include "Math.hpp"

char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
char operators[7] = {'+', '-', '*', '/', '^', '(', ')'};

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
  bool foundNegative;

  std::string newNumStr = numStr.substr(0, checkForDecimalPointIndex(numStr));
  if (newNumStr[0] == '.' || newNumStr[0] == '0') {
    return 0;
  }

  for (int i = 0; i < newNumStr.length(); i++) {
    if (numStr[0] == '-' && !foundNegative) {
      foundNegative = true;
      continue;
    } else if (numLength == 1 || i == numLength - 1) {
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

int getNearestNumIndex(int currentIndex, std::string str) {
  for (int i = currentIndex; i < str.length(); ++i) {
    if (isFound(numbers, str[i], 11)) {
      return i;
    }
  }
  return -1;
}

int getNumLength(int startIndex, std::string equation) {
  int numLength = 0;
  for (int i = startIndex; i < equation.length(); i++) {
    if (i == startIndex && equation[i] == '-') {
      ++numLength;
      continue;
    } else if (isFound(numbers, equation[i], 11)) {
      ++numLength;
    } else {
      break;
    }
  }
  return numLength;
}

std::string getNumStr(int startIndex, std::string equation) {
  int numLength = getNumLength(startIndex, equation);

  std::string numStr = equation.substr(startIndex, numLength);

  return numStr;
}

void PrintErrorBase(int i, std::string equation) {
  char spaceChar = ' ';
  char caretChar = '^';
  int nearestNumIndex = getNearestNumIndex(i, equation);
  int endOfNumIndex =
      getNumLength(nearestNumIndex, equation) - 1 + nearestNumIndex;
  std::string spaces(equation.length() -
                         getNumLength(nearestNumIndex, equation) -
                         (equation.length() - endOfNumIndex - 1),
                     spaceChar);
  std::string carets(getNumLength(nearestNumIndex, equation), caretChar);
  std::cout << "****************" << '\n';
  std::cout << equation << '\n';
  std::cout << spaces << carets << '\n';
}

long double getNum(int startIndex, std::string equation) {
  std::string numStr = getNumStr(startIndex, equation);
  long double num = 0;
  num += getNumBeforeDecimalPoint(numStr);
  if (!(getNumAfterDecimalPoint(numStr) == -1)) {
    num += getNumAfterDecimalPoint(numStr);
  }

  if (numStr[0] == '-') {
    std::cout << "negative" << '\n';
    return num * -1;
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

  for (int i = 0; i < equation.length(); i++) {
    if (isFound(numbers, equation[i], 11) && !foundNum) {
      foundNum = true;
      if (foundNegative) {
        std::string numStr = getNumStr(i, equation);
        numStr.insert(numStr.begin(), '-');
        equationVec.push_back(numStr);
      } else {
        equationVec.push_back(getNumStr(i, equation));
      }
    } else if (!isFound(numbers, equation[i], 11) && foundNum) {
      foundNum = false;
    } else if (equation[i] == '-' && isFound(numbers, equation[i + 1], 11)) {

      foundNegative = true;
    } else if (isFound(operators, equation[i], 7) && !foundOp) {
      foundOp = true;
      foundNegative = false;
      foundNum = false;
    } else if (!isFound(operators, equation[i], 7) && foundOp) {
      foundOp = false;
    }
  }
}

// I've got an idea on how to do this
void Solver::solve() {}

bool Solver::checkEquationValidity() {
  bool foundOp = false;
  bool foundNegative = false;
  bool foundNum = false;
  bool foundOpB = false;
  bool foundNegativeB = false;
  bool foundNumB = false;
  char spaceChar = ' ';
  char caretChar = '^';
  std::string expecting = "number";

  for (int i = 0; i < equation.length(); ++i) {
    char currentChar = equation[i];
    if (currentChar == ' ') {
      continue;
    } else {
      if (expecting == "number") {
        if (isFound(numbers, currentChar, 11)) {
          expecting = "op";
          int numLength = getNumLength(i, equation);
          i += numLength - 1;
        } else if (currentChar == '-') {
          if (isFound(numbers, equation[i + 1], 11)) {
            continue;
          } else {
            PrintErrorBase(i, equation);
            std::cout << "math error: expected a number\n";
            break;
          }
        }
      } else {
        if (expecting == "op") {
          if (isFound(operators, currentChar, 7)) {
            expecting = "number";
          } else {
            PrintErrorBase(i, equation);
            std::cout << "math error: expected an operator\n";
            break;
          }
        }
      }
    }
  }
  return 0;
}
// if (i == 0) {
//       if (isFound(numbers, equation[i], 11) && !foundNum) {
//         std::cout << "Found a number at index " << i << '\n';
//         foundNumB = true;
//       }
//       if (isFound(operators, equation[i], 5)) {
//         if ((isFound(numbers, equation[i + 1], 11)) && equation[i] ==
//         '-')
//         {
//           std::cout << "Found negative number at index " << i << '\n';
//           foundNumB = true;
//           foundNegativeB = true;
//         } else {
//           PrintErrorBase(i, equation);
//           std::cout << "error: expected number before '" << equation[i]
//           <<
//           "'."
//                     << '\n';
//         }
//       }
// }

long double Solver::getTotal() { return total; }
