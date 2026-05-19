#include <stdio.h>

#define MAX 20
#define can_bang 0
#define khong_can_bang 1
#define INF 1e9

void nhap_tram(int m, int n, int supply[], int demand[])
{
    for (int i = 1; i <= m; i++)
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

    for (int j = 1; j <= n; j++)
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
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
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

void least_cost_method(int m, int n, int supply[], int demand[], int cost[][MAX], int allocation[][MAX]){
    while(1){
        int minCost = INF;
        int row = -1, column = -1;

        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
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

        supply[row] -= x;
        demand[column] -= x;
    }
}

int xet_tinh_suy_bien(int m, int n, int allocation[][MAX]){
    
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
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            allocation[i][j] = 0;
        }
    }

    nhap_tram(m, n, supply, demand);

    nhap_chi_phi(m, n, cost);
}