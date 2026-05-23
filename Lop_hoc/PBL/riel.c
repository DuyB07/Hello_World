#include <stdio.h>

#define MAX 20
#define INF 1e9

#define can_bang 1
#define khong_can_bang 0

#define suy_bien 1
#define khong_suy_bien 0

#define TRUE 1
#define FALSE 0

typedef struct {
    int r, c;
} Box;

Box path[MAX * 2];
int path_len = 0;

int u[MAX], v[MAX];
u[0] = 0;

int coeff[MAX][MAX];

int is_basis[MAX][MAX];

void nhap_tram(int m, int n, int supply[], int demand[])
{
    for (int i = 0; i < m; i++)
    {
        printf("Luong hang o tram phat %d: ", i);
        scanf("%d", &supply[i]);
        while (supply[i] <= 0)
        {
            printf("So hang tram phat phai > 0\n");
            printf("Luong hang o tram phat %d: ", i);
            scanf("%d", &supply[i]);
        }
    }

    for (int j = 0; j < n; j++)
    {
        printf("Luong hang o tram thu %d: ", j);
        scanf("%d", &demand[j]);
        while (demand[j] <= 0)
        {
            printf("So hang tram thu phai > 0\n");
            printf("Luong hang o tram thu %d: ", j);
            scanf("%d", &demand[j]);
        }
    }
}

void nhap_chi_phi(int m, int n, int cost[][MAX])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("- Chi phi o (%d, %d): ", i, j);
            scanf("%d", &cost[i][j]);

            while (cost[i][j] <= 0)
            {
                printf("Chi phi phai > 0\n");
                printf("- Chi phi o (%d, %d): ", i, j);
                scanf("%d", &cost[i][j]);
            }
        }
    }
}

int least_cost_method(int m, int n, int supply[], int demand[], int cost[][MAX], int allocation[][MAX]){
    int count = 0;
    while(1){
        int minCost = INF;
        int row = -1, column = -1;

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(supply[i] > 0 && demand[j] > 0){
                    if(cost[i][j] < minCost){
                        minCost = cost[i][j];
                        row = i;
                        column = j;
                    }
                }   
            }
        }

        if(row == -1 || column == -1){
            break;
        }

        int x;

        if(supply[row] < demand[column]){
            x = supply[row];
        }
        else x = demand[column];

        allocation[row][column] = x;
        is_basis[row][column] = TRUE;

        supply[row] -= x;
        demand[column] -= x;

        count += 1;
    }
    return count;
}

int xet_tinh_suy_bien(int m, int n, int supply[], int demand[], int cost[][MAX], int allocation[][MAX]){
    int count = least_cost_method(m,n,supply,demand,cost,allocation);
    if(count == m + n - 1) return khong_suy_bien;
    else return suy_bien;
}

int check_cycle(int m, int n, int curr_r, int curr_c, int start_r, int start_c, int step, int dir, int visited[][MAX], int allocation[][MAX]){
    if(curr_r == start_r && curr_c == start_c && step >= 4){
        path_len = step;
        return TRUE;
    }

    if(visited[curr_r][curr_c] == TRUE) return FALSE;

    if(step > 0 && !allocation[curr_r][curr_c]) return FALSE;

    visited[curr_r][curr_c] = TRUE;
    path[step].r = curr_r;
    path[step].c = curr_c;
    
    // 2 --> cần đi ngang
    if(dir == 0 || dir == 2){
        for(int next_c = 0; next_c < n; next_c++){
            if(next_c != curr_c){
                if(check_cycle(m, n, curr_r, next_c, start_r, start_c, step+1, 1, visited, allocation))
                    return TRUE;
            }
        }
    }

    // 1 --> cần đi dọc
    if(dir == 0 || dir == 1){
        for(int next_r = 0; next_r < m; next_r++){
            if(next_r != curr_r){
                if(check_cycle(m, n, next_r, curr_r, start_r, start_c, step + 1, 2, visited, allocation))
                    return TRUE;
            }
        }
    }

    visited[curr_r][curr_c] = FALSE;
    return FALSE;
}

void he_thong_the_vi(int m, int n, int cost[][MAX], int is_basis[][MAX]){
    int mark_u[MAX], mark_v[MAX];
    mark_u[0] = TRUE;

    for(int i = 1; i < m; i++){
        mark_u[i] = FALSE;
    }

    for(int j = 0; j < n; j++){
        mark_v[j] = FALSE;
    }

    int changed;
    do {
        changed = FALSE;

        for(int curr_r = 0; curr_r < m; curr_r++){
            for(int curr_c = 0; curr_c < n; curr_c++){
                if(is_basis[curr_r][curr_c]){
                    if(mark_u[curr_r] == TRUE && mark_v[curr_c] == FALSE){
                        v[curr_c] = cost[curr_r][curr_c] - u[curr_r];
                        mark_v[curr_c] = TRUE;
                        changed = TRUE;
                    }

                    else if(mark_u[curr_r] == FALSE && mark_v[curr_c] == TRUE){
                        u[curr_r] = cost[curr_r][curr_c] - v[curr_c];
                        mark_u[curr_r] = TRUE;
                        changed = TRUE;
                    }
                }
            }
        }   
    }
    while(changed);
}

void tinh_hsul(int m, int n, int cost[][MAX], int is_basic[][MAX]){
    for(int curr_r = 0; curr_r < m; curr_r++){
        for(int curr_c = 0; curr_c < n; curr_c++){
            if(!is_basic[curr_r][curr_c]){
                coeff[curr_r][curr_c] = u[curr_r] + v[curr_c] - cost[curr_r][curr_c];
            }
        }
    }
}

int check_can_bang(int m, int n)
{
    if (m = n)
        return can_bang;
    return khong_can_bang;
}

int main()
{
    int m, n;
    printf("Nhap so tram phat: ");
    scanf("%d", &m);
    while (m <= 0)
    {
        printf("So tram phat phai > 0\n");
        printf("Nhap so tram phat");
        scanf("%d", &m);
    }

    printf("Nhap so tram thu: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("So tram thu phai > 0\n");
        printf("Nhap so tram thu: ");
        scanf("%d", &n);
    }

    int supply[MAX];
    int demand[MAX];

    int cost[MAX][MAX];

    int allocation[MAX][MAX];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            allocation[i][j] = 0;
        }
    }
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            is_basis[i][j] = 0;
        }
    }
    nhap_tram(m, n, supply, demand);

    nhap_chi_phi(m, n, cost);

    int visited[MAX][MAX];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            visited[i][j] = 0;
        }
    }


}