#include <stdio.h>
#include <limits.h>
#define size 6 

int p[size], m[size][size], s[size][size];

void MCM_Order(int n) {
    //putting zeroes in the m[i,i] positions
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }

    //initializing rest positions with infinity
    //l is the chain length
    for (int l = 1; l < n; l++) {  
        for (int i = 0; i < n - l; i++) {
            int j = i + l;  
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + (p[i] * p[k + 1] * p[j + 1]);
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parens(int i, int j) {
    if (i == j) {
        printf("A%d", i+1);
    } else {
        printf("(");
        print_optimal_parens(i, s[i][j]);
        print_optimal_parens(s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    // Input the dimensions
    printf("Enter the dimensions of matrices: ");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    // Call MCM to compute minimum cost and optimal parenthesization
    MCM_Order(n);
    printf("Optimal parenthesization is: ");
    print_optimal_parens(0, n-1);
    printf("\n");

    return 0;
}
