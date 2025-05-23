#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printMatrix(vector<vector<int> > matrix) {
  for (int i = 0;i<matrix.size();++i) {
    for (int j = 0;j<matrix[0].size();++j) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

string lcs(string s1, string s2) {
  // Initialise the 2d Matrix
  const int l1 = s1.length();
  const int l2 = s2.length();
  vector<vector<int> > matrix(l2+1, vector<int>(l1+1) );

  for (int i = 0;i<l2;++i) {
    for (int j = 0;j<l1;++j) {
      if (s1[j] == s2[i]) {
        matrix[i+1][j+1] = matrix[i][j] + 1;
      }
      else {
        matrix[i+1][j+1] = max(matrix[i][j+1], matrix[i+1][j]);
      }
    }
  }

  printMatrix(matrix);

  // Finding the LCS
  string lcs = "";
  int i = l2, j = l1;
  while (i > 0 && j > 0) {
    if (s1[j-1] == s2[i-1]) {
      lcs.push_back(s1[i-1]);
      i--; j--;
    }
    else if (matrix[i-1][j] > matrix[i][j-1]) {
      i--;
    }
    else j--;
  }

  // Reverse the string
  reverse(lcs.begin(), lcs.end());

  return lcs;
}

int main () {
  string s1 = "ABCD";
  string s2 = "ACBD";

  cout << "String 1: " << s1 << endl;
  cout << "String 2: " << s2 << endl;
  cout << "LCS: \n" << lcs(s1, s2) << endl;
  
  return 0;
}