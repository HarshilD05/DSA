#include<iostream>
#include<vector>

using namespace std;

void PrintVector(const vector<int>& vec) {
  for (int i = 0;i<vec.size();++i) {
    cout<< vec[i] <<", ";
  }
  cout<<endl;
}

struct GraphColoringData {
  int V;
  vector<vector<int>> graph;
  int nColors;
  bool solved;
  vector<int> colors;

  GraphColoringData() : V(0), graph({}), nColors(1), solved(false), colors({}) {}
};

void helper(GraphColoringData& data, int idx) {
  // Check Within Bounds
  if (idx < data.V) {
    // Try All Colors for current Node
    for (int i = 1;i <= data.nColors;++i) {
      // Check if Color Doesnt Clash with Adjacent Edges
      bool clash = false;
      for (int j = 0;j<data.V;j++) {
        if (data.graph[idx][j] != 0 && data.colors[j] == i) {
          clash = true;
          break;
        }
      }

      // If No Clashes move to next Node
      if (!clash) {
        data.colors[idx] = i;
        helper(data, idx+1);
      }

      // Continue Coloring only if not solved
      if (data.solved) break;
    }

    // BackTrack only if not solved
    if (!data.solved) {
      data.colors[idx] = 0;
    }

  }
  else {
    data.solved = true;
  }
}

struct GraphColoringAns {
  int nColors;
  vector<int> colors;
};

GraphColoringAns GraphColoring(const vector<vector<int>>& graph) {
  GraphColoringData data;
  data.graph = graph;
  data.V = graph.size();
  // Initially All Vertex Uncolored (0)
  data.colors = vector<int>(data.V);
  // Let Initial Node be colored first color if node present
  if (data.V) {
    data.colors[0] = 1;
  }

  // Base Case of 1 or 0 vertex
  if (data.V <= 1) {
    return {data.nColors, data.colors};
  }

  // Minimum 2 colors needed to color graph with multiple nodes 
  data.nColors = 2;

  while (!data.solved) {
    // If given Colors are not enough then increment number of colors
    data.nColors++;
    // Start with 2nd node since first Node already Colored
    helper(data, 1);
  }

  return {data.nColors, data.colors};
}

int main () {
  vector<vector<int>> graph = {
    {0, 4, 0, 0, 0, 5},
    {4, 0, 9, 0, 7, 11},
    {0, 9, 0, 2, 13, 0},
    {0, 0, 2, 0, 6, 0},
    {0, 7, 13, 6, 0, 3},
    {5, 11, 0, 0, 3, 0}
  };

  GraphColoringAns ans = GraphColoring(graph);

  cout<<"Min Number of Colors needed : "<< ans.nColors <<endl;
  cout<<"Coloring : "<<endl;
  PrintVector(ans.colors);


  return 0;
}