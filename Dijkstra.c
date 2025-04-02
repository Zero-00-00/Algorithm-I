#include <stdio.h>
#include <limits.h>

#define MAX 50

int Graph[MAX][MAX] = {0};  // Adjacency Matrix
int weight[MAX][MAX] = {0}; // Edge weights
int distance[MAX];          // Distance from source
int parent[MAX];            // Parent array for path reconstruction
int Q[MAX];                 // Min-Heap (vertex indices)
int pos[MAX];               // Position of each vertex in the heap
int inHeap[MAX];            // Track if vertex is in heap

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heapify function
void min_heapify(int i, int heap_size) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < heap_size && distance[Q[left]] < distance[Q[smallest]])
        smallest = left;

    if (right < heap_size && distance[Q[right]] < distance[Q[smallest]])
        smallest = right;

    if (smallest != i) {
        pos[Q[i]] = smallest;
        pos[Q[smallest]] = i;

        swap(&Q[i], &Q[smallest]);
        min_heapify(smallest, heap_size);
    }
}

// Build the Min-Heap
void build_min_heap(int heap_size) {
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        min_heapify(i, heap_size);
    }
}

// Extracts the minimum distance vertex from the heap
int extract_min(int *heap_size) {
    if (*heap_size == 0) return -1;

    int min_vertex = Q[0];
    Q[0] = Q[--(*heap_size)];
    pos[Q[0]] = 0;
    min_heapify(0, *heap_size);

    inHeap[min_vertex] = 0;  // Mark as removed from heap
    return min_vertex;
}

// Decreases the key value and updates heap
void decrease_key(int v, int new_key) {
    int i = pos[v];
    distance[v] = new_key;

    while (i > 0 && distance[Q[(i - 1) / 2]] > distance[Q[i]]) {
        pos[Q[i]] = (i - 1) / 2;
        pos[Q[(i - 1) / 2]] = i;

        swap(&Q[i], &Q[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Checks if a vertex is still in the heap
int Q_member(int v) {
    return inHeap[v];
}

// Relax function to update shortest path
void relax(int u, int v) {
    if (distance[v] > distance[u] + weight[u][v]) {
        distance[v] = distance[u] + weight[u][v];
        parent[v] = u;  // Track parent for path reconstruction
        decrease_key(v, distance[v]);
    }
}

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

void Dijkstra(int src, int n) {
    int heap_size = n;

    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        Q[i] = i;
        pos[i] = i;
        inHeap[i] = 1;
    }

    distance[src] = 0;
    build_min_heap(n);

    while (heap_size > 0) {
        int u = extract_min(&heap_size);

        for (int v = 0; v < n; v++) {
            if (Graph[u][v] && Q_member(v)) {
                relax(u, v);
            }
        }
    }

    printf("\nShortest Paths from Source %d:\n", src);
    printf("Destination   Distance   Path\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d      %d      ", src, i, distance[i]);
        print_path(src, i);
        printf("\n");
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
        weight[v][u] = w;
        Graph[u][v] = 1;
        Graph[v][u] = 1;
    }

    printf("Enter the source vertex for Dijkstra’s Algorithm: ");
    scanf("%d", &src);

    if (src < 0 || src >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    Dijkstra(src, n);
    return 0;
}
