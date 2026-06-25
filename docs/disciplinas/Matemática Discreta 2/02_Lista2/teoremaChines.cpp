#include <iostream>
#include <vector>
#include <numeric> 

using namespace std;

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int chinese_remainder_theorem(const vector<int>& a, const vector<int>& m) {
    int n = a.size();
    int M = 1; 

    for (int i = 0; i < n; i++) {
        M *= m[i];
    }

    int result = 0;

    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int yi = mod_inverse(Mi, m[i]);
        result += a[i] * Mi * yi;
    }

    return result % M;
}

int main() {
    int num_equations;

    cout << "Quantas equacoes deseja resolver (1-4)? ";
    cin >> num_equations;

    if (num_equations < 1 || num_equations > 4) {
        cout << "Numero invalido de equaçoes. Deve ser entre 1 e 4." << endl;
        return 1;
    }

    vector<int> a(num_equations);
    vector<int> m(num_equations);

    cout << "Insira as equacoes no formato x = a (mod m):" << endl;
    for (int i = 0; i < num_equations; i++) {
        cout << "a[" << i + 1 << "]: ";
        cin >> a[i];
        cout << "m[" << i + 1 << "]: ";
        cin >> m[i];

        if (m[i] <= 0) {
            cout << "O modulo deve ser um numero positivo." << endl;
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (gcd(m[i], m[j]) != 1) {
                cout << "Os modulos devem ser primos." << endl;
                return 1;
            }
        }
    }

    int solution = chinese_remainder_theorem(a, m);

    int M = 1;
    for (int i = 0; i < num_equations; i++) {
        M *= m[i];
    }

    cout << "A solucao eh x =" << solution << " (mod " << M << ")." << endl;

    return 0;
}