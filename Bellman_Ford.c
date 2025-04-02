#include <stdio.h>
#include <limits.h>

#define MAX 50

int Graph[MAX][MAX] = {0};  // Adjacency Matrix
int weight[MAX][MAX] = {0}; // Edge weights
int distance[MAX];          // Distance from source
int parent[MAX];            // Parent array for path reconstruction

// Function to print the path from source to a vertex
void print_path(int src, int v) {
    if (v == src) {
        printf("%d", src);
        return;
    }
    if (parent[v] == -1) {
        printf("No path");
        return;
    }
    print_path(src, parent[v]);
    printf(" -> %d", v);
}

// Bellman-Ford Algorithm
void BellmanFord(int src, int n, int e) {
    // Step 1: Initialize distances
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[src] = 0;

    // Step 2: Relax all edges (n-1) times
    for (int i = 1; i <= n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (Graph[u][v] && distance[u] != INT_MAX && distance[u] + weight[u][v] < distance[v]) {
                    distance[v] = distance[u] + weight[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (Graph[u][v] && distance[u] != INT_MAX && distance[u] + weight[u][v] < distance[v]) {
                printf("\nGraph contains a negative weight cycle! Exiting...\n");
                return;
            }
        }
    }

    // Step 4: Print the shortest paths
    printf("\nShortest Paths from Source %d:\n", src);
    printf("Destination   Distance   Path\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d      ", src, i);
        if (distance[i] == INT_MAX) {
            printf("INF      No path\n");
        } else {
            printf("%d      ", distance[i]);
            print_path(src, i);
            printf("\n");
        }
    }
}

int main() {
    int n, e, src;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &e);
    printf("Enter the edges with their weights (vertex1 vertex2 weight):\n");

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= n || v >= n || u < 0 || v < 0) {
            printf("Invalid edge (%d, %d). Skipping...\n", u, v);
            continue;
        }
        weight[u][v] = w;
        Graph[u][v] = 1; // Directed graph
    }

    printf("Enter the source vertex for Bellman-Ford Algorithm: ");
    scanf("%d", &src);

    if (src < 0 || src >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    BellmanFord(src, n, e);
    return 0;
}
