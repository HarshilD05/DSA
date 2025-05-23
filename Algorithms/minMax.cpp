#include<iostream>
#include<vector>
#include<utility>
#include<chrono>

using namespace std;

// Time Based Seed for RNG
void seed_random() {
  srand(time(NULL));
}

vector<int> random_number_generator(size_t n) {
  vector<int> arr(n);
  for (size_t i = 0; i < n; i++) {    
    arr[i] = rand();
  }
  return arr;
}

// Print Array
void print_vector(const vector<int> &arr) {
  size_t n = arr.size();
  for (size_t i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

pair<int, int> newMinMax(const vector<int> &arr, int low, int high) {
  // Base Conditions
  if (high - low <= 1) {
    return (arr[low]  < arr[high]) ? make_pair(arr[low], arr[high]) : make_pair(arr[high], arr[low]) ;
  }
  
  // Recursions
  int mid = low + (high - low) / 2;
  pair<int, int> left = newMinMax(arr, low, mid);
  pair<int, int> right = newMinMax(arr, mid+1, high);

  // Compare and Return
  // Get Min Val from both Subtrees
  left.first = (left.first < right.first) ? left.first : right.first;
  // Get MaxVal from Both SubTrees
  left.second = (left.second > right.second) ? left.second : right.second;

  return left;
}

pair<int, int> naiveMinMax(const vector<int>& arr) {
  int minVal = INT_MAX;
  int maxVal = INT_MIN;

  for (const int& x : arr) {
    if (x < minVal) minVal = x;
    if (x > maxVal) maxVal = x;
  }

  return {minVal, maxVal};
}

int main () {
  seed_random();
  int n = 1000000;
  vector<int> arr = random_number_generator(n);

  cout<<"Array Size : "<< n <<endl;

  auto start = chrono::high_resolution_clock::now();
  pair<int, int> minMaxPair = naiveMinMax(arr);
  auto end = chrono::high_resolution_clock::now();

  cout<<"Naive Min Max Algo : "<< endl;
  cout << "Min: " << minMaxPair.first << " Max: " << minMaxPair.second <<endl;
  cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() <<" microseconds"<< endl;

  start = chrono::high_resolution_clock::now();
  minMaxPair = newMinMax(arr, 0, n-1);
  end = chrono::high_resolution_clock::now();

  cout<<"New Min Max Algo : "<< endl;
  cout << "Min: " << minMaxPair.first << " Max: " << minMaxPair.second <<endl;
  cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() <<" microsecond "<<endl;
  
  return 0;
}