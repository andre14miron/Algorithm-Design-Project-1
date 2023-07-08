#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    int64_t score = 0;          // final scor
    int64_t size = a.size();    // size of the arrays
    vector <int> c;             // union vector between a and b

    /* compute the union between A and B */
    for (int i = 0; i < size; i++) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }

    sort(c.begin(), c.end());

    /* add the largest numbers to the score */
    for (int i = 1; i <= size; i++)
        score += c[2 * size - i];

    return score;
}

struct element {
    int value;
    int index;
};

int descComparator(const struct element a, const struct element b) {
    return a.value > b.value;
}

int64_t SolveTask2(const vector<int>& a, const vector<int>& b, int moves) {
    int64_t score = 0;          // final scor
    int64_t size = a.size();    // size of the arrays
    vector <struct element> c;  // union vector between a and b
    vector <int> fr(size, 0);   // vector that stores the occupied indices

    /* compute the union between A and B */
    struct element e;
    for (e.index = 0; e.index < size; e.index++) {
        e.value = a[e.index];
        c.push_back(e);
        e.value = b[e.index];
        c.push_back(e);
    }

    sort(c.begin(), c.end(), descComparator);

    /* calculate the score */
    for (int i = 0; i < size; i++)
        if (fr[c[i].index] == 0) {
            // no move is necessary
            score += c[i].value;
            fr[c[i].index] = 1;
        } else {
            // move is the best option
            // check if we still have available moves
            if (moves) {
                score += c[i].value;
                moves--;
            } else {
                size++;
            }
        }

    return score;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
