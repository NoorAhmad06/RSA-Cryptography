#include <iostream>
#include <vector>
#include <cmath>

using namespace std; 

bool isPrime(int num) {
    if (num < 2) {
        return false;
    }

    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        } 
    }
    return true;
}

long long GCD(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

long long modInverse(long long a, long long b){
    long long x1 = 1;
    long long y1 = 0;
    long long x2 = 0;
    long long y2 = 1;
    long long originalMod = a;

    while (b != 0) {
        long long q = a / b;
        long long remainder = a % b;

        long long newX = x1 - q * x2;
        long long newY = y1 - q * y2;

        x1 = x2;
        x2 = newX;

        y1 = y2;
        y2 = newY;

        a = b;
        b = remainder;
    }
    y1 = y1 % originalMod;

    if (y1 < 0) {
        y1 = y1 + originalMod;
    }
    return y1;
}

long long modExponent(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exponent /= 2;
    }

    return result;
}

int main() {
    int e;
    int n;
    int m;

    cin >> e;
    cin >> n;
    cin >> m;
    
    vector<int> encrypted;

    for (int i = 0; i < m; i++) {
        int value;
        cin >> value;
        encrypted.push_back(value);
    }

    int p = 0;
    int q = 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            int possibleP = i;
            int possibleQ = n / i;

        if (isPrime(possibleP) && isPrime(possibleQ) && possibleP != possibleQ) {
            p = possibleP;
            q = possibleQ;
            break;
            }
        }
    }
    if (p == 0 || q == 0) {
        cout << "Public key is not valid!" << endl;
        return 0;
    }

    long long phi = (static_cast<long long>(p) - 1) * (q - 1);

    if (GCD(e, phi) != 1) {
        cout << "Public key is not valid!" << endl;
        return 0;
    }

    long long d = modInverse(phi, e);

    vector<int> message;

    for (int i = 0; i < encrypted.size(); i++) {
        int value = encrypted.at(i);

        long long decrypted = modExponent(value, d, n);

        message.push_back(decrypted);
    }

    cout << p << " " << q << " " << phi << " " << d << endl;

    for (int i = 0; i < message.size(); i++) {
        cout << message.at(i);

        if (i < message.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < message.size(); i++) {
        int value = message.at(i);

        if (value >= 5 && value <= 30) {
            char letter = static_cast<char>('A' + value - 5);
            cout << letter;
        }
        else if (value == 31) {
            cout << " ";
        }
        else if (value == 32) {
            cout << "\"";
        }
        else if (value == 33) {
            cout << ",";
        }
        else if (value == 34) {
            cout << ".";
        }
        else if (value == 35) {
            cout << "'";
        }
    }

    cout << endl;

    return 0;
}