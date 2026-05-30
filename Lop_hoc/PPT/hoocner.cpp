#include <bits/stdc++.h>
 
using namespace std;
 
// =====================================================================
// HAM HO TRO IN DA THUC DEP MAT
// =====================================================================
void InDaThuc(const vector<double>& a, int n, string var) {
    bool first = true;
    for (int i = 0; i <= n; ++i) {
        if (a[i] == 0) continue;
 
        if (!first && a[i] > 0) cout << " + ";
        else if (a[i] < 0) {
            if (first) cout << "-";
            else cout << " - ";
        }
 
        double val = abs(a[i]);
        int power = n - i;
 
        if (val != 1 || power == 0) cout << val;
 
        if (power > 0) {
            cout << var;
            if (power > 1) cout << "^" << power;
        }
        first = false;
    }
    if (first) cout << "0";
}
 
// =====================================================================
// BÀI 3: TÍNH GIÁ TRỊ ĐA THỨC BẰNG SƠ ĐỒ HOOCNER (CƠ BẢN)
// =====================================================================
void TinhGiaTriHoocner(const vector<double>& a, int n, double c) {
    vector<double> b(n + 1);
 
    // b_0 = a_0
    b[0] = a[0];
 
    // Cong thuc Hoocner: b_i = a_i + c * b_{i-1}
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] + c * b[i - 1];
    }
 
    // In bang ket qua
    int width = 12;
    int total_width = 15 + (n + 1) * (width + 3);
 
    cout << "\n[BANG KET QUA SO DO HOOCNER TINH P(c)]\n";
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    // Dong 1: He so a
    cout << left << setw(12) << "He so a_i";
    for (int i = 0; i <= n; i++) cout << " | " << setw(width) << fixed << setprecision(3) << a[i];
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    // Dong 2: He so b
    cout << left << "c = " << setw(8) << defaultfloat << c;
    for (int i = 0; i <= n; i++) cout << " | " << setw(width) << fixed << setprecision(3) << b[i];
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << "=> Gia tri cua da thuc tai x = " << defaultfloat << c << " la: P(" << c << ") = " << fixed << setprecision(3) << b[n] << endl;
}
 
// =====================================================================
// BÀI 6: TÌM HỆ SỐ ĐA THỨC P(y+c) BẰNG SƠ ĐỒ HOOCNER TỔNG QUÁT
// =====================================================================
void HoocnerTongQuat(const vector<double>& a, int n, double c) {
    vector<vector<double>> rows;
    vector<double> temp = a;
    vector<double> A(n + 1); // Mang luu cac he so moi A_0, A_1, ..., A_n
 
    rows.push_back(temp); // Dong 0: Cac he so ban dau
    A[0] = a[0];          // He so bac cao nhat khong doi
 
    // Thuc hien thuat toan Hoocner tong quat
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n - k + 1; ++i) {
            temp[i] = temp[i] + c * temp[i - 1];
        }
        rows.push_back(temp);
        A[n - k + 1] = temp[n - k + 1]; // Luu lai he so A_i tim duoc
    }
 
    // In bang ket qua (In theo kieu tam giac)
    int width = 12;
    int total_width = 15 + (n + 1) * (width + 3) + 20;
 
    cout << "\n[BANG KET QUA SO DO HOOCNER TONG QUAT TIM P(y+c)]\n";
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    // Tieu de cot
    cout << left << setw(12) << ("c = " + to_string(c).substr(0, 4));
    for (int i = 0; i <= n; i++) cout << " | a" << left << setw(width-1) << i;
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    // In cac buoc lap
    for (int k = 0; k <= n; k++) {
        cout << left << setw(12) << (k == 0 ? "Ban dau" : "Lan " + to_string(k));
        for (int i = 0; i <= n; i++) {
            if (i <= n - k) {
                cout << " | " << setw(width) << fixed << setprecision(3) << rows[k][i];
            } else {
                cout << " | " << setw(width) << " "; // In khoang trang tao hinh tam giac
            }
        }
        if (k > 0) cout << "  => A_" << n - k + 1 << " = " << rows[k][n - k + 1];
        cout << endl;
    }
 
    // In ket luan A_0
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
    cout << left << setw(12) << "Chot A_0";
    cout << " | " << setw(width) << fixed << setprecision(3) << rows[n][0];
    for (int i = 1; i <= n; i++) cout << " | " << setw(width) << " ";
    cout << "  => A_0 = " << rows[n][0] << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    // In bieu dien da thuc cuoi cung
    cout << "\n=> P(x) ban dau = "; InDaThuc(a, n, "x"); cout << endl;
    cout << "=> Da thuc P(y + " << defaultfloat << c << ") = "; InDaThuc(A, n, "y"); cout << endl;
}
 
// =====================================================================
// CHUONG TRINH CHINH
// =====================================================================
int main() {
    char tieptuc;
    int lua_chon, n;
    double c;
 
    do {
    	system("cls");
        cout << "\n=======================================================\n";
        cout << "            CHUONG TRINH TINH SO DO HOOCNER            \n";
        cout << "=======================================================\n";
        cout << "1. Tinh gia tri da thuc P(c) theo so do Hoocner\n";
        cout << "2. Xac dinh he so da thuc P(y+c) theo Hoocner tong quat\n";
        cout << "-------------------------------------------------------\n";
        cout << "=> Chon tinh nang (1 hoac 2): ";
        cin >> lua_chon;
 
        if (lua_chon != 1 && lua_chon != 2) {
            cout << "=> Lua chon khong hop le!\n";
            continue;
        }
 
        // Nhap du lieu dau vao (dung chung cho ca 2 bai)
        cout << "\n--- NHAP THONG TIN DA THUC ---\n";
        cout << "=> Nhap bac cua da thuc n = ";
        cin >> n;
 
        vector<double> a(n + 1);
        cout << "=> Nhap cac he so tu a_0 den a_" << n << " (voi a_0 la he so cua x^" << n << "):\n";
        for (int i = 0; i <= n; i++) {
            cout << "   a[" << i << "] = ";
            cin >> a[i];
        }
 
        cout << "=> Nhap gia tri c = ";
        cin >> c;
 
        // Thuc thi
        if (lua_chon == 1) {
            TinhGiaTriHoocner(a, n, c);
        } else {
            HoocnerTongQuat(a, n, c);
        }
 
        cout << "\n=======================================================\n";
        cout << "Tiep tuc voi da thuc khac? (Y/N): ";
        cin >> tieptuc;
 
    } while (tieptuc == 'Y' || tieptuc == 'y');
 
    cout << "\nChuong trinh ket thuc.\n";
    return 0;
}