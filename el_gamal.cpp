#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// Extended Euclidean Algorithm
int64 egcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64 x1, y1;
    int64 g = egcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// Calculate (a^e) mod m
int64 mod_pow(int64 a, int64 e, int64 m) {
    int64 r = 1;
    a %= m;

    while (e) {
        if (e & 1)
            r = (__int128)r * a % m;

        a = (__int128)a * a % m;
        e >>= 1;
    }

    return r;
}

// Calculate modular inverse of a modulo m
int64 modinv(int64 a, int64 m) {
    int64 x, y;

    int64 g = egcd(a, m, x, y);

    if (g != 1)
        return -1;

    x %= m;

    if (x < 0)
        x += m;

    return x;
}

int main() {

    // =========================
    // KEY GENERATION
    // =========================

    int64 p = 467;
    int64 alpha = 2;

    // Private key
    int64 a = 123;

    // Public key component
    int64 beta = mod_pow(alpha, a, p);

    cout << "Public Key (p, alpha, beta): ("
         << p << ", " << alpha << ", " << beta << ")\n";

    cout << "Private Key a = " << a << "\n";


    // =========================
    // MESSAGE
    // =========================

    int64 m = 5;

    // Random value
    int64 r = 7;


    // =========================
    // ENCRYPTION
    // =========================

    int64 C1 = mod_pow(alpha, r, p);

    int64 C2 =
        (m * mod_pow(beta, r, p)) % p;

    cout << "\nOriginal Message = " << m << "\n";

    cout << "Ciphertext (C1, C2) = ("
         << C1 << ", " << C2 << ")\n";


    // =========================
    // DECRYPTION
    // =========================

    // s = C1^a mod p
    int64 s = mod_pow(C1, a, p);

    // Find inverse of s modulo p
    int64 s_inv = modinv(s, p);

    // m = C2 * s^(-1) mod p
    int64 m_dec =
        (C2 * s_inv) % p;

    cout << "Decrypted Message = "
         << m_dec << "\n";


    return 0;
}