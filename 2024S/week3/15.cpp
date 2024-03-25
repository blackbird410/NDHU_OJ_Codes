#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#define BINSIZE 16

#define OPCODE_R "000000"
#define OPCODE_J "001000"
#define FUNCT_ADD "100000"
#define FUNCT_SUB "100010"
#define FUNCT_OR "100101"
#define FUNCT_AND "100100"
#define SHAMNT "00000"
#define T0 "01000"
#define T1 "01001"
#define T2 "01010"
#define T3 "01011"
#define T4 "01100"
#define T5 "01101"
#define T6 "01110"
#define T7 "01111"

string convertToDifferentBase(int dec, int base); 

class Instruction {
  string command;
  string params[3];
  string assemblyCode;
public:
  Instruction() : command("") {};
  Instruction(string s) { 
    getParams(s); 
    convertToAssembly();
  };

  string getAssemblyCode() {return assemblyCode;};

  void convertToAssembly() {
    enum Cmd {ADDI = 0, ADD = 1, SUB = 2, OR = 3, AND = 4, NONE = 5};
    Cmd c;
    if (command == "addi") c = ADDI;
    else if (command == "add") c = ADD;
    else if (command == "sub") c = SUB;
    else if (command == "or") c = OR;
    else if (command == "and") c = AND;
    else c = NONE;

    switch (c) {
      case ADDI:
        assemblyCode = OPCODE_J + params[1] + params[0] + params[2];
        break;
      case ADD:
      case SUB:
      case OR:
      case AND:
        assemblyCode = OPCODE_R + params[1] + params[2] + params[0] + SHAMNT;
        if (c == ADD) assemblyCode += FUNCT_ADD;
        else if (c == SUB) assemblyCode += FUNCT_SUB;
        else if (c == OR) assemblyCode += FUNCT_OR;
        else assemblyCode += FUNCT_AND;
        break;
      default:
        assemblyCode = "WRONG FORMAT";
        break;
    }
  }

  void getParams(string s) {
    int i;
    char str[50];
    for (i = 0; i < s.length(); i++) str[i] = s[i];
    str[i] = '\0';
    
    command = strtok(str, " ");
    char *token = strtok(NULL, ", ");

    i = -1;
    while (token != NULL) {
      params[++i] = convert(token);
      token = strtok(NULL, ", ");
    }
  }

  string convert(string t) {
    int v = (t[0] == '$') ? t[2] - '0' : -1;

    switch (v) {
      case 0:
        return T0;
      case 1:
        return T1;
      case 2:
        return T2;
      case 3:
        return T3;
      case 4:
        return T4;
      case 5:
        return T5;
      case 6:
        return T6;
      case 7:
        return T7;
      default:
        t = convertToDifferentBase(stoi(t), 2);
        int l = t.length();
        int i = -1;
        while(++i < 16 - l) t = "0" + t; 
        return t;
    }
  }
};

typedef struct Case {
  string instruction;
  string assemblyCode;
} Case;

int test() {
  int n, i;
  int failed = 0;

  Case cases[10];
  cout << "N cases: ";
  cin >> n;
  n = (n > 10) ? 10 : n;
  while (!getchar());
  
  for (i = 0; i < n; i++) {
    getline(cin, cases[i].instruction);
    cin >> cases[i].assemblyCode; 
    while (!getchar());
  }

  cout << "\nTesting..." << endl;
  for (i = 0; i < n; i++) {
    Instruction p(cases[i].instruction);
    if (p.getAssemblyCode() != cases[i].assemblyCode) {
      failed++;
      cout << "Case " << i + 1 << " failed" << endl;
      cout << "Instruction: " << cases[i].instruction << endl;
      cout << p.getAssemblyCode() << " != " << cases[i].assemblyCode << endl;
      cout << endl;
    }
  }

  return failed;
}

int main () {
  string cmd; 

  while(getline(cin, cmd) && cmd != "") {
    Instruction i(cmd);
    cout << i.getAssemblyCode() << endl;
  }

  //int failed = test();
  //if (!failed) cout << "All test passed." << endl;
  //else if (failed == 1) cout << "1 test failed." << endl;
  //else cout << failed << "tests failed." << endl;

  return 0;
}

string convertToDifferentBase(int dec, int base) 
{
  string result = "";
  if (!(dec / base))
  {
    if (dec < 0) result = '-';
    
    result += (abs(dec % base) > 9) 
          ? to_string(abs(dec % base)) 
          : to_string(abs(dec % base));
    return result; 
  }    
  
  result = convertToDifferentBase(dec / base, base);
  string digit = (abs(dec % base) > 9) ? to_string(abs(dec % base)): to_string(abs(dec % base));
  result += digit;
  
  return result;
}

