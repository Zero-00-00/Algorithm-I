#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50  // Max edges

struct edge {
    struct ele *u, *v;
    int weight;
};

struct set {
    struct ele *head, *tail;
};

struct ele {
    struct set *head;
    char vertex;
    struct ele *tail;
};

struct edge* w[MAX]; // Array to store edges
struct ele* vertex[256]; // Ensure all characters map properly

struct set* make_set(struct ele* x) {
    struct set* newset = (struct set*)malloc(sizeof(struct set));
    newset->head = x;
    newset->tail = NULL;
    x->head = newset;
    x->tail = NULL;
    return newset;
}

struct ele* find_set(struct ele* x) {
    return x->head->head;
}

void Union(struct ele* x, struct ele* y) {
    struct set* U = x->head;
    struct ele* temp = find_set(y);
    struct ele* temp2 = x;

    while (temp2->tail != NULL) {
        temp2 = temp2->tail;
    }
    temp2->tail = temp; // Attach set y to set x

    while (temp != NULL) {
        temp->head = U; // Update set pointers
        temp = temp->tail;
    }
}

// Swap function for qsort
void swap(struct edge** p, struct edge** q) {
    struct edge* temp = *p;
    *p = *q;
    *q = temp;
}

// Partition function for quicksort
int partition(int p, int r) {
    int pivot = w[r]->weight;  
    int i = p - 1;  

    for (int j = p; j < r; j++) {
        if (w[j]->weight <= pivot) {
            i++;
            swap(&w[i], &w[j]);
        }
    }
    swap(&w[i + 1], &w[r]);  
    return i + 1;
}

// Quicksort function
void quicksort(int p, int r) {
    if (p < r) {
        int q = partition(p, r);
        quicksort(p, q - 1);
        quicksort(q + 1, r);
    }
}

// Kruskal’s algorithm
void Kruskal(int edge_count) {
    for (int i = 0; i < 256; i++) {
        if (vertex[i] != NULL) {
            make_set(vertex[i]);
        }
    }

    quicksort(0, edge_count - 1);
    printf("Minimum Spanning Tree Edges:\n");

    for (int i = 0; i < edge_count; i++) {
        struct ele* u = w[i]->u;
        struct ele* v = w[i]->v;

        if (find_set(u) != find_set(v)) {
            printf("(%c, %c)\n", u->vertex, v->vertex);
            Union(u, v);
        }
    }
}

int main() {
    int v, n;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);

    printf("Enter the vertices:\n");
    for (int i = 0; i < v; i++) {
        char c;
        scanf(" %c", &c);  // Leading space to ignore newline
        vertex[(int)c] = (struct ele*)malloc(sizeof(struct ele));
        vertex[(int)c]->vertex = c;
        vertex[(int)c]->head = NULL;
        vertex[(int)c]->tail = NULL;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Error: Too many edges!\n");
        return 1;
    }

    printf("Enter the edges (vertex1 weight vertex2):\n");
    for (int i = 0; i < n; i++) {
        char u, v;
        int weight;
        scanf(" %c %d %c", &u, &weight, &v);

        struct edge* temp = (struct edge*)malloc(sizeof(struct edge));
        temp->u = vertex[(int)u];  // Reference existing vertex
        temp->v = vertex[(int)v];
        temp->weight = weight;

        w[i] = temp;
    }

    Kruskal(n);
    return 0;
}
