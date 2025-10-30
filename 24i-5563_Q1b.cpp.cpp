#include <iostream>
using namespace std;

void PrintPatternHelper(int arr[], int size, int n) {
	
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int i;
    for (i = size - 1; i >= 0; i--) {
        if (arr[i] > 1)
            break;
    }

    if (i < 0)
        return;

    arr[i]--;

    int total = 0;
    for (int j = 0; j <= i; j++)
        total += arr[j];

    while (total < n) {
        arr[++i] = 1;
        total++;
    }

    PrintPatternHelper(arr, i + 1, n);
}

void PrintPattern(int &n) {
    int arr[100];
    arr[0] = n;
    PrintPatternHelper(arr, 1, n);
}

int main() {
    int n;
    cout << "Enter any number = ";
    cin >> n;
    PrintPattern(n);
    return 0;
}

