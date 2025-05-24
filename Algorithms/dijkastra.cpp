#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;

struct Route {
  int src, dest, totalCost;
  vector<int> path;

  Route (int src = -1, int dest = -1, int totalCost = 0, vector<int> path = {}): src(src), dest(dest), totalCost(totalCost), path(path) {}
};

struct RoutingTable {
  int srcNode;
  unordered_map<int, Route> table;

  RoutingTable(int src, unordered_map<int, Route> rt = {}): srcNode(src), table(rt) {}
};

void PrintRoutingTable(const RoutingTable& rt) {
  cout<<"\nRouting Table for Node : "<< rt.srcNode <<endl;
  for (const auto& r : rt.table) {
    cout<<"Dest : "<< r.first <<"  Cost : "<< r.second.totalCost <<endl;
    cout<<"Path : ";
    for (int x : r.second.path) {
      cout<< x <<", ";
    }
    cout<<endl;
  }
}

RoutingTable dijkastra(const vector<vector<int>>& graph, const int srcNode) {
  const int V = graph.size();
  // Initialise Distance , Vistied and Parent Arrays
  vector<int> dist(V, INT_MAX);
  vector<bool> visited(V, false);
  vector<int> parent(V, -1);

  // Initialise the Source Node
  dist[srcNode] = 0;
  parent[srcNode] = srcNode;
  visited[srcNode] = true;

  // Queue to hold the Nodes
  queue<int> nodes;
  nodes.push(srcNode);

  while (!nodes.empty() ) {
    // Get the Current Node
    int currNode = nodes.front(); nodes.pop();

    // Check all Adjacent Nodes
    for (int i = 0;i<V;i++) {
      if (graph[currNode][i] != 0) {
        // Check Edge and Update Table
        int cost = dist[currNode] + graph[currNode][i];
        if (dist[i] > cost) {
          dist[i] = cost;
          parent[i] = currNode;
        }

        // Add Unvisited nodes in Queue
        if (!visited[i] ) {
          visited[i] = true;
          nodes.push(i);
        }
      }
    }

  }

  // Creating the Routing Table from the Dist and Parent Arrays
  unordered_map<int, Route> rt;
  int idx = 0;
  for (int i = 0;i<V;++i) {
    if (i == srcNode || parent[i] == -1) continue;
    idx = i;
    vector<int> path;
    while (idx != srcNode) {
      path.push_back(idx);
      idx = parent[idx];
    }
    path.push_back(srcNode);

    reverse(path.begin(), path.end() );
    rt[i] = Route(srcNode, i, dist[i], path);
  }

  cout<<"Routes Calculated!";

  return RoutingTable(srcNode, rt);
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

  RoutingTable rt = dijkastra(graph, 0);

  PrintRoutingTable(rt);

  return 0;
}