#include <stdio.h>
#include <stdlib.h>
#define n 8

int x[n];        //global solution `array`

int place(int k, int i) {     //returns true if Q is placed at k-th row and i-th col, otherwise false
    for (int j=1; j<k; j++) {       //check all prev Q
        if ((x[j] == i) || (abs(x[j]-i) == abs(j-k)))       //in same col or diagonal
        return 0;
    }
    return 1;
}

void NQueens(int k) {
    for (int i=1; i<=n; i++) {
        if (place(k, i)) {
            x[k]=i;
            if (k==n) {
                for (int j=1; j<=n; j++) {
                    printf("%d\n", x[j]);
                }
                printf("\n");
            }
            else
            NQueens(k+1);
        }
    }
}

int main() {
    NQueens(1);
}