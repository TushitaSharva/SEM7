import networkx as nx
import random
import os

def generate_random_graph(node_count, edge_count):
    """Generate a random graph with the specified number of nodes and edges."""
    graph = nx.Graph()
    graph.add_nodes_from(range(node_count))
    edges = set()
    while len(edges) < edge_count:
        u = random.randint(0, node_count - 1)
        v = random.randint(0, node_count - 1)
        if u != v:
            edges.add((min(u, v), max(u, v)))  # Avoid duplicate and self-loops
    graph.add_edges_from(edges)
    return graph

def save_graph_as_txt(graph, node_count, edge_count, folder="inputs"):
    """Save the graph as a .txt file in the specified format."""
    os.makedirs(folder, exist_ok=True)
    filename = f"{folder}/graph_{node_count}_nodes_{edge_count}_edges.txt"
    with open(filename, "w") as file:
        # Write the number of vertices and edges
        file.write(f"{node_count} {edge_count}\n")
        # Write each edge (as adjacency list)
        for node in graph.nodes:
            neighbors = list(graph.neighbors(node))
            for neighbor in neighbors:
                if node < neighbor:  # Write each edge only once
                    file.write(f"{node} {neighbor}\n")
    print(f"Graph saved to {filename}")

def main():
    sizes = [10000, 20000, 30000, 40000, 50000]  # Sizes of the graphs
    edge_density_factor = 5  # Average edges per node (adjustable)

    for size in sizes:
        edge_count = size * edge_density_factor
        print(f"Generating graph with {size} nodes and {edge_count} edges...")
        graph = generate_random_graph(size, edge_count)
        
        # Save graph as a .txt file
        save_graph_as_txt(graph, size, edge_count)

if __name__ == "__main__":
    main()