#include <bits/stdc++.h>
using namespace std;

int egcd(int a, int b, int &x, int &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1; int g = egcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

int mod_pow(int a, int e, int m) {
    int r = 1; a %= m;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

int modinv(int a, int m) {
    int x, y;
    int g = egcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {
    int p = 467, alpha = 2, a = 123;
    int beta = mod_pow(alpha, a, p);
    cout << "Public (p, alpha, beta): (" << p << "," << alpha << "," << beta << ")\n";
    cout << "Private a = " << a << "\n";

    int m1 = 5, m2 = 10;
    int r1 = 7, r2 = 11;

    int C11 = mod_pow(alpha, r1, p);
    int C12 = (m1 * mod_pow(beta, r1, p)) % p;

    int C21 = mod_pow(alpha, r2, p);
    int C22 = (m2 * mod_pow(beta, r2, p)) % p;

    // int C1p = (C11 * C21) % p;
    // int C2p = (C12 * C22) % p;
     int C1p= mod_pow(alpha,r1+r2,p);
     int C2p= ((m1*m2)*mod_pow(beta,r1+r2,p))%p;

    cout << "Combined Cipher (C1', C2') = (" << C1p << "," << C2p << ")\n";

    int s = mod_pow(C1p, a, p);
    int s_inv = modinv(s, p);
    int m_dec = (C2p * s_inv) % p;

    cout << "Decrypted m' = " << m_dec << "  Expected = " << (m1 * m2) % p << "\n";
}