#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define MAX_SOL 100
#define INF 9999999

int soKho = 0, soCT = 0;
int supply[MAX];
int demand[MAX];
int distance[MAX][MAX];

int allocation[MAX][MAX];
int min_distance = INF;
int optimal_count = 0;
int optimal_matrices[MAX_SOL][MAX][MAX];
int tempSoKho, tempSoCT;
int tempSupply[MAX], tempDemand[MAX], tempDistance[MAX][MAX];

void hienThiMenu();
void nhapToanBoDuLieu();
void chinhSuaDuLieu();
void giaiBaiToan();
void Try(int i, int j, int current_cost);
void luuMaTranToiUu(int current_cost);
void inKetQua();

int main() {
    int luaChon;
    int daCoDuLieu = 0;

    do {
        hienThiMenu();
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                nhapToanBoDuLieu();
                daCoDuLieu = 1;
                break;
            case 2:
                if (daCoDuLieu) chinhSuaDuLieu();
                else printf("\n[!] Vui long nhap du lieu truoc!\n");
                break;
            case 3:
                if (daCoDuLieu) giaiBaiToan();
                else printf("\n[!] Khong co du lieu de giai bai toan!\n");
                break;
            case 4:
                printf("\nCam on ban da su dung chuong trinh!\n");
                break;
            default:
                printf("\n[!] Lua chon khong hop le!\n");
        }
    } while (luaChon != 4);

    return 0;
}

void hienThiMenu() {
    printf("\n=========================================\n");
    printf("   CHUONG TRINH GIAI BAI TOAN VAN TAI\n");
    printf("=========================================\n");
    printf("1. Nhap toan bo du lieu moi\n");
    printf("2. Chinh sua mot phan du lieu hien tai\n");
    printf("3. Giai bai toan\n");
    printf("4. Thoat chuong trinh\n");
    printf("=========================================\n");
}

void nhapToanBoDuLieu() {
    printf("\n--- NHAP DU LIEU MOI ---\n");
    printf("Nhap so luong Kho: "); scanf("%d", &soKho);
    printf("Nhap so luong Cong truong (CT): "); scanf("%d", &soCT);

    printf("\n1. Nhap luong CUNG tai cac Kho:\n");
    for (int i = 0; i < soKho; i++) {
        printf(" - Kho %d: ", i + 1);
        scanf("%d", &supply[i]);
    }

    printf("\n2. Nhap luong CAU tai cac Cong truong:\n");
    for (int j = 0; j < soCT; j++) {
        printf(" - Cong truong %d: ", j + 1);
        scanf("%d", &demand[j]);
    }

    printf("\n3. Nhap MA TRAN KHOANG CACH (Kho x CT):\n");
    for (int i = 0; i < soKho; i++) {
        for (int j = 0; j < soCT; j++) {
            printf(" - Khoang cach (Chi phi) tu Kho %d den CT %d: ", i + 1, j + 1);
            scanf("%d", &distance[i][j]);
        }
    }
    printf("\n[v] Da nhap du lieu thanh cong!\n");
}

void chinhSuaDuLieu() {
    int luaChonSua;
    do {
        printf("\n--- CHINH SUA DU LIEU ---\n");
        printf("1. Sua luong CUNG cua mot Kho\n");
        printf("2. Sua luong CAU cua mot Cong truong\n");
        printf("3. Sua KHOANG CACH van chuyen\n");
        printf("4. Quay lai man hinh chinh\n");
        printf("Chon muc can sua: ");
        scanf("%d", &luaChonSua);

        int id1, id2, giaTriMoi;
        switch (luaChonSua) {
            case 1:
                printf("Sua Kho so (1-%d): ", soKho); scanf("%d", &id1);
                if(id1 >= 1 && id1 <= soKho) {
                    printf("Moi nhap lai: "); scanf("%d", &supply[id1-1]);
                }
                break;
            case 2:
                printf("Sua CT so (1-%d): ", soCT); scanf("%d", &id1);
                if(id1 >= 1 && id1 <= soCT) {
                    printf("Moi nhap lai: "); scanf("%d", &demand[id1-1]);
                }
                break;
            case 3:
                printf("Nhap Kho (1-%d) va CT (1-%d): ", soKho, soCT); 
                scanf("%d %d", &id1, &id2);
                if(id1 >= 1 && id1 <= soKho && id2 >= 1 && id2 <= soCT) {
                    printf("Khoang cach (Chi phi) moi: "); scanf("%d", &distance[id1-1][id2-1]);
                }
                break;
        }
    } while (luaChonSua != 4);
}

void luuMaTranToiUu(int current_distance) {
    if (current_distance < min_distance) {
        min_distance = current_distance;
        optimal_count = 0; 
    }
    
    if (current_distance == min_distance && optimal_count < MAX_SOL) {
        for (int i = 0; i < tempSoKho; i++) {
            for (int j = 0; j < tempSoCT; j++) {
                optimal_matrices[optimal_count][i][j] = allocation[i][j];
            }
        }
        optimal_count++;
    }
}

void Try(int i, int j, int current_distance) {
    if (current_distance > min_distance) return;

    if (i == tempSoKho) {
        for (int c = 0; c < tempSoCT; c++) {
            if (tempDemand[c] > 0) return; 
        }
        luuMaTranToiUu(current_distance);
        return;
    }

    int next_i = i, next_j = j + 1;
    if (next_j == tempSoCT) {
        next_i = i + 1;
        next_j = 0;
    }

    int max_val = tempSupply[i] < tempDemand[j] ? tempSupply[i] : tempDemand[j];
    int min_val = 0;

    if (j == tempSoCT - 1) {
        if (tempSupply[i] > tempDemand[j]) return; 
        min_val = max_val = tempSupply[i];
    }
    if (i == tempSoKho - 1) {
        if (tempDemand[j] > tempSupply[i]) return;
        min_val = max_val = tempDemand[j];
    }

    for (int val = min_val; val <= max_val; val++) {
        allocation[i][j] = val;
        tempSupply[i] -= val;
        tempDemand[j] -= val;
        
        Try(next_i, next_j, current_distance + val * tempDistance[i][j]);
        
        tempSupply[i] += val;
        tempDemand[j] += val;
    }
}

void giaiBaiToan() {
    int tongCung = 0, tongCau = 0;
    tempSoKho = soKho;
    tempSoCT = soCT;

    for (int i = 0; i < soKho; i++) {
        tempSupply[i] = supply[i];
        tongCung += supply[i];
    }
    for (int j = 0; j < soCT; j++) {
        tempDemand[j] = demand[j];
        tongCau += demand[j];
    }
    for (int i = 0; i < soKho; i++) {
        for (int j = 0; j < soCT; j++) tempDistance[i][j] = distance[i][j];
    }

    if (tongCung > tongCau) {
        tempDemand[tempSoCT] = tongCung - tongCau;
        for (int i = 0; i < tempSoKho; i++) {
            tempDistance[i][tempSoCT] = 0;
        }
        tempSoCT++;
        printf("\n[*] Tong Cung > Tong Cau. Da them 1 Cong truong gia.\n");
    } 
    else if (tongCau > tongCung) {
        tempSupply[tempSoKho] = tongCau - tongCung;
        for (int j = 0; j < tempSoCT; j++) {
            tempDistance[tempSoKho][j] = 0;
        }
        tempSoKho++;
        printf("\n[*] Tong Cau > Tong Cung. Da them 1 Kho gia.\n");
    }

    min_distance = INF;
    optimal_count = 0;
    Try(0, 0, 0);
    inKetQua();
}

void inKetQua() {
    if (optimal_count == 0) {
        printf("\n[!] Khong tim thay phuong an phan bo nao hop le.\n");
        return;
    }

    printf("\n=========================================\n");
    printf(" >> TONG KHOANG CACH TOI THIEU: %d\n", min_distance);
    if (optimal_count > 1) {
        printf(" >> [!] PHAT HIEN %d MA TRAN TOI UU\n", optimal_count);
    } else {
        printf(" >> Co 1 phuong an toi uu duy nhat.\n");
    }
    printf("=========================================\n");

    for (int k = 0; k < optimal_count; k++) {
        printf("\n--- MA TRAN TOI UU #%d ---\n", k + 1);
        
        printf("       ");
        for (int j = 0; j < tempSoCT; j++) {
            if (j >= soCT) printf("  CT.Gia");
            else printf("   CT%-2d ", j + 1);
        }
        printf("\n       +");
        for (int j = 0; j < tempSoCT; j++) printf("-------+");
        printf("\n");

        for (int i = 0; i < tempSoKho; i++) {
            if (i >= soKho) printf(" K.Gia |");
            else printf(" Kho %d |", i + 1);
            
            for (int j = 0; j < tempSoCT; j++) {
                printf(" %5d |", optimal_matrices[k][i][j]);
            }
            printf("\n       +");
            for (int j = 0; j < tempSoCT; j++) printf("-------+");
            printf("\n");
        }
    }
}