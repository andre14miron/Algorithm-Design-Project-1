#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int mod = 1000000007;

int type1(int x, int y) {
	vector <vector <int> > fr0;  // signals with the last bit equal to 0
	vector <vector <int> > fr1;  // signals with the last bit equal to 1

	fr0.assign(x + y, vector <int> (y + 1, 0));
	fr1.assign(x + y, vector <int> (y + 1, 0));

	/* Base case */
	fr0[0][0] = 1;
	fr1[0][1] = 1;

	/* General case */
	for (int i = 1; i < x + y; i++) {
		fr0[i][0] = 1;
		for (int j = 1; j <= y; j++) {
			fr0[i][j] = (fr0[i-1][j] + fr1[i-1][j]) % mod;
			fr1[i][j] = fr0[i-1][j-1];
		}
	}

	return (fr0[x+y-1][y] + fr1[x+y-1][y]) % mod;
}

int type2(int x, int y) {
	vector <int> a0(y + 1, 0);	  // signals with the last bit equal to 0
	vector <int> b0(y + 1, 0);
	vector <int> a1(y + 1, 0);	  // signals with the last bit equal to 1
	vector <int> b1(y + 1, 0);
	vector <int> a11(y + 1, 0);   // signals with the last two bits equal to 11
	vector <int> b11(y + 1, 0);

	/* Base case */
	a0[0] = 1;
	a1[1] = 1;

	/* General case */
	for (int i = 1; i < x + y; i++) {
		b0[0] = 1;
		for (int j = 1; j <= y; j++) {
			b0[j] = (a0[j] + a1[j]) % mod;
			b0[j] = (b0[j] + a11[j]) % mod;
			b1[j] = a0[j-1];
			b11[j] = a1[j-1];
		}
		copy(b0.begin(), b0.end(), a0.begin());
		copy(b1.begin(), b1.end(), a1.begin());
		copy(b11.begin(), b11.end(), a11.begin());
	}

	return ((a0[y] + a1[y]) % mod + a11[y]) % mod;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
