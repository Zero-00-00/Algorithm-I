#include <stdio.h>
#include <stdlib.h>
#define max 6      //number of edges

struct list{
    int data;
    struct list* nxt;
};
struct list* Graph[max] = { NULL };

void adj_list(int u, int v) {
    struct list* newNode = (struct list*)malloc(sizeof(struct list));
    newNode->data = v;
    newNode->nxt = NULL;

    if (Graph[u]==NULL) {
        Graph[u] = newNode;
    }
    else {
        struct list* temp = Graph[u];
        while(temp->nxt!=NULL) {
            temp=temp->nxt;
        }
        temp->nxt=newNode;
    }
}

void DFS_visit(int visited[max], int i) {
    visited[i]=1;
    struct list* temp = Graph[i];
        while (temp!=NULL) {
            int v = temp->data;
            if (!visited[v]) {
                printf("%d -> %d\n", i, v);   //print the traversed edges
                DFS_visit(visited, v);
            }
            temp=temp->nxt;
        } 
}

void DFS() {
    int visited[max]={ 0 };          //initialize with 0
    for(int i=0; i<max; i++) {
        if (!visited[i]) {
            printf("DFS Traversed Edges:\n");
            DFS_visit(visited, i);
        }
    }
    printf("\n");
}

int main() {
    int n, c, cnt=1;

    printf("\nEnter the number of edges of the graph: ");
    scanf("%d", &n);

    while (cnt) {
        printf("\n1.Directed\n2.Undirected\n3.Exit\nChoose: ");
        scanf("%d", &c);
        int c1, c2, s;
        switch(c) {
            case 1:
            for (int i=0; i<n; i++) {
                printf("Enter the edge: ");
                scanf("%d %d", &c1, &c2);
                adj_list(c1, c2);
            }
            DFS();
            cnt=0;
            break;

            case 2:
            for (int i=0; i<n; i++) {
                printf("Enter the edge: ");
                scanf("%d %d", &c1, &c2);
                adj_list(c1, c2);
                adj_list(c2, c1);
            }
            DFS();
            cnt=0;
            break;

            default:
            printf("INVALID INPUT!!\n");
        }
    }
}
