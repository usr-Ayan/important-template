#include <iostream>
using namespace std;

void primeFactors(int n) {
    // Check divisibility by 2
    while (n % 2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    // Check odd numbers from 3 to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    // If n is still > 1, then it's prime
    if (n > 1)
        cout << n;

    cout << endl;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Prime factors: ";
    primeFactors(n);
    return 0;
}
