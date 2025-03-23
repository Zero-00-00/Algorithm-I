#include <stdio.h>
#define max 6      //number of edges

int Graph[max][max];    //Adj Matrix

void adj_mat(int u, int v) {
    Graph[u][v] = 1;
}

void DFS_visit(int visited[max], int i) {
    visited[i]=1;
    for (int j=0; j<max; j++) {
        if (Graph[i][j]==1 && !visited[j]) {
            printf("%d -> %d\n", i, j);   //print the traversed edges
            DFS_visit(visited, j);
        } 
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
                adj_mat(c1, c2);
            }
            DFS();
            cnt=0;
            break;

            case 2:
            for (int i=0; i<n; i++) {
                printf("Enter the edge: ");
                scanf("%d %d", &c1, &c2);
                adj_mat(c1, c2);
                adj_mat(c2, c1);
            }
            DFS();
            cnt=0;
            break;

            default:
            printf("INVALID INPUT!!\n");
        }
    }
}
