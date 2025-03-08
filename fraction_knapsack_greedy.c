#include <stdio.h>

//quick sort
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int part(int A[], int b[], int c[], int p, int r) {     //adept at swapping all the matrices based on ratio
    int x = A[p];
    int i = p;
    for(int j = p+1; j < r+1; j++) {
        if (A[j] >= x) {
            i += 1;
            swap (&A[i], &A[j]);
            swap (&b[i], &b[j]);
            swap (&c[i], &c[j]);
        }
    }
    swap(&A[i], &A[p]);            //swap the pivot with the element in A[i]
    swap (&b[i], &b[p]);
    swap (&c[i], &c[p]);
    return i;
}

void qsort(int A[], int b[], int c[], int p, int r) {
    int q;
    if (p < r) {
        q = part(A, b, c, p, r);
        qsort(A, b, c, p, q-1);
        qsort(A, b, c, q+1, r);
    }
}

// Greedy Algorithm
int greedy(int w[], int p[], int ratio[], float x[], int W, int n) {
    for (int i=0; i<n; i++) {       //initialize the x[i] matrix with zero
        x[i]=0;
    }

    for (int i=0; i<n; i++) {       //finding the ratio (profit/weight)
        ratio[i]=p[i]/w[i];
    }

    qsort(ratio, w, p, 0, n-1);     //sort

    int weight=0, profit=0;

    for (int i=0; i<n; i++) {
        if (weight + w[i] < W) {
            x[i]=1;
            weight+=w[i];
            profit+=p[i];
        }
        else {
            x[i]=(float)(W - weight)/w[i];
            weight=W;
            profit+=p[i]*x[i];
            break;
        }
    }

    return profit;
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the weight of the Knapsack: ");
    scanf("%d", &W);
    
    int p[n], w[n], ratio[n];
    float x[n];

    printf ("Enter the profits and weights of each item in shop...\n");
    for (int i=0; i<n; i++) {
        printf("Item %d\n", i+1);
        printf("Profit: ");
        scanf("%d", &p[i]);
        printf("Weight: ");
        scanf("%d", &w[i]);
    }

    printf("The maximum profit is %d\n", greedy(w, p, ratio, x, W, n));       //applying greedy algorithm

    printf("The optimal solution is\n");
    for (int i=0; i<n; i++) {
        printf("%.2f of item with weight %d, profit %d\n", x[i], w[i], p[i]);
    }

    return 0;
}