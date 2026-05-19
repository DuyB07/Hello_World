#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAX_SOL 100
#define INF 9999999

int soKho = 0, soCT = 0;
int supply[MAX];
int demand[MAX];
int distance[MAX][MAX];

int allocation[MAX][MAX];
int basic[MAX][MAX]; // Ðánh d?u ô co b?n trong phuong pháp th? v?
int visited[MAX][MAX];
int path_r[MAX * MAX], path_c[MAX * MAX];
int cycle_len;

int min_distance = INF;
int optimal_count = 0;
int optimal_matrices[MAX_SOL][MAX][MAX];
int tempSoKho, tempSoCT;
int tempSupply[MAX], tempDemand[MAX], tempDistance[MAX][MAX];

// --- CÁC HÀM KHAI BÁO ---
void hienThiMenu();
void nhapToanBoDuLieu();
void chinhSuaDuLieu();
void docGiaTriKhoangCach(int *val);
void giaiBaiToan();
int find_cycle(int r, int c, int target_r, int target_c, int dir, int depth);
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

// Hàm d?c d? li?u ch?p nh?n "inf" / "infinity"
void docGiaTriKhoangCach(int *val) {
    char buffer[50];
    scanf("%s", buffer);
    char lower_buf[50];
    int i;
    for (i = 0; buffer[i]; i++) {
        lower_buf[i] = tolower((unsigned char)buffer[i]);
    }
    lower_buf[i] = '\0';
    
    if (strcmp(lower_buf, "inf") == 0 || strcmp(lower_buf, "infinity") == 0) {
        *val = INF;
    } else {
        *val = atoi(buffer);
    }
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

    printf("\n3. Nhap MA TRAN KHOANG CACH (Nhap so hoac 'inf'/'infinity'):\n");
    for (int i = 0; i < soKho; i++) {
        for (int j = 0; j < soCT; j++) {
            printf(" - Khoang cach (Chi phi) tu Kho %d den CT %d: ", i + 1, j + 1);
            docGiaTriKhoangCach(&distance[i][j]);
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

        int id1, id2;
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
                    printf("Khoang cach (Chi phi) moi (So hoac inf): ");
                    docGiaTriKhoangCach(&distance[id1-1][id2-1]);
                }
                break;
        }
    } while (luaChonSua != 4);
}

// Thu?t toán tìm vòng (Cycle Detection) cho Phuong pháp th? v?
int find_cycle(int r, int c, int target_r, int target_c, int dir, int depth) {
    if (dir == 0) { // Tìm theo chi?u ngang
        for (int j = 0; j < tempSoCT; j++) {
            if (j != c && (basic[r][j] || (r == target_r && j == target_c))) {
                if (r == target_r && j == target_c && depth >= 3) {
                    cycle_len = depth;
                    return 1;
                }
                if (!visited[r][j]) {
                    visited[r][j] = 1;
                    path_r[depth] = r; path_c[depth] = j;
                    if (find_cycle(r, j, target_r, target_c, 1, depth + 1)) return 1;
                    visited[r][j] = 0;
                }
            }
        }
    } else { // Tìm theo chi?u d?c
        for (int i = 0; i < tempSoKho; i++) {
            if (i != r && (basic[i][c] || (i == target_r && c == target_c))) {
                if (i == target_r && c == target_c && depth >= 3) {
                    cycle_len = depth;
                    return 1;
                }
                if (!visited[i][c]) {
                    visited[i][c] = 1;
                    path_r[depth] = i; path_c[depth] = c;
                    if (find_cycle(i, c, target_r, target_c, 0, depth + 1)) return 1;
                    visited[i][c] = 0;
                }
            }
        }
    }
    return 0;
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
        for (int i = 0; i < tempSoKho; i++) tempDistance[i][tempSoCT] = 0;
        tempSoCT++;
        printf("\n[*] Tong Cung > Tong Cau. Da them 1 Cong truong gia.\n");
    } 
    else if (tongCau > tongCung) {
        tempSupply[tempSoKho] = tongCau - tongCung;
        for (int j = 0; j < tempSoCT; j++) tempDistance[tempSoKho][j] = 0;
        tempSoKho++;
        printf("\n[*] Tong Cau > Tong Cung. Da them 1 Kho gia.\n");
    }

    for (int i = 0; i < tempSoKho; i++) {
        for (int j = 0; j < tempSoCT; j++) {
            allocation[i][j] = 0;
            basic[i][j] = 0;
        }
    }

    // --- BU?C 1: Tìm phuong án co b?n ban d?u (Cu?c phí bé nh?t) ---
    int tSupply[MAX], tDemand[MAX];
    for(int i=0; i<tempSoKho; i++) tSupply[i] = tempSupply[i];
    for(int j=0; j<tempSoCT; j++) tDemand[j] = tempDemand[j];
    
    int row_done[MAX] = {0}, col_done[MAX] = {0};
    int num_basic = 0;
    
    while (num_basic < tempSoKho + tempSoCT - 1) {
        int min_c = INF + 1, min_i = -1, min_j = -1;
        for(int i=0; i<tempSoKho; i++) {
            if (row_done[i]) continue;
            for(int j=0; j<tempSoCT; j++) {
                if (col_done[j]) continue;
                if (tempDistance[i][j] < min_c) {
                    min_c = tempDistance[i][j];
                    min_i = i; min_j = j;
                }
            }
        }
        
        if (min_i == -1) break; 
        
        int qty = tSupply[min_i] < tDemand[min_j] ? tSupply[min_i] : tDemand[min_j];
        allocation[min_i][min_j] = qty;
        basic[min_i][min_j] = 1;
        num_basic++;
        
        tSupply[min_i] -= qty;
        tDemand[min_j] -= qty;
        
        // Tránh xóa d?ng th?i hàng và c?t (Ch?ng suy bi?n)
        if (tSupply[min_i] == 0 && !row_done[min_i]) {
            row_done[min_i] = 1;
        } else if (tDemand[min_j] == 0 && !col_done[min_j]) {
            col_done[min_j] = 1;
        }
    }

    // --- BU?C 2: Vòng l?p Phuong pháp Th? v? (MODI) ---
    int iter = 0;
    while (iter++ < 100) { 
        int u[MAX], v[MAX];
        int u_def[MAX] = {0}, v_def[MAX] = {0};
        
        u[0] = 0; u_def[0] = 1;
        int changed = 1;
        
        // Tính U_i, V_j
        while(changed) {
            changed = 0;
            for(int i=0; i<tempSoKho; i++) {
                for(int j=0; j<tempSoCT; j++) {
                    if (basic[i][j]) {
                        if (u_def[i] && !v_def[j]) {
                            v[j] = tempDistance[i][j] - u[i];
                            v_def[j] = 1;
                            changed = 1;
                        } else if (!u_def[i] && v_def[j]) {
                            u[i] = tempDistance[i][j] - v[j];
                            u_def[i] = 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
        
        // Ki?m tra di?u ki?n t?i uu d_ij = c_ij - (U_i + V_j)
        int max_neg_d = 0;
        int enter_i = -1, enter_j = -1;
        for(int i=0; i<tempSoKho; i++) {
            for(int j=0; j<tempSoCT; j++) {
                if (!basic[i][j] && tempDistance[i][j] != INF) {
                    if(u_def[i] && v_def[j]) {
                        int d = tempDistance[i][j] - (u[i] + v[j]);
                        if (d < max_neg_d) {
                            max_neg_d = d;
                            enter_i = i;
                            enter_j = j;
                        }
                    }
                }
            }
        }
        
        if (enter_i == -1) break; // Khong con d_ij am => Da dat toi uu
        
        // Tìm vòng (Cycle) d? di?u ch?nh lu?ng hàng
        for(int i=0; i<tempSoKho; i++) for(int j=0; j<tempSoCT; j++) visited[i][j] = 0;
        cycle_len = 0;
        path_r[0] = enter_i; path_c[0] = enter_j;
        visited[enter_i][enter_j] = 1;
        
        if (!find_cycle(enter_i, enter_j, enter_i, enter_j, 0, 1)) {
            for(int i=0; i<tempSoKho; i++) for(int j=0; j<tempSoCT; j++) visited[i][j] = 0;
            visited[enter_i][enter_j] = 1;
            find_cycle(enter_i, enter_j, enter_i, enter_j, 1, 1);
        }
        
        if (cycle_len == 0) break; // An toan tranh loop vo han
        
        int min_theta = INF;
        int min_idx = -1;
        for (int k = 1; k < cycle_len; k += 2) {
            int r = path_r[k], c = path_c[k];
            if (allocation[r][c] < min_theta) {
                min_theta = allocation[r][c];
                min_idx = k;
            }
        }
        
        for (int k = 0; k < cycle_len; k++) {
            int r = path_r[k], c = path_c[k];
            if (k % 2 == 0) allocation[r][c] += min_theta;
            else allocation[r][c] -= min_theta;
        }
        
        basic[enter_i][enter_j] = 1;
        basic[path_r[min_idx]][path_c[min_idx]] = 0;
    }

    // --- BU?C 3: Luu l?i k?t qu? t?i uu cu?i cùng ---
    min_distance = 0;
    for(int i=0; i<tempSoKho; i++) {
        for(int j=0; j<tempSoCT; j++) {
            optimal_matrices[0][i][j] = allocation[i][j];
            if (basic[i][j]) {
                min_distance += allocation[i][j] * tempDistance[i][j];
            }
        }
    }
    optimal_count = 1; // MODI thong thuong tra ve 1 phuong an toi uu nhat
    inKetQua();
}

void inKetQua() {
    if (optimal_count == 0) {
        printf("\n[!] Khong tim thay phuong an phan bo nao hop le.\n");
        return;
    }

    printf("\n=========================================\n");
    printf(" >> TONG KHOANG CACH TOI THIEU: %d\n", min_distance);
    printf(" >> Da ap dung toi uu bang Phuong phap the vi.\n");
    printf("=========================================\n");

    for (int k = 0; k < optimal_count; k++) {
        printf("\n--- MA TRAN TOI UU #%d ---\n", k + 1);
        
        printf("        ");
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