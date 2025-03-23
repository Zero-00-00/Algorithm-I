#include <stdio.h>
#define max 4      //number of edges

int Graph[max][max];    //Adj Matrix

void adj_mat(int u, int v) {
    Graph[u][v] = 1;
}

void BFS(int s) {       //s is source
    int visited[max]={ 0 };          //initialize with 0
    int Q[max], front=0, rear=0;       //d is distance & Q is Queue
    int parent[max]={ -1 };             //pie

    visited[s]=1;           //source set True
    Q[rear++]=s;            //Enqueue source

    printf("BFS Traversal order:\n");
    while(front<rear) {     //check if Queue is Empty
        int u = Q[front++];    //Dequeue  
        printf("%d  ", u);    //visited vertex

        for (int i=0; i<max; i++) {
            if (Graph[u][i]==1 && !visited[i]) {
                visited[i]=1;
                parent[i]=u;
                Q[rear++]=i;
            }
        }
    }

    printf("\nEdges in BFS Traversal:\n");
    for (int i = 0; i < max; i++) {
        if (parent[i] != -1) {  // If the node has a parent, print the edge
            printf("%d -> %d\n", parent[i], i);
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
            printf("Enter the Source Vertex for BFS: ");
            scanf("%d", &s);
            BFS(s);
            cnt=0;
            break;

            case 2:
            for (int i=0; i<n; i++) {
                printf("Enter the edge: ");
                scanf("%d %d", &c1, &c2);
                adj_mat(c1, c2);
                adj_mat(c2, c1);
            }
            printf("Enter the Source Vertex for BFS: ");
            scanf("%d", &s);
            BFS(s);
            cnt=0;
            break;

            default:
            printf("INVALID INPUT!!\n");
        }
    }
}
