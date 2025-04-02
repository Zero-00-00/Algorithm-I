#include <stdio.h>
#include <limits.h>

#define MAX 50

int Graph[MAX][MAX] = {0};  // Adjacency Matrix
int weight[MAX][MAX] = {0}; // Edge weights
int parent[MAX];            // Predecessor
int key[MAX];               // Key value for each vertex
int Q[MAX];                 // Min-Heap (stores vertex indices)
int pos[MAX];               // Position of each vertex in the heap
int inHeap[MAX];            // Tracks if a vertex is in the heap

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

    if (left < heap_size && key[Q[left]] < key[Q[smallest]])
        smallest = left;

    if (right < heap_size && key[Q[right]] < key[Q[smallest]])
        smallest = right;

    if (smallest != i) {
        // Update positions before swapping
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

// Extracts the minimum key vertex from the heap
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
    key[v] = new_key;

    while (i > 0 && key[Q[(i - 1) / 2]] > key[Q[i]]) {
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

void prim(int r, int n) {
    int heap_size = n;

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        Q[i] = i;
        pos[i] = i;
        inHeap[i] = 1;  // Mark all vertices as present in the heap
    }

    key[r] = 0;
    build_min_heap(n);

    while (heap_size > 0) {
        int u = extract_min(&heap_size);

        for (int v = 0; v < n; v++) {
            if (Graph[u][v] && Q_member(v) && weight[u][v] < key[v]) {
                parent[v] = u;
                decrease_key(v, weight[u][v]);
            }
        }
    }

    printf("\nEdges in MST:\n");
    int mst_weight = 0;
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d -> %d (Weight: %d)\n", parent[i], i, weight[parent[i]][i]);
            mst_weight += weight[parent[i]][i];
        }
    }

    printf("Total weight of MST: %d\n", mst_weight);
}

int main() {
    int n, r, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges in the Graph: ");
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

    printf("Enter the start point for Prim's MST: ");
    scanf("%d", &r);
    
    if (r < 0 || r >= n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    prim(r, n);
}
