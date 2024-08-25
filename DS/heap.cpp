#include<iostream>
#include<vector>
#include<cmath>
#include<stdexcept>
#include<functional>
typedef unsigned int uint;

enum HEAP_TYPE {
  MIN_HEAP,
  HEAP,
  MAX_HEAP
};

template <typename T>
class Heap {
  T* heapPtr;
  size_t _size;
  size_t _capacity;
  HEAP_TYPE _type;

  void expandHeap();
  void heapify();

  public : 
  Heap(HEAP_TYPE hpType = HEAP_TYPE::HEAP) {
    this->_type = hpType;
    this->_size = 0;
    this->_capacity = 1;
    this->heapPtr = new T[_capacity];
  }

  Heap (std::vector<T> v, HEAP_TYPE hpType = HEAP_TYPE::HEAP) {
    this->_type = hpType;
    uint level = (uint) ceil(log2(v.size()+1));
    this->_size = 0;
    this->_capacity = (size_t) pow(2, level)-1;
    this->heapPtr = new T[this->_capacity];

    for (T x : v) this->insert(x);
  }

  // Deconstructor
  ~Heap() {
    delete[] this->heapPtr;
  }

  void insert(T val);
  T pop();
  void printHeap() const;
  size_t size() { return this->_size; }
  size_t capacity() { return this->_capacity; }
  bool isEmpty() { return this->_size == 0; }
  T& operator[] (size_t idx);
};

template<typename T>
void Heap<T>::expandHeap() {
  uint currLevel = (uint)(this->_size+1);
  size_t newCap = (size_t)pow(2,currLevel+1)-1;
  // Copying Items to the new Array
  T* temp = new T[newCap];
  for (size_t i = 0;i<this->_size;++i) {
    temp[i] = this->heapPtr[i];
  }
  // Deleting Previous Mem Allocation
  delete[] heapPtr;
  // Updating Mem Pointer
  this->heapPtr = temp;
  // Updating Capacity
  this->_capacity = newCap;
}

template<typename T>
void Heap<T>::insert(T val) {
  if (this->_size == this->_capacity) this->expandHeap();
  size_t idx = this->_size;
  this->heapPtr[idx] = val;
  this->_size++;

  if (this->_size == 1 || this->_type == HEAP) return;
  // Choosign the comparison operator based on Heap Type
  std::function<bool(T, T)> compare;
  if (this->_type == MIN_HEAP) compare = std::less<T>();
  else compare = std::greater<T>();

  while (idx > 0) {
    size_t rootIdx = (idx-1)/2;
    // Compare with the root value
    if (compare(heapPtr[idx], heapPtr[rootIdx]) ) {
      std::swap(heapPtr[idx], heapPtr[rootIdx] );
      idx = rootIdx;
    }
    else break;
  }

}

template<typename T>
void Heap<T>::heapify() {
  if (this->_size < 2 || this->_type == HEAP) return;
  // Deciding the Compare fn based on Heap type
  std::function<bool(T, T)> compare;
  if (this->_type == MIN_HEAP) compare = std::less<T>();
  else compare = std::greater<T>();

  size_t idx = 0;

  while (idx < this->_size/2) {
    size_t leftChildIdx = 2*idx+1;
    size_t rightChildIdx = 2*idx+2;
    size_t j;

    // Check if LeftChild within heapBounds
    if (leftChildIdx >= this->_size) break;
    // Check if RightChild within Heap Bounds
    if (rightChildIdx >= this->_size) {
      j = leftChildIdx;
    }
    else {
      j = (compare(this->heapPtr[leftChildIdx], this->heapPtr[rightChildIdx]) )? leftChildIdx : rightChildIdx ;
    }

    if (compare(this->heapPtr[j], this->heapPtr[idx]) ) {
      std::swap(this->heapPtr[j], this->heapPtr[idx]);
    }
    
    idx++;
  }

}

template<typename T>
T Heap<T>::pop() {
  if (this->isEmpty() ) throw(std::out_of_range("\n Cannot Pop from an Empty Heap... \n") );
  // Getting the last Element on Top
  std::swap(this->heapPtr[0], this->heapPtr[this->_size-1]);
  this->_size--;
  // Heapify to maintain a MIN / MAX HEAP
  this->heapify();

  return this->heapPtr[this->_size];
}

template<typename T>
T& Heap<T>::operator[] (size_t idx) {
  if (idx < this->_size) return this->heapPtr[idx];
  else {
    throw std::out_of_range("\n Index [" + std::to_string(idx) +"] out of range when Size : " + std::to_string(this->_size) + "\n" );
  }
}

template<typename T>
void Heap<T>::printHeap() const {
  std::cout<<"\n";
  for (size_t i = 0;i<this->_size;++i) {
    std::cout<< this->heapPtr[i] <<",";
  }
  std::cout<<"\n";
}


int main (int argc, char* argv[]) {
  Heap<int> hp({3,1,4,2,5,6,0},  MAX_HEAP);
  hp.printHeap();
  hp.pop();
  hp.printHeap();
  return 0;
}