#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;

void PrintMatrix(const vector<vector<int>>& matrix) {
  for (const auto& row : matrix) {
    for (const int& x : row) {
      cout<< x <<" ";
    }
    cout<<endl;
  }
}

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

  RoutingTable(int src = -1, unordered_map<int, Route> rt = {}): srcNode(src), table(rt) {}
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

unordered_map<int, RoutingTable> FloydWarshall(vector<vector<int>> graph) {
  const int V = graph.size();
  // Initialise the Cost Matrix and Next Hop Matrix
  vector<vector<int>> nextHop(V, vector<int>(V, -1));
  // Cost Matrix = Copy of Graph Adj Matrix with diagnol as 0 and other 0 values turned to INF
  for (int i = 0;i<V-1;++i) {
    for (int j = i+1;j<V;j++) {
      if (graph[i][j] == 0) {
        graph[i][j] = INT_MAX;
        graph[j][i] = INT_MAX;
      }
      else {
        nextHop[i][j] = j;
        nextHop[j][i] = i;
      }
    }
  }


  int cost;
  // Floyd Warsahll Algorithm Calculates Path from all nodes to All nodes
  // Going Via Intermediate Nodes
  for (int i = 0;i<V;++i) {
    for (int j = 0;j<V;j++) {
      // If row is of Intermediate Skip or if Dist Via CurrNode to dest is INF
      if (j == i || graph[j][i] == INT_MAX) continue;
      for (int k = 0;k<V;k++) {
        // If Col is of Intermediate Skip or if Dist Via CurrNode to dest is INF
        // OR if diagonal Value
        if (k == j || k == i || graph[i][k] == INT_MAX) continue;

        // Update Cost
        cost = graph[j][i] + graph[i][k];
        if (graph[j][k] > cost) {
          graph[j][k] = cost;
          nextHop[j][k] = i;
        }
      }
    }
  }

  unordered_map<int, RoutingTable> graphRoutes;
  int nextNode;
  // Construct Routing table from the Cost and NextHop Matrix
  for (int i = 0;i<V;++i) {
    // Routing Table for Each Node
    RoutingTable rt(i);
    for (int j = 0;j<V;j++) {
      if (i == j) continue; // Skip Diagonal

      // Construct Route for i to j
      vector<int> path;
      nextNode = i;
      while (nextNode != j) {
        cout<< nextNode;
        path.push_back(nextNode);
        nextNode = nextHop[nextNode][j];
      }
      path.push_back(j);

      // Add the Route for j to Routing table for i
      rt.table[j] = Route(i, j, graph[i][j], path);
    }

    // Add Routing Table for this ndoe to the Graph Routes
    graphRoutes[i] = rt;
  }

  cout<<"Returning..."<<endl;

  return graphRoutes;
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

  unordered_map<int, RoutingTable> graphRoutes = FloydWarshall(graph);
  for (const pair<int, RoutingTable>& p : graphRoutes) {
    cout<<"\n";
    PrintRoutingTable(p.second);
  }


  return 0;
}