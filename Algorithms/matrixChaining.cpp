#include<iostream>
#include<vector>

using namespace std;
typedef unsigned int uint;

void PrintMatrix(const vector<vector<uint>>& mat) {
  for (const vector<uint>& row : mat) {
    for (const uint& x : row) {
      cout << x <<", ";
    }
    cout << endl;
  }
}

void GetMatMulOrder(const vector<vector<uint>>& orderDPMat, int i, int j, vector<int>& order) {
  if (i < j) {
    int k = orderDPMat[i][j];
    GetMatMulOrder(orderDPMat, i, k, order);
    GetMatMulOrder(orderDPMat, k+1, j, order);

    order.push_back(k);
  }

}

struct MatChainAns {
  uint totalCost;
  vector<int> order;

  MatChainAns(uint c = 0, vector<int> order = {}) : totalCost(c), order(order) {}
};

MatChainAns MatrixChain(const vector<uint>& dimensions) {
  const uint N = dimensions.size()-1;
  // Create a DP Cost Matrix 
  vector<vector<uint>> cost(N, vector<uint>(N));
  vector<vector<uint>> order(N, vector<uint>(N));

  uint minCost, c;
  
  // Loop for Diagonals
  for (int diff = 1;diff<N;diff++) {
    // Rows
    for (int i = 0;i<N-diff;i++) {
      int j = i+diff;
      minCost = INT_MAX;
      
      // Checking All Combinations for Mat Mul for Mat i to Mat j
      for (int k = i;k<j;k++) {
        c = cost[i][k] + cost[k+1][j] + dimensions[i] * dimensions[k+1] * dimensions[j+1];
        if (c < minCost) {
          minCost = c;
          order[i][j] = k;
        }
      }

      cost[i][j] = minCost;
    }
  }

  cout<<"Cost Matrix : "<<endl;
  PrintMatrix(cost);

  cout<<"Order Matrix : "<<endl;
  PrintMatrix(order);

  vector<int> precendence;
  GetMatMulOrder(order, 0, N-1, precendence);

  return {cost[0][N-1], precendence};
}

int main () {
  vector<uint> dimensions = {10, 2, 5, 12, 6};

  MatChainAns ans = MatrixChain(dimensions);

  cout<<"Min Multiplications : "<< ans.totalCost <<endl;
  cout<<"Order of Multiplication : "<<endl;
  for (const int& x : ans.order) {
    cout<< x <<", ";
  }
  cout<<endl;

  return 0;
}