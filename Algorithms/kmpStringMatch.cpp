#include<iostream>
#include<vector>

using namespace std;

vector<int> generateLPS(string s) {
  vector<int> lps(s.length() );
  int idx = 0;
  for (int i = 1;i<s.length();++i) {
    while (idx > 0 && s[idx] != s[i]) {
      idx = lps[idx-1];
    }
    if (s[i] == s[idx]) idx++;
    lps[i] = idx;
  }

  return lps;
}

// Knuth Morris Pratt
vector<int> KMPMatch(string s1, string s2) {
  int l1 = s1.length();
  int l2 = s2.length();
  if (l1  < l2) return {};

  // Get the LPS Array
  vector<int> pattern = generateLPS(s2);
  cout<<"LPS Pattern : "<<endl;
  for (int& x : pattern) {  
    cout<< x <<" ";
  }
  cout<<endl;

  // Find Match in S1
  int idx = 0;
  vector<int> ans;
  for (int i = 0;i<l1;++i) {
    while (idx > 0 && s1[i] != s2[idx]) {
      idx = pattern[idx-1];
    }
    
    if (s1[i] == s2[idx]) {
      idx++;
      if (idx == l2) ans.push_back(i - l2 + 1);
    }

  }
  
  return ans;
}

int main () {
  string s1 = "babacdbbacbabdcdbacbscdbacbbacbdcbacbdcabdebna";
  string s2 = "abcaba";
  vector<int> matches = KMPMatch(s1, s2);

  cout << "String 1: " << s1 << endl;
  cout << "String 2: " << s2 << endl;
  cout << "Match Idx: "<< endl;
  for (int& x : matches) {  
    cout<< x <<" ";
  }
  cout<<endl;

  return 0;
}