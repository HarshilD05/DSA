#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;

struct Edge {
  int weight, src, dest;

  Edge () : src(-1), dest(-1), weight(0) {}
  Edge (int src, int dest, int weight) : src(src), dest(dest), weight(weight)  {}
};

void PrintEdge(const Edge& e) {
  cout<< e.src <<" -> "<< e.dest <<"("<< e.weight <<")"<<endl;
}

typedef struct Route {
  int src, dest, totalCost;
  vector<int> path;

  Route (int src = -1, int dest = -1, int totalCost = 0, vector<int> path = {}): src(src), dest(dest), totalCost(totalCost), path(path) {}
} Route;

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

vector<Edge> GetUndirectedEdges(const vector<vector<int>>& graph) {
  vector<Edge> edges;
  const int V = graph.size();
  for (int i = 0;i<V;i++) {
    for (int j = i+1;j<V;j++) {
      if (graph[i][j] != 0) {
        edges.push_back(Edge(i, j, graph[i][j]) );
      }
    }
  }

  return edges;
}


RoutingTable BellmanFord(const vector<vector<int>>& graph, const int srcNode) {
  const int V = graph.size();
  vector<Edge> edges = GetUndirectedEdges(graph);

  // Initialise Distance and Parent Arrays
  vector<int> dist(V, INT_MAX);
  vector<int> parent(V, -1);

  // Initialise the Source Node
  dist[srcNode] = 0;
  parent[srcNode] = srcNode;
  bool change = false;
  int cost;

  for (int i = 0;i<V;i++) {
    change = false;

    for (const Edge& e : edges) {
      // If Source Node Dist is INF then dont check
      if (dist[e.src] == INT_MAX) continue;

      cost = dist[e.src] + e.weight;
      if (dist[e.dest] > cost) {
        dist[e.dest] = cost;
        parent[e.dest] = e.src;

        change = true;
      }
    }

    // If No change Happened to Table in Last itteration no need to check again
    if (!change) break;
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

  // Check 1 More Time for the Negative Cycle
  for (Edge& e : edges) {
    cost = dist[e.src] + e.weight;
    if (cost < dist[e.dest]) {
      cout<<"Negetive Weight Cycle Found at Node : "<< e.dest <<endl;
      break;
    }
  }

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

  RoutingTable rt = BellmanFord(graph, 0);

  PrintRoutingTable(rt);

  return 0;
}