#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector <int> gradesSushi(int n, int m, vector <vector <int> >& g) {
	vector <int> grades(m, 0);

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			grades[j] += g[i][j];
		}
	}

	return grades;
}

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	int budget = n * x;
	vector <int> grades = gradesSushi(n, m, g);
	vector <vector <int> > dp(m + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int price = 0; price <= budget; price++) {
            // not add the plate i
            dp[i][price] = dp[i-1][price];

            // decided to use plate i and check if it fits
            if (price - p[i-1] >= 0) {
                int sol_aux = dp[i-1][price - p[i-1]] + grades[i-1];

				// choose the best option
                dp[i][price] = max(dp[i][price], sol_aux);
            }
        }
    }

	return dp[m][budget];
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int budget = n * x;
	vector <int> grades = gradesSushi(n, m, g);
	vector <vector <int> > dp(2*m + 1, vector <int>(budget + 1, 0));

	/* multiply each sushi plate */
	for (int i = 0; i < m; i++) {
		p.push_back(p[i]);
		grades.push_back(grades[i]);
	}

    for (int i = 1; i <= 2 * m; i++) {
        for (int price = 0; price <= budget; price++) {
            // not add the plate i
            dp[i][price] = dp[i-1][price];

            // decided to use plate i and check if it fits
            if (price - p[i-1] >= 0) {
                int sol_aux = dp[i-1][price - p[i-1]] + grades[i-1];

				// choose the best option
                dp[i][price] = max(dp[i][price], sol_aux);
            }
        }
    }

	return dp[2 * m][budget];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int budget = n * x;
	vector<int> grades = gradesSushi(n, m, g);
	vector <vector <vector <int> > > dp(m + 1, vector< vector <int>>(
										budget + 1, vector <int>(n + 1, 0)));

    for (int i = 1; i <= m; i++) {
        for (int price = 0; price <= budget; price++) {
			for (int k = 1; k <= n; k++) {
            	// not add the plate i
				dp[i][price][k] = dp[i-1][price][k];

            	// decided to use plate i and check if it fits
            	if (price - p[i-1] >= 0) {
					int sol1 = 0;  // solution if we use one plates
					int sol2 = 0;  // solution if we use two plates

                	sol1 = dp[i-1][price - p[i-1]][k-1] + grades[i-1];

					// decided to use two plates i and check if it fits
					if (price - 2*p[i-1] >= 0 && k > 1) {
                		sol2 = dp[i-1][price - 2*p[i-1]][k-2] + 2*grades[i-1];
					}

					// choose the best option
                	dp[i][price][k] = max(dp[i][price][k], sol1);
					dp[i][price][k] = max(dp[i][price][k], sol2);
            	}
        	}
		}
    }

	return dp[m][budget][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
