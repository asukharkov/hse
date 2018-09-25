#include <algorithm>
#include <iostream>
#include <map>
#include <set>
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
    vector<long double> shapley(n, 0);
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
        cin >> character[playersInCoalition];
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
                cin >> character[playersInCoalition];
                was[playersInCoalition] = true;
            }
        }
    }
    for (auto coalition: character) {
        set<int> currentPlayers = coalition.first;
        int value = coalition.second;
        for (auto player: currentPlayers) {
            set<int> without = currentPlayers;
            without.erase(player);
            shapley[player - 1] += fact(currentPlayers.size() - 1)
                                   * fact(n - currentPlayers.size()) / fact(n) * (value - character[without]);
        }
    }
    cout << "Значения Шепли для каждого игрока: " << endl;
    for (int i = 0; i < n; ++i) {
        if (decision == 'Y') {
            cout << names[i];
        } else {
            cout << i + 1;
        }
        cout << ": " << shapley[i] << endl;
    }
}
