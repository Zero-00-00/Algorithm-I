#include <stdio.h>
#define size 15

int c[size][size];

//quick sort
int swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int part(int A[], int b[], int p, int r) {
    int x = A[p];
    int i = p;
    for(int j = p+1; j < r+1; j++) {
        if (A[j] <= x) {
            i += 1;
            swap (&A[i], &A[j]);
            swap (&b[i], &b[j]);
        }
    }
    swap(&A[i], &A[p]);            //swap the pivot with the element in A[i]
    swap(&b[i], &b[p]);
    return i;
}

int qsort(int A[], int b[], int p, int r) {
    int q;
    if (p < r) {
        q = part(A, b, p, r);
        qsort(A, b, p, q-1);
        qsort(A, b, q+1, r);
    }
}

//max function
int max(int a, int b) {
    return (a > b) ? a : b;
}

//0-1 Knapsack (DP)
void DP_0_1_Knapsack(int w[], int p[], int c[size][size], int n, int W) {
    qsort(w, p, 0, n-1);        //sort the weights
    for (int i=0; i<=W; i++) {
        c[0][i]=0;
    }
    for (int i=1; i<=n; i++) {
        c[i][0]=0;
        for (int j=1; j<=W; j++) {
            if (w[i-1] <= j) {    // i-1 as w, p matices start from zero
                c[i][j] = max(c[i-1][j-w[i-1]] + p[i-1], c[i-1][j]);
            }
            else {
                c[i][j] = c[i-1][j];
            }
        }
    }
}

//find optimal solution

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the weight of the Knapsack: ");
    scanf("%d", &W);
    
    int p[n], w[n];

    printf ("Enter the profits and weights of each item in shop...\n");
    for (int i=0; i<n; i++) {
        printf("Item %d\n", i+1);
        printf("Profit: ");
        scanf("%d", &p[i]);
        printf("Weight: ");
        scanf("%d", &w[i]);
    }

    DP_0_1_Knapsack(w, p, c, n, W);       //applying DP to solve and find the maximum profit of 0-1 Knapsack problem

    // for (int i=0; i<n; i++) {
    //     printf("%d,", p[i]);
    //     printf("%d  ", w[i]);
    // }

    // printf("\n");

    for (int i=0; i<=n; i++) {
        for (int j=0; j<=W; j++) {
            printf("%d  ", c[i][j]);
        }
        printf("\n");
    }

   // Find the optimal solution
   int profit = c[n][W]; // The maximum profit
   printf("Maximum Profit: %d\n", profit);

   // Find which items are included in the optimal solution
   printf("Items included in the knapsack:\n");
   int j = W;
   for (int i = n; i > 0; i--) {
       if (c[i][j] != c[i - 1][j]) { // This item is included
           printf("Item %d\n", i);
           j -= w[i - 1]; // Reduce the weight of the remaining knapsack
       }
   }

    return 0;
}
