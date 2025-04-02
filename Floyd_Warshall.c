#include <stdio.h>
#include <limits.h>

#define MAX 50
#define INF INT_MAX

int dist[MAX][MAX];  // Distance matrix
int next[MAX][MAX];  // Matrix to reconstruct paths

// Function to initialize the matrices
void initialize(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                dist[i][j] = 0;  // Distance to self is 0
            else
                dist[i][j] = INF;  // Initially set to infinity

            next[i][j] = -1;  // No path known initially
        }
    }
}

// Function to run Floyd-Warshall Algorithm
void floydWarshall(int n) {
    // Algorithm: Consider each vertex as an intermediate
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // If vertex k is on the shortest path from i to j, update it
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];  // Update the path
                }
            }
        }
    }

    // Detect negative weight cycles
    for (int k = 0; k < n; k++) {
        if (dist[k][k] < 0) {
            printf("\nGraph contains a negative weight cycle! Exiting...\n");
            return;
        }
    }
}

// Function to print the shortest path between two vertices
void printPath(int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }
    printf("%d", u);
    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
}

// Function to handle user queries
void handleQueries(int n) {
    int q;
    printf("\nEnter the number of queries: ");
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int u, v;
        printf("Enter source and destination: ");
        scanf("%d %d", &u, &v);

        if (u >= n || v >= n || u < 0 || v < 0) {
            printf("Invalid query! Nodes out of range.\n");
            continue;
        }

        printf("Shortest distance from %d to %d: ", u, v);
        if (dist[u][v] == INF)
            printf("INF (No path)\n");
        else {
            printf("%d\n", dist[u][v]);
            printf("Path: ");
            printPath(u, v);
            printf("\n");
        }
    }
}

int main() {
    int n, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Initialize the matrices
    initialize(n);

    printf("Enter the number of edges: ");
    scanf("%d", &e);
    printf("Enter the edges with their weights (u v weight):\n");

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= n || v >= n || u < 0 || v < 0) {
            printf("Invalid edge (%d, %d). Skipping...\n", u, v);
            continue;
        }
        dist[u][v] = w;
        next[u][v] = v;  // Initialize path tracking
    }

    // Run Floyd-Warshall Algorithm
    floydWarshall(n);

    // Handle user queries for shortest paths
    handleQueries(n);

    return 0;
}
