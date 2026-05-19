#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 50
#define INF 1e9

// --- Cấu trúc dữ liệu ---
typedef struct {
    int m, n;
    int supply[MAX], demand[MAX];
    int cost[MAX][MAX];
    int alloc[MAX][MAX];
    bool is_basic[MAX][MAX];
    int u[MAX], v[MAX];
} TransportData;

// Biến hỗ trợ tìm chu trình
int path[MAX * MAX][2];
int path_len;
bool found_loop;

// --- GIAO DIỆN & TIÊU ĐỀ ---
void print_header() {
    printf("\033[1;32m"); // Đổi màu xanh lá
    printf("==============================================================\n");
    printf("      DO AN PBL: TOI UU HOA - GIAI BAI TOAN VAN TAI         \n");
    printf("           THUAT TOAN THE VI (MODI METHOD)                  \n");
    printf("==============================================================\n");
    printf("\033[0m"); // Reset màu
}

// --- HÀM NHẬP DỮ LIỆU ---
void input_manual(TransportData *td) {
    printf("\n[NHAP DU LIEU TU BAN PHIM]\n");
    printf("Nhap so kho hang (m): "); scanf("%d", &td->m);
    printf("Nhap so cong truong (n): "); scanf("%d", &td->n);
    
    printf("Nhap luong cung tung kho: ");
    for (int i = 0; i < td->m; i++) scanf("%d", &td->supply[i]);
    
    printf("Nhap luong cau tung cong truong: ");
    for (int j = 0; j < td->n; j++) scanf("%d", &td->demand[j]);
    
    printf("Nhap ma tran chi phi cuoc phi:\n");
    for (int i = 0; i < td->m; i++) {
        for (int j = 0; j < td->n; j++) {
            printf("Cost[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &td->cost[i][j]);
        }
    }
}

void input_file(TransportData *td) {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        printf("\033[1;31m[LOI] Khong tim thay file input.txt!\033[0m\n");
        return;
    }
    fscanf(f, "%d %d", &td->m, &td->n);
    for (int i = 0; i < td->m; i++) fscanf(f, "%d", &td->supply[i]);
    for (int j = 0; j < td->n; j++) fscanf(f, "%d", &td->demand[j]);
    for (int i = 0; i < td->m; i++)
        for (int j = 0; j < td->n; j++)
            fscanf(f, "%d", &td->cost[i][j]);
    fclose(f);
    printf("\n\033[1;34m[OK] Da nap du lieu tu file input.txt thanh cong!\033[0m\n");
}

// --- THUẬT TOÁN TÌM CHU TRÌNH (LOOP DFS) ---
bool find_loop(TransportData *td, int r, int c, int target_r, int target_c, bool move_row, int depth) {
    if (depth > 3 && r == target_r && c == target_c) {
        path_len = depth;
        return true;
    }
    if (move_row) {
        for (int nc = 0; nc < td->n; nc++) {
            if (nc != c && (td->is_basic[r][nc] || (r == target_r && nc == target_c))) {
                path[depth][0] = r; path[depth][1] = nc;
                if (find_loop(td, r, nc, target_r, target_c, false, depth + 1)) return true;
            }
        }
    } else {
        for (int nr = 0; nr < td->m; nr++) {
            if (nr != r && (td->is_basic[nr][c] || (nr == target_r && c == target_c))) {
                path[depth][0] = nr; path[depth][1] = c;
                if (find_loop(td, nr, c, target_r, target_c, true, depth + 1)) return true;
            }
        }
    }
    return false;
}

// --- THUẬT TOÁN GIẢI CHI TIẾT ---
void solve_transport(TransportData td) {
    memset(td.alloc, 0, sizeof(td.alloc));
    memset(td.is_basic, false, sizeof(td.is_basic));
    int s[MAX], d[MAX];
    memcpy(s, td.supply, sizeof(s));
    memcpy(d, td.demand, sizeof(d));

    // Bước 1: Khởi tạo bằng Cước phí nhỏ nhất
    int count = 0;
    while (count < td.m + td.n - 1) {
        int min_c = INF, r = -1, c = -1;
        for (int i = 0; i < td.m; i++) {
            for (int j = 0; j < td.n; j++) {
                if (s[i] > 0 || d[j] > 0) {
                    if (!td.is_basic[i][j] && td.cost[i][j] < min_c) {
                        min_c = td.cost[i][j]; r = i; c = j;
                    }
                }
            }
        }
        if (r == -1) break;
        int val = (s[r] < d[c]) ? s[r] : d[c];
        td.alloc[r][c] = val;
        td.is_basic[r][c] = true;
        s[r] -= val; d[c] -= val;
        count++;
    }

    // Bước 2: Vòng lặp tối ưu hóa
    int iter = 0;
    while (iter < 100) {
        int u[MAX], v[MAX];
        bool u_set[MAX] = {0}, v_set[MAX] = {0};
        for(int i=0; i<MAX; i++) u[i] = v[i] = 0;
        u_set[0] = true; // Gán u1 = 0

        for (int k = 0; k < td.m + td.n; k++) {
            for (int i = 0; i < td.m; i++) {
                for (int j = 0; j < td.n; j++) {
                    if (td.is_basic[i][j]) {
                        if (u_set[i] && !v_set[j]) { v[j] = td.cost[i][j] - u[i]; v_set[j] = true; }
                        else if (!u_set[i] && v_set[j]) { u[i] = td.cost[i][j] - v[j]; u_set[i] = true; }
                    }
                }
            }
        }

        int max_delta = -1, row_in = -1, col_in = -1;
        for (int i = 0; i < td.m; i++) {
            for (int j = 0; j < td.n; j++) {
                if (!td.is_basic[i][j]) {
                    int delta = u[i] + v[j] - td.cost[i][j];
                    if (delta > max_delta) { max_delta = delta; row_in = i; col_in = j; }
                }
            }
        }

        if (max_delta <= 0) break; // Phương án đã tối ưu

        // Tìm chu trình điều chỉnh
        path[0][0] = row_in; path[0][1] = col_in;
        if (!find_loop(&td, row_in, col_in, row_in, col_in, true, 1)) break;

        int theta = INF, r_out = -1, c_out = -1;
        for (int i = 1; i < path_len; i += 2) {
            if (td.alloc[path[i][0]][path[i][1]] < theta) {
                theta = td.alloc[path[i][0]][path[i][1]];
                r_out = path[i][0]; c_out = path[i][1];
            }
        }

        for (int i = 0; i < path_len; i++) {
            if (i % 2 == 0) td.alloc[path[i][0]][path[i][1]] += theta;
            else td.alloc[path[i][0]][path[i][1]] -= theta;
        }
        td.is_basic[row_in][col_in] = true;
        td.is_basic[r_out][c_out] = false;
        iter++;
    }

    // Bước 3: In kết quả rực rỡ
    printf("\n\033[1;33m--- KET QUA PHAN PHOI TOI UU ---\033[0m\n");
    long total_cost = 0;
    printf("      ");
    for(int j=0; j<td.n; j++) printf("CT%d\t", j+1);
    printf("\n");
    for (int i = 0; i < td.m; i++) {
        printf("Kho%d: ", i+1);
        for (int j = 0; j < td.n; j++) {
            printf("%d\t", td.alloc[i][j]);
            total_cost += (long)td.alloc[i][j] * td.cost[i][j];
        }
        printf("\n");
    }
    printf("\n\033[1;32m==> TONG CHI PHI VAN TAI THAP NHAT: %ld\033[0m\n", total_cost);
}

// --- HAM MAIN DIEU KHIEN ---
int main() {
    TransportData td;
    int choice;
    bool has_data = false;

    while (1) {
        // system("cls"); // Dung cho Windows để xóa màn hình
        print_header();
        printf("[1]. Nhap du lieu tu ban phim\n");
        printf("[2]. Nhap du lieu tu file (input.txt)\n");
        printf("[3]. Xem va Chinh sua cuoc phi\n");
        printf("[4]. Giai bai toan (Tim phuong an toi uu)\n");
        printf("[0]. Thoat chuong trinh\n");
        printf("--------------------------------------------------------------\n");
        printf("Chon chuc nang (0-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_manual(&td);
                has_data = true;
                break;
            case 2:
                input_file(&td);
                has_data = true;
                break;
            case 3:
                if (!has_data) printf("Chua co du lieu!\n");
                else {
                    int r, c, nc;
                    printf("Nhap hang (kho) va cot (cong truong) can sua: ");
                    scanf("%d %d", &r, &c);
                    printf("Gia tri moi: "); scanf("%d", &nc);
                    td.cost[r-1][c-1] = nc;
                }
                break;
            case 4:
                if (!has_data) printf("Vui long nhap du lieu truoc khi giai!\n");
                else solve_transport(td);
                printf("\nNhan Enter de quay lai Menu...");
                getchar(); getchar();
                break;
            case 0:
                printf("Dang thoat... Tam biet!\n");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
    return 0;
}