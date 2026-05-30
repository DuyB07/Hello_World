#include <bits/stdc++.h>
 
using namespace std;
 
// Dinh nghia sai so theo yeu cau de bai
const double EPSILON = 1e-3;
 
// Bien toan cuc de luu tru he so cho phuong trinh tu nhap (Option 17)
vector<double> custom_coeffs;
 
// =====================================================================
// PHAN 1: CAC HAM CHO MENU GIAI PHUONG TRINH (TIM NGHIEM)
// =====================================================================
 
double f(int id, double x) {
    if (id == 17) {
        // Tinh gia tri da thuc bang so do Horner cho phuong trinh tu nhap
        double res = custom_coeffs[0];
        for (int i = 1; i < (int)custom_coeffs.size(); ++i) {
            res = res * x + custom_coeffs[i];
        }
        return res;
    }
 
    switch(id) {
        case 1: return pow(x, 3) - x + 5;           // 1a
        case 2: return pow(x, 3) - x - 1;           // 1b
        case 3: return sin(x) - x + 0.25;           // 1c
        case 4: return pow(x, 4) - 4*x - 1;         // 1d
        case 5: return pow(x, 3) + x - 5;           // 1e
        case 6: return exp(x) + x - 2;              // 1f
        case 7: return exp(x) - 10*x + 7;           // 2a
        case 8: return pow(2, x) + x - 4;           // 2c
        case 9: return exp(x) + x + 1;              // 2d
        case 10: return pow(x, 3) + 5*x - 2;        // 3a
        case 11: return pow(2, x) + x - 5;          // 3b
        case 12: return cos(2*x) + x - 5;           // 3c
        case 13: return log(x) + x + 1;             // 3d
        case 14: return pow(x, 3) - x - 1000;       // Bai 4
        case 15: return pow(x, 3) + pow(x, 2) - 2*x - 5; // Bai 5
        case 16: return pow(x, 4) - 3*pow(x, 2) + 75*x - 1000; // Bai 6
        default: return 0;
    }
}
 
double df(int id, double x) {
    if (id == 17) {
        // Tu dong tinh dao ham cua da thuc tu nhap
        int n = (int)custom_coeffs.size() - 1;
        if (n <= 0) return 0;
        double res = custom_coeffs[0] * n;
        for (int i = 1; i < n; ++i) {
            res = res * x + custom_coeffs[i] * (n - i);
        }
        return res;
    }
 
    switch(id) {
        case 1: return 3*pow(x, 2) - 1;
        case 2: return 3*pow(x, 2) - 1;
        case 3: return cos(x) - 1;
        case 4: return 4*pow(x, 3) - 4;
        case 5: return 3*pow(x, 2) + 1;
        case 6: return exp(x) + 1;
        case 7: return exp(x) - 10;
        case 8: return pow(2, x)*log(2) + 1;
        case 9: return exp(x) + 1;
        case 10: return 3*pow(x, 2) + 5;
        case 11: return pow(2, x)*log(2) + 1;
        case 12: return -2*sin(2*x) + 1;
        case 13: return 1.0/x + 1;
        case 14: return 3*pow(x, 2) - 1;
        case 15: return 3*pow(x, 2) + 2*x - 2;
        case 16: return 4*pow(x, 3) - 6*x + 75;
        default: return 1; 
    }
}
 
double phi(int id, double x) {
    if (id == 17) {
        double d = df(id, x);
        if (abs(d) < 1e-9) return x;
        return x - f(id, x) / d;
    }
    switch(id) {
        case 1: return cbrt(x - 5); 
        case 2: return cbrt(x + 1); 
        case 3: return sin(x) + 0.25;
        case 4: return sqrt(sqrt(4*x + 1));
        case 5: return cbrt(5 - x);
        case 6: return log(2 - x);
        case 7: return (exp(x) + 7) / 10.0;
        case 8: return log2(4 - x);
        case 9: return -exp(x) - 1;
        case 10: return cbrt(2 - 5*x);
        case 11: return log2(5 - x);
        case 12: return 5 - cos(2*x);
        case 13: return exp(-x - 1);
        case 14: return cbrt(x + 1000); 
        case 15: return cbrt(5 + 2*x - x*x);
        case 16: return sqrt(sqrt(3*x*x - 75*x + 1000));
        default: return x;
    }
}
 
string getPhiStr(int id) {
    if (id == 17) return "x - f(x)/f'(x)";
    switch(id) {
        case 1: return "cbrt(x - 5)"; 
        case 2: return "cbrt(x + 1)"; 
        case 3: return "sin(x) + 0.25";
        case 4: return "(4x + 1)^(1/4)";
        case 5: return "cbrt(5 - x)";
        case 6: return "ln(2 - x)";
        case 7: return "(e^x + 7) / 10";
        case 8: return "log2(4 - x)";
        case 9: return "-e^x - 1";
        case 10: return "cbrt(2 - 5*x)";
        case 11: return "log2(5 - x)";
        case 12: return "5 - cos(2*x)";
        case 13: return "e^(-x - 1)";
        case 14: return "cbrt(x + 1000)"; 
        case 15: return "cbrt(5 + 2*x - x*x)";
        case 16: return "(3x^2 - 75x + 1000)^(1/4)";
    }
}
 
void PhuongPhapChiaDoi(int id, double a, double b) {
    if (f(id, a) * f(id, b) > 0) {
        cout << "=> Loi: f(a) va f(b) cung dau. Khong phan ly duoc nghiem!\n";
        return;
    }
    cout << "\n[BANG KET QUA PHUONG PHAP CHIA DOI]\n";
    cout << string(60, '-') << endl;
    cout << setw(5) << "Lap" << setw(12) << "a" << setw(12) << "b" << setw(12) << "c" << setw(15) << "f(c)" << endl;
    cout << string(60, '-') << endl;
    double c; int lap = 0;
    do {
        c = (a + b) / 2.0;
        double fc = f(id, c);
        lap++;
        cout << setw(5) << lap << setw(12) << fixed << setprecision(4) << a << setw(12) << b << setw(12) << c << setw(15) << fc << endl;
        if (f(id, a) * fc <= 0) b = c; else a = c;
    } while (abs(b - a) >= EPSILON && lap < 100);
    cout << string(60, '-') << endl;
    cout << "=> Nghiem gan dung: x = " << fixed << setprecision(4) << c << endl;
}
 
void PhuongPhapDayCung(int id, double a, double b) {
    if (f(id, a) * f(id, b) > 0) {
        cout << "=> Loi: Khoang [" << a << ", " << b << "] khong hop le!\n";
        return;
    }
    cout << "\n[BANG KET QUA PHUONG PHAP DAY CUNG]\n";
    cout << string(60, '-') << endl;
    cout << setw(5) << "Lap" << setw(12) << "a" << setw(12) << "b" << setw(12) << "c" << setw(15) << "f(c)" << endl;
    cout << string(60, '-') << endl;
    double c, c_old = a; int lap = 0;
    do {
        double fa = f(id, a), fb = f(id, b);
        c = (a * fb - b * fa) / (fb - fa);
        lap++;
        cout << setw(5) << lap << setw(12) << fixed << setprecision(4) << a << setw(12) << b << setw(12) << c << setw(15) << f(id, c) << endl;
        if (f(id, a) * f(id, c) <= 0) b = c; else a = c;
        if (abs(c - c_old) < EPSILON) break;
        c_old = c;
    } while (lap < 100);
    cout << string(60, '-') << endl;
    cout << "=> Nghiem gan dung: x = " << fixed << setprecision(4) << c << endl;
}
 
void PhuongPhapTiepTuyen(int id, double x0) {
    cout << "\n[BANG KET QUA PHUONG PHAP TIEP TUYEN]\n";
    cout << string(55, '-') << endl;
    cout << setw(5) << "n" << setw(15) << "xn" << setw(15) << "f(xn)" << setw(15) << "f'(xn)" << endl;
    cout << string(55, '-') << endl;
    double x = x0, x_new; int lap = 0;
    do {
        double fx = f(id, x), dfx = df(id, x);
        if (dfx == 0) { cout << "=> Loi: Dao ham bang 0!\n"; return; }
        x_new = x - fx / dfx;
        lap++;
        cout << setw(5) << lap << setw(15) << fixed << setprecision(4) << x << setw(15) << fx << setw(15) << dfx << endl;
        if (abs(x_new - x) < EPSILON) { x = x_new; break; }
        x = x_new;
    } while (lap < 100);
    cout << string(55, '-') << endl;
    cout << "=> Nghiem gan dung: x = " << fixed << setprecision(4) << x << endl;
}
 
void PhuongPhapLap(int id, double x0) {
    double x = x0, x_new; int lap = 0;
    cout << "\n[BANG KET QUA PHUONG PHAP LAP]\n";
    cout << "--------------------------------------------\n";
    cout << left << setw(15) << "      x" << "|  g(x) = " << getPhiStr(id) << "\n";
    cout << "--------------------------------------------\n";
    do {
        x_new = phi(id, x);
        if (isnan(x_new)) { cout << "=> Loi tinh toan!\n"; return; }
        cout << "  " << left << setw(13) << fixed << setprecision(4) << x << "|  " << fixed << setprecision(4) << x_new << "\n";
        if (abs(x_new - x) <= EPSILON) { x = x_new; break; }
        x = x_new; lap++;
    } while (lap < 100);
    cout << "--------------------------------------------\n";
    cout << "=> Nghiem gan dung: x = " << fixed << setprecision(4) << x << endl;
}
 
 
// =====================================================================
// PHAN 2: CAC HAM CHO MENU SO DO HOOCNER
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
 
void TinhGiaTriHoocner(const vector<double>& a, int n, double c) {
    vector<double> b(n + 1);
    b[0] = a[0];
 
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] + c * b[i - 1];
    }
 
    int width = 12;
    int total_width = 15 + (n + 1) * (width + 3);
 
    cout << "\n[BANG KET QUA SO DO HOOCNER TINH P(c)]\n";
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << left << setw(12) << "He so a_i";
    for (int i = 0; i <= n; i++) cout << " | " << setw(width) << fixed << setprecision(3) << a[i];
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << left << "c = " << setw(8) << defaultfloat << c;
    for (int i = 0; i <= n; i++) cout << " | " << setw(width) << fixed << setprecision(3) << b[i];
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << "=> Gia tri cua da thuc tai x = " << defaultfloat << c << " la: P(" << c << ") = " << fixed << setprecision(3) << b[n] << endl;
}
 
void HoocnerTongQuat(const vector<double>& a, int n, double c) {
    vector<vector<double>> rows;
    vector<double> temp = a;
    vector<double> A(n + 1); 
 
    rows.push_back(temp); 
    A[0] = a[0];          
 
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n - k + 1; ++i) {
            temp[i] = temp[i] + c * temp[i - 1];
        }
        rows.push_back(temp);
        A[n - k + 1] = temp[n - k + 1]; 
    }
 
    int width = 12;
    int total_width = 15 + (n + 1) * (width + 3) + 20;
 
    cout << "\n[BANG KET QUA SO DO HOOCNER TONG QUAT TIM P(y+c)]\n";
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << left << setw(12) << ("c = " + to_string(c).substr(0, 4));
    for (int i = 0; i <= n; i++) cout << " | a" << left << setw(width-1) << i;
    cout << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    for (int k = 0; k <= n; k++) {
        cout << left << setw(12) << (k == 0 ? "Ban dau" : "Lan " + to_string(k));
        for (int i = 0; i <= n; i++) {
            if (i <= n - k) {
                cout << " | " << setw(width) << fixed << setprecision(3) << rows[k][i];
            } else {
                cout << " | " << setw(width) << " "; 
            }
        }
        if (k > 0) cout << "  => A_" << n - k + 1 << " = " << rows[k][n - k + 1];
        cout << endl;
    }
 
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
    cout << left << setw(12) << "Chot A_0";
    cout << " | " << setw(width) << fixed << setprecision(3) << rows[n][0];
    for (int i = 1; i <= n; i++) cout << " | " << setw(width) << " ";
    cout << "  => A_0 = " << rows[n][0] << endl;
    cout << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
 
    cout << "\n=> P(x) ban dau = "; InDaThuc(a, n, "x"); cout << endl;
    cout << "=> Da thuc P(y + " << defaultfloat << c << ") = "; InDaThuc(A, n, "y"); cout << endl;
}
 
// =====================================================================
// CHUONG TRINH CHINH TONG HOP
// =====================================================================
int main() {
    int action = 1; // 1: Ve Menu Chinh, 2: Lap lai Menu Hien Tai, 0: Thoat
    int current_mode = 0;
 
    while (true) {
        // Hien thi Menu Chinh khi action == 1
        if (action == 1) {
            system("cls");
            cout << "\n=======================================================\n";
            cout << "               CHUONG TRINH CUA NHOM 9              \n";
            cout << "=======================================================\n";
            cout << "1. Giai phuong trinh (Tim nghiem theo cac phuong phap)\n";
            cout << "2. So do Hoocner (Tinh gia tri, Hoocner tong quat)\n";
            cout << "0. Thoat chuong trinh\n";
            cout << "-------------------------------------------------------\n";
            cout << "=> Nhap lua chon cua ban (0-2): ";
            cin >> current_mode;
 
            if (current_mode == 0) break;
 
            if (current_mode != 1 && current_mode != 2) {
                cout << "=> Lua chon khong hop le!\n";
                system("pause");
                continue; // Lap lai MENU CHINH
            }
        }
 
        system("cls");
 
        // ==========================================
        // CHE DO 1: GIAI PHUONG TRINH
        // ==========================================
        if (current_mode == 1) {
            cout << "\n=======================================================\n";
            cout << "            CHUONG TRINH GIAI PHUONG TRINH             \n";
            cout << "=======================================================\n";
            cout << "--- DANH SACH CAC PHUONG TRINH ---\n";
            cout << left << setw(32) << "1.  x^3 - x + 5 = 0"          << "9.  e^x + x + 1 = 0\n";
            cout << left << setw(32) << "2.  x^3 - x - 1 = 0"          << "10. x^3 + 5x - 2 = 0\n";
            cout << left << setw(32) << "3.  sin(x) - x + 1/4 = 0"     << "11. 2^x + x - 5 = 0\n";
            cout << left << setw(32) << "4.  x^4 - 4x - 1 = 0"         << "12. cos(2x) + x - 5 = 0\n";
            cout << left << setw(32) << "5.  x^3 + x - 5 = 0"          << "13. ln(x) + x + 1 = 0\n";
            cout << left << setw(32) << "6.  e^x + x - 2 = 0"          << "14. x^3 - x - 1000 = 0\n";
            cout << left << setw(32) << "7.  e^x - 10x + 7 = 0"        << "15. x^3 + x^2 - 2x - 5 = 0\n";
            cout << left << setw(32) << "8.  2^x + x - 4 = 0"          << "16. x^4 - 3x^2 + 75x - 1000 = 0\n";
            cout << "17. Phuong trinh da thuc tong quat\n";
            cout << "-------------------------------------------------------\n";
            cout << "=> Chon phuong trinh can giai (1-17): ";
            int bai_tap; cin >> bai_tap;
 
            if (bai_tap == 17) {
                int n_poly;
                cout << "=> Nhap bac cua da thuc: "; cin >> n_poly;
                custom_coeffs.assign(n_poly + 1, 0);
                cout << "=> Nhap cac he so tu a0 (bac cao nhat) den an (tu do):\n";
                for (int i = 0; i <= n_poly; ++i) {
                    cout << "   a[" << i << "] = "; cin >> custom_coeffs[i];
                }
            } else if (bai_tap < 1 || bai_tap > 16) {
                cout << "=> Lua chon khong hop le!\n";
                goto cuoi_vong_lap;
            }
 
            cout << "\n--- CHON PHUONG PHAP GIAI ---\n";
            cout << "1. Chia doi | 2. Day cung | 3. Tiep tuyen | 4. Lap\n";
            cout << "=> Chon (1-4): ";
            int phuong_phap; cin >> phuong_phap;
 
            if (phuong_phap == 1 || phuong_phap == 2) {
                double a, b;
                cout << "=> Nhap khoang phan ly nghiem [a, b]: "; cin >> a >> b;
                if (phuong_phap == 1) PhuongPhapChiaDoi(bai_tap, a, b);
                else PhuongPhapDayCung(bai_tap, a, b);
            } else if (phuong_phap == 3 || phuong_phap == 4) {
                double x0;
                cout << "=> Nhap diem xap xi dau x0: "; cin >> x0;
                if (phuong_phap == 3) PhuongPhapTiepTuyen(bai_tap, x0);
                else PhuongPhapLap(bai_tap, x0);
            } else {
                cout << "=> Phuong phap khong hop le!\n";
            }
        }
        // ==========================================
        // CHE DO 2: SO DO HOOCNER
        // ==========================================
        else if (current_mode == 2) {
            int lua_chon, n;
            double c;
 
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
                goto cuoi_vong_lap;
            }
 
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
 
            if (lua_chon == 1) {
                TinhGiaTriHoocner(a, n, c);
            } else {
                HoocnerTongQuat(a, n, c);
            }
        }
 
        // ==========================================
        // DIEU HUONG CHUNG SAU KHI TINH TOAN
        // ==========================================
        cuoi_vong_lap:
        cout << "\n=======================================================\n";
        cout << "[1] Quay lai MENU CHINH (De doi sang Hoocner hoac Tim nghiem)\n";
        cout << "[2] Tiep tuc tinh toan trong phan hien tai\n";
        cout << "[0] Thoat chuong trinh\n";
        cout << "=> Nhap lua chon (0-2): ";
        cin >> action;
 
        if (action == 0) break;
    }
 
    cout << "\nChuong trinh ket thuc.\n";
 
    return 0;
}