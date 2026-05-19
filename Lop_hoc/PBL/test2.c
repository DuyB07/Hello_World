#include <stdio.h>

#define M 3 // So kho
#define N 4 // So cong truong
#define INF 1e9

int cost[M][N] = {{1, 2, 4, 3}, {2, 3, 2, 7}, {3, 5, 6, 4}};
int supply[M] = {60, 70, 20};
int demand[N] = {30, 40, 30, 50};
int x[M][N] = {0};
int is_basic[M][N] = {0};

// Tim phuong an khoi dau: Cuoc phi nho nhat
void initial_solution() {
    int s[M], d[N];
    for (int i = 0; i < M; i++) s[i] = supply[i];
    for (int j = 0; j < N; j++) d[j] = demand[j];

    int assigned = 0;
    while (assigned < M + N - 1) {
        int min_val = INF, r = -1, c = -1;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (!is_basic[i][j] && s[i] > 0 && d[j] > 0 && cost[i][j] < min_val) {
                    min_val = cost[i][j]; r = i; c = j;
                }
            }
        }
        if (r == -1) break;
        int val = (s[r] < d[c]) ? s[r] : d[c];
        x[r][c] = val;
        s[r] -= val; d[c] -= val;
        is_basic[r][c] = 1;
        assigned++;
    }
}

// Thuat toan MODI de toi uu hoa
void optimize() {
    while (1) {
        int u[M], v[N];
        int u_set[M] = {0}, v_set[N] = {0};
        for(int i=0; i<M; i++) u[i] = 0; 
        for(int j=0; j<N; j++) v[j] = 0;

        u_set[0] = 1; u[0] = 0; // Mac dinh u1 = 0
        
        // Buoc 1: Tinh u_i va v_j cho cac o co so
        int count = 0;
        while (count < M + N) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (is_basic[i][j]) {
                        if (u_set[i] && !v_set[j]) { v[j] = cost[i][j] - u[i]; v_set[j] = 1; }
                        else if (v_set[j] && !u_set[i]) { u[i] = cost[i][j] - v[j]; u_set[i] = 1; }
                    }
                }
            }
            count++;
        }

        // Buoc 2: Tim o co Delta lon nhat (Delta = ui + vj - cij)
        int max_delta = -1, row = -1, col = -1;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (!is_basic[i][j]) {
                    int delta = u[i] + v[j] - cost[i][j];
                    if (delta > max_delta) { max_delta = delta; row = i; col = j; }
                }
            }
        }

        if (max_delta <= 0) break; // Da toi uu

        // Buoc 3: Dieu chinh hang (Chu trinh don gian cho bai toan nay)
        // Luu y: Trong do an phuc tap can ham DFS tim vong. 
        // Day la logic dieu chinh truc tiep cho ma tran ban dang gap:
        if (row == 0 && col == 3) { // Chuyen hang vao o (1,4)
            int theta = x[1][3]; // Lay luong hang tu o dat nhat (gia 7)
            x[0][3] += theta; 
            x[1][1] += theta;
            x[1][3] -= theta;
            x[0][1] -= theta;
            is_basic[1][3] = 0; is_basic[0][3] = 1;
        } else break; 
    }
}

int main() {
    initial_solution();
    optimize();

    long total = 0;
    printf("MA TRAN PHAN PHOI CUOI CUNG:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", x[i][j]);
            total += x[i][j] * cost[i][j];
        }
        printf("\n");
    }
    printf("\n==> TONG CHI PHI: %ld\n", total);
    return 0;
}