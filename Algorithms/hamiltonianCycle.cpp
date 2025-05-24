#include<iostream>
#include<vector>

using namespace std;

struct HamiltonianData {
  int V;
  vector<vector<int>> graph;
  vector<bool> visited;
  vector<int> cycle;
  vector<vector<int>> allCycles;
};

void helper (HamiltonianData& data, int idx) {
  // Check within Graph Bounds
  if (idx < data.V) {
    // Try All Possible for NextNode in Cycle
    for (int i = 0;i<data.V;i++) {
      // If Node Already done or doesnt have edge with prev node donot add
      if (data.visited[i] || data.graph[data.cycle[idx-1] ][i] == 0) continue;
      
      data.cycle[idx] = i;
      data.visited[i] = true;

      helper(data, idx+1);

      // BackTrack
      data.visited[i] = false;
    }

  }
  // When Reached end Check if Last Node has Edge with First Node
  else if ( data.graph[ data.cycle[idx-1] ][ data.cycle[0] ] ) {
    // Check if this Cycle is not just Reverse of a Previous Cycle
    int i, j;
    bool same = false;

    for (vector<int>& c : data.allCycles) {
      i = 1; j = data.V-1;
      same = true;
      while (i < data.V) {
        if (data.cycle[i] != c[j]) {
          same = false;
          break;
        }

        i++; j--;
      }

      if (same) break;
    }


    // Add only if Unique Cycle
    if (!same) data.allCycles.push_back(vector<int>(data.cycle.begin(), data.cycle.end() ) );
  }

}

vector<vector<int>> HamiltonianCycle(vector<vector<int>>& graph) {
  const int V = graph.size();
  // Create arrays for Vistied and Cycle Path
  HamiltonianData data;
  data.V = V;
  data.graph = graph;
  data.cycle = vector<int>(V, -1);
  data.visited = vector<bool> (V, false);

  // Keeping the Source Node Fixed such that Rotations of a Cycle are not Considered
  data.visited[0] = true;
  data.cycle[0] = 0;

  helper(data, 1);

  return data.allCycles;
}

void PrintVector(const vector<int>& vec) {
  for (int i = 0;i<vec.size();++i) {
    cout<< vec[i] <<", ";
  }
  cout<<endl;
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

  vector<vector<int>> cycles = HamiltonianCycle(graph);

  cout<<"Number of Cycles : "<< cycles.size() <<endl;
  cout<<"Cycles : "<<endl;
  for (const vector<int>& v : cycles) {
    PrintVector(v);
  }


  return 0;
}