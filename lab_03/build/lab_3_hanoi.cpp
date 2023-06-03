#include <iostream>
#include <string>
#include <list>
#include <cmath>

using namespace std;

void hanoi(int n, char source, char destination, char auxiliary, list<string> &actions) {
    if (n == 1) {
        actions.push_back("disk 1 from " + string(1, source) + " to " + string(1, destination));
        return;
    }

    hanoi(n - 1, source, auxiliary, destination, actions);
    actions.push_back("disk " + to_string(n) + " from " + string(1, source) + " to " + string(1, destination));
    hanoi(n - 1, auxiliary, destination, source, actions);

}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    list<string> actions;
    hanoi(n, 'A', 'B', 'C', actions);

    for (string step : actions) {
        cout << step << endl;
    }

    int num = pow(2, n) - 1;
    cout << "Algorithm has done " << actions.size() << " iterations | Optimal number of iterations is " << num;  
    actions.clear();
}