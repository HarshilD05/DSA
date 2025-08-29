#include<iostream>
#include<vector>
#include<random>
// #include<bitset>
#include<algorithm>

using namespace std;

constexpr size_t SEED = 12345;
mt19937 generator(SEED);


int rng(int start, int end) {
  uniform_int_distribution<int> rng(start, end);
  return rng(generator);
}


void printVec(const vector<int>& arr ) {
  cout << "\n[";
  for (size_t i = 0; i < arr.size(); i++) {
    cout << arr[i] << ", ";
  }
  cout << "]\n";
}


vector<int> generateRandomArray(size_t N) {
  // geenrates N arrays of Size K
  vector<int> arr(N);
  for (size_t i = 0; i < N; i++) {
    arr[i] = rng(-10000, 100);
  }

  return arr;
}

typedef struct MyInt {
  bool neg;
  unsigned int val;

  MyInt(int num = 0) {
    val = num & 0x7FFFFFFF;
    // check if the negative bit (MSB) is set
    if (num & 0x80000000) {
      neg = true;
      val = ~val;
    }
    else {
      neg = false;
    }
  }

} MyInt;

int toInt(MyInt i) {
  int val = i.val;
  if (i.neg) {
    val = ~val;
    val |= 0x80000000;
  }

  return val;
}

void radixSort(vector<int>& arr) {
  // Convert to a Vector of custom Int data Types
  const size_t N = arr.size();
  vector<MyInt> vec(N);
  for (size_t i = 0; i < N; i++) {
    vec[i] = MyInt(arr[i]);
  }

  // Create 2 Buckets for 0 and 1
  vector<MyInt>* old_b0 = new vector<MyInt>();
  vector<MyInt>* old_b1 = new vector<MyInt>();

  // Create 2 Other Buckets for next Itt
  vector<MyInt>* b0 = new vector<MyInt>();
  vector<MyInt>* b1 = new vector<MyInt>();

  // Initially resize All Buckets to N/2
  old_b0->reserve(N / 2);
  old_b1->reserve(N / 2);
  b0->reserve(N / 2);
  b1->reserve(N / 2);

  // Initial assignement baesd on LSB
  for (MyInt& x : vec) {
    // Check ith bit of the Value
    if ( x.val & 1 ) {
      b1->push_back(x);
    }
    else {
      b0->push_back(x);
    }
  }

  for (int idx = 1; idx < sizeof(int) * 8; idx++) {
    // Swap the Buckets by swapping pointers
    swap(old_b0, b0);
    swap(old_b1, b1);

    // Clear the Buckets for this itt
    b0->clear();
    b1->clear();

    // Itterate Over Elements of OldB0
    MyInt x;
    for (size_t i = 0; i < old_b0->size(); i++) {
      x = old_b0->at(i);
      if (x.val & (1 << idx) ) {
        b1->push_back(x);
      }
      else {
        b0->push_back(x);
      }
    }

    // Itterate over old_b1 Elements
    for (size_t i = 0; i < old_b1->size(); i++) {
      x = old_b1->at(i);
      if (x.val & (1 << idx) ) {
        b1->push_back(x);
      }
      else {
        b0->push_back(x);
      }
    }

  }

  // Clear old_buckets for the final Sort
  old_b0->clear();
  old_b1->clear();

  // Finally Put all Negatives in b1 and all positives in b0
  // Itterate Over b0 Elements
  MyInt x;
  for (size_t i = 0; i < b0->size(); i++) {
    x = b0->at(i);
    // Check ith bit of the Value
    if ( x.neg ) {
      old_b1->push_back(x);
    }
    else {
      old_b0->push_back(x);
    }
  }

  // Itterate Over b1 Elements
  for (size_t i = 0; i < b1->size(); i++) {
    x = b1->at(i);
    // Check ith bit of the Value
    if ( x.neg ) {
      old_b1->push_back(x);
    }
    else {
      old_b0->push_back(x);
    }
  }



  // Form Final array of Integers by merging [old_b1, old_b0]
  for (size_t i = 0; i < old_b1->size(); i++) {
    x = old_b1->at(i);
    arr[i] = toInt(x);
  }

  reverse(arr.begin(), arr.begin() + old_b1->size() );

  size_t offset = old_b1->size();
  for (size_t i = 0; i < old_b0->size(); i++) {
    x = old_b0->at(i);
    arr[offset + i] = toInt(x);
  }

}

int main () {
  const int N = 1;
  const int K = 10;

  vector<int> arr = generateRandomArray(K);

  printVec(arr);
  radixSort(arr);
  printVec(arr);


  return 0;
}