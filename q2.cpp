// Run this by "cat numbers.txt | ./q2.out" after compiling

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to compute mean
double computeMean(const vector<int>& data) {
    double sum = 0;
    for (int value : data)
        sum += value;
    return sum / data.size();
}

// Function to compute median
double computeMedian(vector<int> data) {
    sort(data.begin(), data.end());


    int n = data.size();
    if (n % 2 == 0)
        return (data[n/2 - 1] + data[n/2]) / 2.0;
    else
        return data[n/2];
}


double computeStdDev(const vector<int>& data, double mean) {
    double sum = 0;
    for (int value : data)
        sum += (value - mean) * (value - mean);
    return sqrt(sum / 1000);
}

int main() {
    const int m = 50;
    const int p = 100003;    // A large prime number
    const int a = 8939;     // Chosen a in [1, p-1]
    const int b = 41269;     // Chosen b in [1, p-1]

    vector<int> hash1_freq(m, 0);
    vector<int> hash2_freq(m, 0);

    long long h1a1 = -1;
    long long h1a2 = -1;
    long long h2a1 = -1;
    long long h2a2 = -1;

    unsigned long long x;
    int count = 0;
    while (cin >> x && count < 1000) {
        // Hash function h1(x) = x mod 50
        int h1 = x % m;
        if (h1 < 0) h1 += m;
        hash1_freq[h1]++;

        // cout << "h1: " << h1 << endl;

        if (h1 == 0 && h1a2 == -1 && h1a1 != -1) {
            h1a2 = x;
        }

        if (h1 == 0 && h1a1 == -1) {
            h1a1 = x;
        }


        // Hash function h2(x) = ((a x + b) mod p) mod 50
        int h2 = ((static_cast<long long>(a) * x + b) % p) % m;
        if (h2 < 0) h2 += m; 
        hash2_freq[h2]++;

        if (h2 == 0 && h2a2 == -1 && h2a1 != -1) {
            h2a2 = x;
        }

        if (h2 == 0 && h2a1 == -1) {
            h2a1 = x;
        }



        count++;
    }

    if (count == 0) {
        cerr << "Error: No input data received." << endl;
        return 1;
    }

    // print all hash_1 frequencies
    // for (int i = 0; i < m; i++) {
    //     cout << hash1_freq[i] << " ";
    // }
    // cout << endl;

    // // print all hash_2 frequencies
    // for (int i = 0; i < m; i++) {
    //     cout << hash2_freq[i] << " ";
    // }
    // cout << endl;

    // Compute statistics for hash1
    double mean1 = computeMean(hash1_freq);
    double median1 = computeMedian(hash1_freq);
    double stddev1 = computeStdDev(hash1_freq, mean1);

    // Compute statistics for hash2
    double mean2 = computeMean(hash2_freq);
    double median2 = computeMedian(hash2_freq);
    double stddev2 = computeStdDev(hash2_freq, mean2);

    // Output the results
    cout << "Hash Function h1(x) = x mod 50" << endl;
    // cout << "Mean: " << mean1 << endl;
    cout << "Median: " << median1 << endl;
    cout << "Standard Deviation: " << stddev1 << endl << endl;
    cout << "U: {" << h1a1 << ", " << h1a2 << "}" << endl << endl;

    cout << "Hash Function h2(x) = ((a * x + b) mod p) mod 50" << endl;
    // cout << "Mean: " << mean2 << endl;
    cout << "Median: " << median2 << endl;
    cout << "Standard Deviation: " << stddev2 << endl;
    cout << "U: {" << h2a1 << ", " << h2a2 << "}" << endl << endl;
    return 0;
}
