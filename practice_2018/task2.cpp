#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

long double fact(int n) {
    long int res = 1;
    for (long int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

int main() {
    cout << "Введите количество игроков: ";
    int n;
    cin >> n;
    cout << "Введите имена игроков, если требуется." << endl;
    cout << "Y - с именами, N - без." << endl;
    char decision;
    cin >> decision;
    vector<string> names(n);
    if (decision == 'Y') {
        for (int i = 0; i < n; ++i) {
            cout << "Игрок №" << i + 1 << ": ";
            cin >> names[i];
        }
    }
    vector<double> shapley(n, 0);
    cout << "Введите характеристическую функцию для каждой коалиции: " << endl;
    map<set<int>, int> character;
    map<set<int>, bool> was;
    vector<int> players(n);
    set<int> playersInCoalition;
    character[playersInCoalition] = 0;
    for (int i = 1; i <= n; ++i) {
        players[i - 1] = i;
        playersInCoalition.insert(i);
        int tmp = 0;
        for (auto player: playersInCoalition) {
            if (tmp != 0) {
                cout << " & ";
            }
            if (decision == 'Y') {
                cout << names[player - 1];
            } else {
                cout << player;
            }
            ++tmp;
        }
        cout << ": ";
        //cin >> character[playersInCoalition];
        character[playersInCoalition] = 1;
        for (auto play: playersInCoalition) {
            character[playersInCoalition] *= play;
        }
        cout << character[playersInCoalition] << endl;
        was[playersInCoalition] = true;
    }
    while (next_permutation(players.begin(), players.end())) {
        playersInCoalition.clear();
        for (int i = 0; i < n; ++i) {
            playersInCoalition.insert(players[i]);
            int tmp = 0;
            if (!was[playersInCoalition]) {
                for (auto player: playersInCoalition) {
                    if (tmp != 0) {
                        cout << " & ";
                    }
                    if (decision == 'Y') {
                        cout << names[player - 1];
                    } else {
                        cout << player;
                    }
                    ++tmp;
                }
                cout << ": ";
                //cin >> character[playersInCoalition];
                character[playersInCoalition] = 1;
                for (auto play: playersInCoalition) {
                    character[playersInCoalition] *= play;
                }
                cout << character[playersInCoalition] << endl;
                was[playersInCoalition] = true;
            }
        }
    }
    long int numberOfCoalitions = fact(n);
    //long double m = rand() % numberOfCoalitions + 1;
    long double m = numberOfCoalitions - 10000;
    map<string, bool> check;
    check[""] = true;
    for (int i = 0; i < m; ++i) {
        vector<int> permutations(n, 0);
        string tryToCheck = "";
        while (check[tryToCheck]) {
            tryToCheck = "";
            vector<bool> used(n, false);
            for (int j = 0; j < n; ++j) {
                int value = rand() % n + 1;
                while (used[value - 1]) {
                    value = rand() % n + 1;
                }
                used[value - 1] = true;
                permutations[j] = value;
                tryToCheck += to_string(value) + ' ';
            }
        }
        check[tryToCheck] = true;
        for (int j = 0; j < n; ++j) {
            int k = 0;
            while (permutations[k] != j + 1) {
                ++k;
            }
            set<int> coalition;
            for (int q = 0; q <= k; ++q) {
                coalition.insert(permutations[q]);
            }
            set<int> without = coalition;
            without.erase(j + 1);
            shapley[j] += ((character[coalition] - character[without]) / m);
        }
    }
    cout << "Приближенные значения Шепли для каждого игрока: " << endl;
    for (int i = 0; i < n; ++i) {
        if (decision == 'Y') {
            cout << names[i];
        } else {
            cout << i + 1;
        }
        cout << ": " << shapley[i] << endl;
    }
    cout << m;
}