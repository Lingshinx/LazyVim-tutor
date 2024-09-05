#ifndef _All_HPP_
#define _All_HPP_

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>

class BrainFupiler {
private:
  static const int SIZE = 27;
  static BrainFupiler *compiler;
  char array[SIZE]{};
  char *p = array;
  char jumpCount{};

  enum state { leap, back, push, pop, keep };

  state oper(char);
  BrainFupiler() { p = array; };

public:
  static BrainFupiler &getInstance();
  const char validOperators[10]{'+', '-', '>', '<',  '[',
                                ']', ',', '.', '\n', ' '};

  bool isValid(char);
  bool isValid(std::string);
  void read(std::string);
  void read(std::istream &);
  void show();
  void set();
  char operator[](char index) { return array[index]; };
};

#endif // !_All_HPP_
/*#include "BrainFupiler.h"*/
#include <iosfwd>
#include <string>

BrainFupiler *BrainFupiler::compiler = new BrainFupiler();
BrainFupiler &BrainFupiler::getInstance() { return *compiler; }
bool BrainFupiler::isValid(char operater) {
  for (char c : validOperators) {
    if (c == operater) {
      return true;
    }
  }
  return false;
}

bool BrainFupiler::isValid(std::string opers) {
  int count{};
  for (char c : opers) {
    if (isValid(c)) {
      if (c == '[')
        count++;
      else if (c == ']')
        count--;
    } else {
      return false;
    }
  }
  return count == 0;
}

BrainFupiler::state BrainFupiler::oper(char operater) {
  switch (operater) {
  case '[':
    return (*p == 0) ? leap : push;
  case ']':
    return (*p == 0) ? pop : back;
  }

  switch (operater) {
  case '+':
    (*p)++;
    break;
  case '-':
    (*p)--;
    break;
  case '<':
    if (p == array)
      break;
    p--;
    break;
  case '>':
    if (p == array + SIZE - 1)
      break;
    p++;
    break;
  case ',':
    std::cin.get(*p);
    break;
  case '.':
    std::cout.put(*p);
    break;
  }
  return keep;
}

void BrainFupiler::read(std::string input) {
  if (!isValid(input)) {
    return;
  }
  using namespace std;
  auto index = input.begin();
  stack<string::iterator> marks;
  int jumpCount;
  while (index != input.end()) {
    switch (oper(*index)) {
    case push:
      marks.push(index);
      break;
    case pop:
      marks.pop();
      break;
    case leap:
      for (jumpCount = 1; index != input.end() - 1; index++) {
        if (*index == '[') {
          jumpCount++;
        } else if (*index == ']') {
          jumpCount--;
        } else if (jumpCount == 0) {
          break;
        }
      }
      break;
    case back:
      index = marks.top();
      break;
    case keep:
      break;
    }
    index++;
  }
}

void BrainFupiler::read(std::istream &in) {
  using namespace std;
  stack<streampos> marks;
  int jumpCount;
  while (!in.eof()) {
    char c = in.get();
    switch (oper(c)) {
    case push:
      marks.push(in.tellg());
      break;
    case pop:
      marks.pop();
      break;
    case leap:
      for (jumpCount = 1; !in.eof(); in.get(c)) {
        if (c == '[') {
          jumpCount++;
        } else if (c == ']') {
          jumpCount--;
        } else if (jumpCount == 0) {
          break;
        }
      }
      break;
    case back:
      in.seekg(marks.top());
      break;
    case keep:
      break;
    }
  }
}

void BrainFupiler::show() {
  using namespace std;
  for (char *it = array; it != array + SIZE; it++) {
    if (it == p) {
      cout << "\033[32m\033[1m\033[4m" << int(*it) << "\033[0m";
    } else {
      cout << int(*it);
    }
    cout << ' ';
  }
  cout << endl << "\033[K\033[3mpointer: \033[38m" << *p << "\033[0m";
}

void BrainFupiler::set() { p = array; }

// 你找到了呀, 来, 把光标放在头文件上面, 然后按`gcc`来注释掉它
// 之后输入命令`:!gcc % -o BF`
// 打开终端, 运行 ./BF, 这是我大一下学期时做的小玩意
// 具体玩法的话要去B站找 BrainF**k 教程

/*#include "BrainFupiler.h"*/
#include <cstdlib>
#include <fstream>
#include <string>

char array[255];

int main(int argCount, char *argValue[]) {
  std::ofstream fout;
  std::ifstream fin;
  if (argCount == 1) {
    using namespace std;
    string x;
    BrainFupiler compiler = BrainFupiler::getInstance();
    compiler.set();
    cout << "\033[2J";
    cout << "\033[3H===================\033[10;8H\033[1m---<\033[33mBrainF**k "
            "\033[34mMade by "
            "\033[32mLingshin\033[0m>---";
    cout << "\033[7H\033[K\033[3moutput: \033[0m\033[s";
    do {
      cout << "\033[H\033[K";
      compiler.show();
      cout << "\033[5H\033[K\033[3moperation: \033[31m";
      cin >> x;
      cin.get();
      cout << "\033[u\033[35m";
      compiler.read(x);
      cout << "\033[s\033[0m";
    } while (!x.empty());
  } else if (argCount > 2) {
    std::cout << "too many arguments" << std::endl;
    return 1;
  } else {
    fin.open(argValue[1]);
    if (fin.good()) {
      BrainFupiler &compiler = BrainFupiler::getInstance();
      compiler.read(fin);
      return 0;
    } else {
      std::cout << "No such file exists" << std::endl;
      return 1;
    }
  }
  return 0;
}
