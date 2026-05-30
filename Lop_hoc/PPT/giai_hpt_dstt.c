#include <stdio.h>

#define MAX 100
// Nhập ma trận vuông cấp n
void nhap(int a[][MAX], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

// Tính định thức ma trận vuông cấp n
double Dt(int a[][MAX], int n){
    if(n == 1) return a[0][0];
    if(n == 2) return a[0][0]*a[1][1] - a[0][1]*a[1][0];
    double dt = 0;
    for(int j = 0; j < n; j++){
        int b[MAX][MAX];
        for(int i = 1; i < n; i++){
            for(int k = 0; k < n; k++){
                if(k < j) b[i-1][k] = a[i][k];
                else if(k > j) b[i-1][k-1] = a[i][k];
            }
        }
        dt += (j % 2 == 0 ? 1 : -1) * a[0][j] * Dt(b, n-1);
    }
    return dt;
}