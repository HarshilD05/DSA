#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

struct Edge {
  int src;
  int dest;
  int weight;

  Edge (): src(0), dest(0), weight(0) {}
  Edge (int s, int d, int w): src(s), dest(d), weight(w) {}
};

void PrintEdge(const Edge& e) {
  cout<<"["<< e.src <<" -> "<< e.dest <<" : "<< e.weight <<" ]"<<endl;
}

struct MST_Data {
  int totalCost;
  vector<Edge> mstEdges;
};

MST_Data primsMinSpanTree(const vector<vector<int>>& graph, int srcNode) {
  // Initialise the Distance and the Parent Arrays
  int nNodes = graph.size();
  vector<int> distance(nNodes, INT_MAX);
  vector<int> parent(nNodes, -1);
  set<pair<int, int>> edges;

  // Initialise the Priority Queue
  auto cmp = [](const Edge& e1, const Edge& e2) {return e1.weight < e2.weight;};
  priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);

  // Keep the Dist and Parent of Src Node as 0 and -1 respectively
  distance[srcNode] = 0;
  parent[srcNode] = srcNode;

  // Add the Adjacenty Edges of the Src Node to the Priority Queue
  for (int i = 0; i < nNodes; i++) {
    if (graph[srcNode][i] != 0) {
      if (srcNode < i) {
        pq.push(Edge(srcNode, i, graph[srcNode][i]) );      
        edges.insert({srcNode, i});
      }
      else {
        pq.push(Edge(i, srcNode, graph[srcNode][i]) );
        edges.insert({i, srcNode});
      }
    }
  }

  //
  while (!pq.empty() ) {
    // Pop the Edge with the Min Weight from the Priority Queue
    Edge e = pq.top();
    pq.pop();

    // Check if Updates Needed in the Table
    if (distance[e.dest] > e.weight) {
      // Updating Table
      distance[e.dest] = e.weight;
      parent[e.dest] = e.src;
            
      // If Updated then Add the Adjacenty Edges of the Dest Node to the Priority Queue
      for (int i = 0; i < nNodes; i++) {
        if (graph[e.dest][i] != 0) {
          if (e.dest < i && edges.find({e.dest, i}) == edges.end() ) {
            pq.push(Edge(e.dest, i, graph[e.dest][i]) );
            edges.insert({e.dest, i});
          }
          else if (i < e.dest && edges.find({i, e.dest}) == edges.end() ) {
            pq.push(Edge(i, e.dest, graph[e.dest][i]) );
            edges.insert({i, e.dest});
          }
        }
      }
      
    }
    
  }

  vector<Edge> ans;
  int totalCost = 0;
  // Adding the Edges
  for (int i = 0; i < nNodes; i++) {
    if (i == srcNode) continue;
    if (parent[i] == -1) continue;
    ans.push_back(Edge(parent[i], i, distance[i]) );
    totalCost += distance[i];
  }
  
  return {totalCost,ans};
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

  MST_Data pmst = primsMinSpanTree(graph, 0);

  cout<<"MST Cost : "<< pmst.totalCost <<endl;
  cout<<"MST Edges : "<<endl;
  for (Edge& e : pmst.mstEdges) {
    PrintEdge(e);
  }

  return 0;
}
