#include<iostream>
#include<vector>
using namespace std;

bool isSafe(const vector<int>& queens, int r, int c) {
  // Row will by default be safe since Placing each queen on Different row
  // Check Column
  for (int i = 0;i<queens.size();++i) {
    if (queens[i] == c) return false;
  }

  // Check Diagonals using the Row and Column difference
  int rowDiff, colDiff;  
  for (int i = 0;i<queens.size();++i) {
    if (queens[i] != -1) {
      rowDiff = abs(r - i);
      colDiff = abs(c - queens[i]);
      if (rowDiff == colDiff) return false;
    }
  }

  return true;
}

void nQueensHelper(vector<int>& queens, const int n, int r, vector<vector<int>>& ans) {
  if (r < n) {
    for (int i = 0;i<n;++i) {
      if (isSafe(queens, r, i) ) {
        queens[r] = i;
        nQueensHelper(queens, n, r+1, ans);
      }
    }
    queens[r] = -1;    
  }
  // If End of Board Reached and Placed all Queens
  else {
    ans.push_back(vector<int>(queens.begin(), queens.end() ) );
  }
}

vector<vector<int>> nQueens(const int n) {
  vector<vector<int>> ans;
  vector<int> queenPos(n, -1);
  nQueensHelper(queenPos, n, 0, ans);

  return ans;
}

int main () {
  int n = 4;
  vector<vector<int>> ans = nQueens(n);
  cout<<"Possible Answers for "<< n <<" x "<< n <<" : "<< ans.size() <<endl;

  for (auto v : ans) {
    for (auto x : v) {
      cout<< x <<" ";
    }
    cout<<endl;
    
  }
  
  return 0;
}
