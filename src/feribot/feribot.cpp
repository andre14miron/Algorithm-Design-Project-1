#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 1000000000000

using namespace std;

int main() {
	freopen("feribot.in", "r", stdin);
	freopen("feribot.out", "w", stdout);

	int N;                 // number of cars
	int K;                 // number of feribots
    long long Cmin = 0;    // lower bound of the search interval
    long long Cmax = 0;    // upper bound of the search interval
    long long min = MAX;   // the biggest weight
    long long max = 0;     // the smallest weight
    int m;                 // maximum number of cars that fit on a ferry
    vector <long long> G;  // weights of each car

	cin >> N >> K;

    G.assign(N, 0);
    m = N/K + 1;

	/* read the weight of each car */
	for (int i = 0; i < N; i++) {
		cin >> G[i];

        if (G[i] > max)
            max = G[i];

        if (G[i] < min)
            min = G[i];
	}

    /* Cmin is at least the maximum weight of cars or the minimum weight that 
     * can be on a ferry */
    Cmin = max > m * min ? max : m * min;

    /* Cmax is the maximum weight that can be found on a ferry */
    vector <long long> G2(G);
    sort(G2.begin(), G2.end());
    for (int i = 1; i <= m; i++) {
        Cmax += G2[N - i];
    }

    /* search C */
    while (Cmin < Cmax) {
        long long Cmid = (Cmin + Cmax) / 2;
        long long G_feribot = 0;    // the weight of the current ferry
        int K_feribot = 1;          // the current ferry

        for (auto g : G) {
            if (G_feribot + g > Cmid) {
                // a new ferry is needed
                K_feribot++;
                // check if all ferries have already been occupied
                if (K_feribot == K+1)
                    break;
                G_feribot = g;
            } else {
                // the car fits in the current ferry
                G_feribot += g;
            }
        }

        if (K_feribot <= K)
            Cmax = Cmid;
        else
            Cmin = Cmid + 1;
    }

    cout << Cmin << endl;

	return 0;
}
