#include <stdio.h>
#include <math.h>
#define eps 1e-3
void nhap(int m[], int n){
    printf("Nhap he so: ");
    for(int i = 0; i <= n; i++){
        scanf("%d", &m[i]);
    }
}

double f(double x, int m[], int n){
    double sum = 0;
    for(int i = 0; i <= n; i++){
        sum += m[i] * pow(x, n-i);
    }
    return sum;
}

void chiadoi(int m[], int n){
    double a, b;
    printf("Nhap khoang nghiem: ");
    scanf("%lf%lf", &a, &b);
    double c;
    while(fabs(a - b) >= eps){
        c = (a+b)/2;
        if(f(a, m, n) * f(c, m, n) < 0) b = c;
        else a = c;
    }
    printf("Nghiem gan dung: %lf", (a+b)/2);
}

int main(){
    int n;
    printf("Nhap so bac: ");
    scanf("%d", &n);
    int m[n+1];
    nhap(m, n);
    chiadoi(m, n);
    return 0;
}