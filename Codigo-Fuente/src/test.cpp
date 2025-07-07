#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    cout << v.size() << endl;

    v.insert(v.begin(), 1);
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    cout << v.size() << endl;

    v.insert(v.begin() + 1, 3);
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    cout << v.size() << endl;

}