#include <iostream>
using namespace std;

void ChangeLocation(char *Array, int b1, int b2) {
	
    if (b1 >= b2) {
        return;
    }

    char temp = Array[b1];
    Array[b1] = Array[b2];
    Array[b2] = temp;

    ChangeLocation(Array, b1 + 1, b2 - 1);
}

int main() {
    char Array[8] = {'C', 'O', 'M', 'P', 'U', 'T', 'E', 'R'};
    int b1 = 3, b2 = 7;

    cout << "Original array: ";
    for (int i = 0; i < 8; i++) cout << Array[i] << " ";
    cout << endl;

    ChangeLocation(Array, b1 - 1, b2 - 2);

    cout << "After changing locations between indices " << b1 << " and " << b2 << ": ";
    for (int i = 0; i < 8; i++) cout << Array[i] << " ";
    cout << endl;

    return 0;
}

