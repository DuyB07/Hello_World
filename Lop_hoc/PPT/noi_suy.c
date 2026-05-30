#include <stdio.h>
#include <math.h>
#define eps 1e-3

void C1_Lagrange()

int main() {
    int n;
    double c, a[100];
    printf("Nhap bac da thuc n: ");
    scanf("%d", &n);
    printf("Nhap he so a_i (tu a_0 den a_n): ");
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &a[i]);
    }
    printf("Nhap gia tri c: ");
    scanf("%lf", &c);
    
    noi_suy(a, n, c);
    
    return 0;
}