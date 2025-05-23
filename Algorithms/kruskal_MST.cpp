#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<climits>

using namespace std;

struct Edge {
  int src;
  int dest;
  int weight;

  Edge (): src(0), dest(0), weight(0) {}
  Edge (int s, int d, int w): src(s), dest(d), weight(w) {}
};

void PrintGraph(const vector<vector<int>>& graph) {
  int n = graph.size();
  cout<<"Graph : "<<endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << graph[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void PrintEdge(const Edge& e) {
  cout<<"["<< e.src <<" -> "<< e.dest <<" : "<< e.weight <<" ]"<<endl;
}

vector<Edge> getUndirectedGraphEdges(const vector<vector<int>>& graph) {
  int n = graph.size();
  vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (graph[i][j] != 0) {
        edges.push_back(Edge(i, j, graph[i][j]) );
      }
    }
  }

  return edges;
}

struct MST_Data {
  int totalCost;
  vector<Edge> mstEdges;
};

MST_Data kruskalMinSpanTree(const vector<vector<int>>& graph) {
  const int NVertex = graph.size();

  // Sort all the Graph Edges Based on their Weight
  vector<Edge> edges = getUndirectedGraphEdges(graph);
  sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {return e1.weight < e2.weight;} );

  // Maintain a Set No to track merged nodes and avoid cycles
  vector<int> setNo(NVertex);
  for (int i = 0;i<NVertex;++i) {
    setNo[i] = i;
  }
  
  vector<Edge> ans;
  int totalCost = 0;
  
  for (Edge e : edges) {
    // Check if the Source and Destination are not in same Set
    if (setNo[e.src] != setNo[e.dest]) {
      // Merge their Sets
      int oldSet = setNo[e.dest];
      for (int& x : setNo) {
        if (x == oldSet) x = setNo[e.src];
      }

      // Add edge to Ans
      ans.push_back(e);
      totalCost += e.weight;
    }
  }

  return {totalCost, ans};
}

int main () {
  
  vector<vector<int>> graph = {
    {0, 4, 0, 0, 0, 0, 0, 8, 0},  // 0
    {4, 0, 8, 0, 0, 0, 0, 11, 0}, // 1
    {0, 8, 0, 7, 0, 4, 0, 0, 2},  // 2
    {0, 0, 7, 0, 9, 14, 0, 0, 0}, // 3
    {0, 0, 0, 9, 0, 10, 0, 0, 0}, // 4
    {0, 0, 4, 14, 10, 0, 2, 0, 0},// 5
    {0, 0, 0, 0, 0, 2, 0, 1, 6},  // 6
    {8, 11, 0, 0, 0, 0, 1, 0, 7}, // 7
    {0, 0, 2, 0, 0, 0, 6, 7, 0}   // 8
  };
  
  MST_Data kmst = kruskalMinSpanTree(graph);
  cout<<"\n MST Cost : "<< kmst.totalCost <<endl;
  cout<<"\n Edges : "<< endl;
  for (Edge e : kmst.mstEdges) {
    PrintEdge(e);
  }
  
  return 0;
}
