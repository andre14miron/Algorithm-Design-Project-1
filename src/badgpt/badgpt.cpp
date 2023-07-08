#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define N 2
#define mod 1000000007

using namespace std;

/* C = A * B */
void multiply_matrix(long long A[N][N], long long B[N][N], long long C[N][N]) {
    long long tmp[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long sum = 0;

            for (int k = 0; k < N; k++) {
                sum += (1LL * (A[i][k] % mod) * (B[k][j] % mod)) % mod;
                sum = sum % mod;
            }

            tmp[i][j] = sum % mod;
        }
    }

    memcpy(C, tmp, sizeof(tmp));
}

/* R = C^p */
void power_matrix(long long C[N][N], long long p, long long R[N][N]) {
    long long tmp[N][N];

    /* create the identity matrix */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tmp[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (p != 1) {
        if  (p % 2 == 0) {
            multiply_matrix(C, C, C);      // C = C * C
            p /= 2;                        // remains to calculate C^(p/2)
        } else {
            multiply_matrix(tmp, C, tmp);  // tmp = tmp * C
            p--;                           // remains to calculate C^(p-1)
        }
    }

    multiply_matrix(C, tmp, R);            // result = tmp * C
}

/* returns the n-th Fibonacci number */
long long fibonacci(long long n) {
    /* base cases */
    if (n <= 2) return 1;

    /* constructing matrix C */
    long long C[N][N] = { {0, 1},
                          {1, 1}};

    /* C = C^(n-2) */
    power_matrix(C, n - 2, C);

    /* get the result*/
    long long result = C[0][1] % mod + C[1][1] % mod;
    return result % mod;
}

int main() {
    freopen("badgpt.in", "r", stdin);
	freopen("badgpt.out", "w", stdout);

    string compressedText;  // compressed text
    int flag_n = 0;         // flag for detecting the sequence with 'n'
    int flag_u = 0;         // flag for detecting the sequence with 'u'
    long long number = 0;   // number of occurrences of the letter
    long long result = 1;   // number of distinct strings

	cin >> compressedText;

    for (char c : compressedText) {
        /* check if it is a digit and if it is the one being searched for */
        /* otherwise, it is possible that the sequence of interest has ended */
        if (isdigit(c) && (flag_n == 1 || flag_u == 1)) {
            number = number * 10 + c - '0';
        } else if (flag_n == 1) {
            /* The number for the sequence with 'n' has finished being read */
            result = (1LL * result * fibonacci(number + 1)) % mod;
            flag_n = 0;
            number = 0;
        } else if (flag_u == 1) {
            /* The number for the sequence with 'n' has finished being read */
            result = (1LL * result * fibonacci(number + 1)) % mod;
            flag_u = 0;
            number = 0;
        }

        if (c == 'n')
            /* a sequence with 'n' has been detected */
            flag_n = 1;
        else if (c == 'u')
            /* a sequence with 'u' has been detected */
            flag_u = 1;
    }

    // check for the last sequence
    if (flag_n == 1 || flag_u == 1) {
        result = (1LL * result * fibonacci(number + 1)) % mod;
    }

    cout << result << endl;

    return 0;
}
