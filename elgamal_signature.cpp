#include <bits/stdc++.h>
using namespace std;

int mod_pow(int a, int e, int m) {
    int r = 1; a %= m;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

int egcd(int a, int b, int &x, int &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1; int g = egcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
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
    int p = 467, alpha = 2, a = 127;
    int beta = mod_pow(alpha, a, p);
    cout << "Public key (p, alpha, beta): (" << p << ", " << alpha << ", " << beta << ")\n";
    cout << "Private key a = " << a << "\n";

    int M;
    cout << "Enter message (integer): ";
    cin >> M;

    int r = 5;
    if (__gcd(r, p - 1) != 1) {
        cout << "r not coprime to p-1\n";
        return 0;
    }

    int y1 = mod_pow(alpha, r, p);
    int r_inv = modinv(r, p - 1);
    int y2 = (r_inv * (M - a * y1)) % (p - 1);
    if (y2 < 0) y2 += (p - 1);

    cout << "Signature (y1, y2) = (" << y1 << ", " << y2 << ")\n";

    int left = mod_pow(alpha, M, p);
    int right = (__int128)mod_pow(beta, y1, p) * mod_pow(y1, y2, p) % p;

    cout << (left == right ? "Signature VALID\n" : " Signature INVALID\n");
}