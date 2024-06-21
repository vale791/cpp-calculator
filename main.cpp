#include <cmath>
#include <iostream>

/*
  TODO: redesign and recode the whole number recognition system, and AFTER that add the operation sequence system.
*/

char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

template <typename T>
bool isFound(T* array, T value, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (array[i] == value)
        {
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

double getNum(int startIndex, std::string equation) {
  int numLength = 0;
  for (int i = startIndex; i < equation.length(); i++) {
    if (equation[i] != '(' && equation[i] != ')' && equation[i] != '*' &&
        equation[i] != '/' && equation[i] != '+' && equation[i] != '-' &&
        equation[i] != ' ') {
      numLength++;
    } else {
      break;
    }
  }

  std::string numStr = equation.substr(startIndex, startIndex + numLength);

  long double num = 0;
  num += getNumBeforeDecimalPoint(numStr);
  num += getNumAfterDecimalPoint(numStr);

  return num;
}

int main() {
  std::string equation;
  bool foundNum = false;
  long double total = 0;

  std::cout << "CALCULATOR\n";
  std::cout << "Enter your equation:\n";

  std::getline(std::cin, equation);
  
  return 0;
}
