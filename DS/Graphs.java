import java.util.ArrayList;
import java.util.Collection;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Queue;
import java.util.LinkedList;

// import org.json.simple.JSONArray;
// import org.json.simple.JSONObject;
// import org.json.simple.parser.JSONParser;
// import org.json.simple.parser.ParseException;
// import java.io.FileReader;
// import java.io.IOException;

public class Graphs {
	static class GraphConnection {
		private GraphNode destNode;
		private int weight;

		GraphConnection(GraphNode destNode) {
			this.destNode = destNode;
			this.weight = 0;
		}

		GraphConnection(GraphNode destNode, int weight) {
			this.destNode = destNode;
			this.weight = weight;
		}

		public void printDetails () {
			System.out.println(this.destNode.name + " : " + this.weight);
		}

		public String getDetails () {
			return (this.destNode.name +" : "+ this.weight);
		}

	};

	static class GraphNode {
		String name;
		ArrayList<GraphConnection> connections;

		GraphNode (String name) {
			this.name = name;
			this.connections = new ArrayList<GraphConnection>();
		}

		GraphNode (String name, ArrayList<GraphConnection> connections) {
			this.name = name;
			this.connections = connections;
		}

		public void printDetails () {
			System.out.println("GraphNode : "+ this.name);
			System.out.println("Connections : ");
			for (GraphConnection conn : this.connections) {
				conn.printDetails();
			}
			System.out.println();
		}

	};

	static class Route {
		GraphNode sourceNode;
		GraphNode destinationNode;
		int totalCost;
		ArrayList<GraphConnection> routePath;

		Route (GraphNode src, GraphNode dest) {
			this.sourceNode = src;
			this.destinationNode = dest;
			this.totalCost = 0;
			this.routePath = new ArrayList<GraphConnection>();
		}

		public void printDetails () {
			System.out.println("Routing Table for " + this.sourceNode.name + " -> " + this.destinationNode.name );
			System.out.println("Total Cost : " + this.totalCost );
			System.out.println("Routing Path : ");
			for (GraphConnection conn : this.routePath ) {
				System.out.println(conn.destNode.name + " : " + conn.weight);
			}
			System.out.println();
		}

	};

	static class GraphData {
		private Map<String, GraphNode> nodes;
		private Map<GraphNode, Map<GraphNode, Route> > routingTable;

		private void calculateRoutingTable () {
			this.routingTable = new  HashMap<GraphNode, Map<GraphNode, Route> >();

			// Itterating through each Node and creating its Routing Table
			for (String nodeName : this.nodes.keySet() ) {
				GraphNode n = this.nodes.get(nodeName);
				Map<GraphNode, Route> nodeNRoutingTable = new HashMap<>();

				// Route to Self
				Route rtToSelf = new Route(n, n);
				// Check if Route to self mentioned in Connections else add a 0 cost route
				for (GraphConnection conn : n.connections ) {
					if (conn.destNode == n) {
						rtToSelf.totalCost = conn.weight;
						break;
					}
				}
				// adding Route to Self in Routing Table
				nodeNRoutingTable.put(n, rtToSelf);

				// Using Que to record the neighbouring nodes
				Queue<GraphNode> q = new LinkedList<>();
				// Using this to record the relaxed Nodes of Graphs
				Set<GraphNode> relaxedNodes = new HashSet<>();
				q.add(n);
				
				GraphNode currNode;

				while (!q.isEmpty() && relaxedNodes.size() < this.nodes.size() ) {
					// Get the Current Node from Que
					currNode = q.remove();
		
					// Routing Table Part
					for (GraphConnection conn : currNode.connections ) {
						// Add the Neighbouring Nodes in Que if Not relaxed
						if (!relaxedNodes.contains(conn.destNode) ) q.add(conn.destNode);
		
						// Add a Route to this Node if not already present
						if (!nodeNRoutingTable.containsKey(conn.destNode) ) {
							Route rt = new Route(n, conn.destNode);
							// Add the route to the currNode to the Routing table
							rt.routePath.addAll(nodeNRoutingTable.get(currNode).routePath );
							// Add Path to connected Node
							rt.routePath.add(conn);
							// Set the total Cost
							rt.totalCost = nodeNRoutingTable.get(currNode).totalCost + conn.weight;
							// Add to Routing table
							nodeNRoutingTable.put(conn.destNode, rt);
						}
						// If Route To Node Already Present
						else {
							// get reference to the Route of this node
							Route rt = nodeNRoutingTable.get(conn.destNode);
							// Calculate the Cost to rech this node using this Path
							int currNodeCost = nodeNRoutingTable.get(currNode).totalCost;
							int newCost = currNodeCost + conn.weight;
							
							// Update the Route if the newRoute is Shorter
							if (newCost < rt.totalCost) {
								// remove the Previous RoutePath
								rt.routePath.clear();
								// add the Route to CurrNode
								rt.routePath.addAll(nodeNRoutingTable.get(currNode).routePath);
								// Add Connection from CurrNode to Neighbour Node
								rt.routePath.add(conn);
								// UpdateCost
								rt.totalCost = newCost;
							}
						}
		
					}
					
					// Add CurrNode to relaxed Nodes
					relaxedNodes.add(currNode);			
				}

				// Availing Memory of Que and Set for clear
				q = null;
				relaxedNodes = null;				

				// Add this Nodes Routing table to the Graph Routing table
				routingTable.put(n, nodeNRoutingTable);
			}

		}

		GraphData (Collection<GraphNode> nodes) {
			this.nodes = new HashMap<String, GraphNode>();
			// Add the GraphNodes from the collection to the set 
			for (GraphNode node : nodes) {
				this.nodes.put(node.name, node);
			}
			// Calculate the Routing table
			calculateRoutingTable();
		}

		public void printRoutingTableDetails() {
			System.out.println("Routing Table of the Graph");
			for (String nodeName : this.nodes.keySet() ) {
				GraphNode n = this.nodes.get(nodeName);
				System.out.println("Routing table for Node : "+ n.name);
				Map<GraphNode, Route> rTable = this.routingTable.get(n);
				for (GraphNode k : rTable.keySet() ) {
					rTable.get(k).printDetails();
				}
			}

		}

		public void printGraphNodesDetails() {
			System.out.println("Graph Nodes : ");
			for (String nodeName : this.nodes.keySet() ) {
				this.nodes.get(nodeName).printDetails();
			}
		}		

	};

	// This Function was created because I Couldn't Load the GraphData from the Json
	static GraphData createDummyGraph() {
		ArrayList<GraphNode> nodes = new ArrayList<GraphNode>();
		// Creating Nodes
		GraphNode a = new GraphNode("A");
		GraphNode b = new GraphNode("B");
		GraphNode c = new GraphNode("C");
		GraphNode d = new GraphNode("D");
		GraphNode e = new GraphNode("E");
		GraphNode f = new GraphNode("F");

		// Forming Connections
		// A Node Connections
		a.connections.add( new GraphConnection(b,2) );
		a.connections.add( new GraphConnection(c,3) );
		// B Node Connections
		b.connections.add( new GraphConnection(a,2) );
		b.connections.add( new GraphConnection(c,1) );
		b.connections.add( new GraphConnection(d,4) );
		// C Node Connections
		c.connections.add( new GraphConnection(a,3) );
		c.connections.add( new GraphConnection(b,1) );
		c.connections.add( new GraphConnection(d,2) );
		c.connections.add( new GraphConnection(e,4) );
		// D Node Connections
		d.connections.add( new GraphConnection(b,4) );
		d.connections.add( new GraphConnection(c,2) );
		d.connections.add( new GraphConnection(e,2) );
		d.connections.add( new GraphConnection(f,3) );
		// E Node Connections
		e.connections.add( new GraphConnection(c,4) );
		e.connections.add( new GraphConnection(d,2) );
		e.connections.add( new GraphConnection(f,1) );
		// F Node Connections
		f.connections.add( new GraphConnection(d,3) );
		f.connections.add( new GraphConnection(e,1) );

		// Inserting Nodes
		nodes.add(a);
		nodes.add(b);
		nodes.add(c);
		nodes.add(d);
		nodes.add(e);
		nodes.add(f);

		GraphData gd = new GraphData(nodes);
		return gd;
	}


	public static void main(String[] args) {
		/*
		// Testing JSON Parse Code
		JSONParser parser = new JSONParser();

		try (FileReader reader = new FileReader("./graphData.json")) {
			// Parse the JSON file
			JSONObject jsonObject = (JSONObject) parser.parse(reader);

			// Get the JSON array
			JSONArray nodesArray = (JSONArray) jsonObject.get("nodes");

			// Iterate over the array
			for (Object nodeObj : nodesArray) {
				String node = (String) nodeObj;

				// Print node
				System.out.println("Node: " + node);
			}
		} catch (IOException | ParseException e) {
			e.printStackTrace();
		}
		*/
	
		/* Sample data */
		GraphData gd = createDummyGraph();
		gd.printGraphNodesDetails();
		
	}

}
