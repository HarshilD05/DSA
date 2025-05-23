#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct SubsetSumData {
  vector<int> remSum;
  vector<int> subset;
  vector<vector<int>> ans;
};

void helper(const vector<int>& arr, int idx, int& target, SubsetSumData& data) {
  // cout<<"\n\nIdx : "<< idx <<endl;
  
  if (idx < arr.size() ) {
    // When Not Including the Current Number
    if (target <= data.remSum[idx] ) {
      helper(arr, idx+1, target, data);      
    }

    
    // When Including Current Number
    target -= arr[idx];
    data.subset.push_back(arr[idx]);

    if (target == 0) {
      data.ans.push_back(vector<int>(data.subset.begin(), data.subset.end() ) );
    }
    else if (target > 0) {      
      helper(arr, idx+1, target, data);
    }

    // Backtrack
    target += arr[idx];
    data.subset.pop_back();
  }
  
}

vector<vector<int>> subsetSum(const vector<int>arr, const int target) {
  int n = arr.size();
  // First Sort the Array
  vector<int> arrCpy(arr.begin(), arr.end() );
  sort(arrCpy.begin(), arrCpy.end() );

  // Printing the Sorted Array 
  cout<<"\nNumbers List : "<<endl;
  for (int x : arrCpy) {
    cout<< x <<" ";
  }
  cout<<endl;
  
  // PostFix ArrSum
  vector<int> postSum(n);
  for (int i = n-2;i>=0;i--) {
    postSum[i] = postSum[i+1] + arrCpy[i+1];
  }

  int tSum = target;

  SubsetSumData d;
  d.remSum = postSum;

  helper(arrCpy, 0, tSum, d);

  return d.ans;  
}


int main () {
  vector<int> arr = {1, 5, 3, 9, 10, 2, 4};
  int target = 14;

  cout<<"Target : "<< target <<endl;

  vector<vector<int>> ans = subsetSum(arr, target);

  for (auto v : ans) {
    for (auto& x : v ) {
      cout<< x <<" ";
    }
    cout<<endl;
  }

  return 0;
}