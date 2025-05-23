#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& str, char delimiter) {
  vector<string> tokens;
  string token;
  for (char c : str) {
    if (c == delimiter) {
      if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
    } else {
      token += c;
    }
  }
  if (!token.empty()) {
    tokens.push_back(token);
  }
  return tokens;
}

string Strip(const string& str) {
  size_t start = str.find_first_not_of(" \t\n\r");
  if (start == string::npos) return "";
  size_t end = str.find_last_not_of(" \t\n\r");
  return str.substr(start, end - start + 1);
}

double postfixEval(string exp) {
  stack<double> s;

  vector<string> tokens = split(exp, ',');
  
  for (string &t : tokens) {
    t = Strip(t);

    if (isdigit(t[0])) {
      s.push( stod(t) );
    } else {
      double b = s.top(); s.pop();
      double a = s.top(); s.pop();
      switch (t[0]) {
        case '+': s.push(a + b); break;
        case '-': s.push(a - b); break;
        case '*': s.push(a * b); break;
        case '/': s.push(a / b); break;
      }
    }
  }
  return s.top();
}

int main () {
  string exp= "35, 25, 2, +, -";
  cout<<"Expression : "<< exp;  
  double ans = postfixEval(exp);
  cout<<"\n Ans : "<< ans <<endl;

  return 0;
}
