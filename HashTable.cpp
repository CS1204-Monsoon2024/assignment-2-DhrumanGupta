#include <iostream>
#include <vector>
using namespace std;

class HashTable{
    private:
        int size;
        int used;
        int* arr; // the table itself
        float threshold = 0.8;

        int hash(int key) {
            // This can be any hash function, but we will use the modulo operation for simplicity
            return key % size;
        }


    public:
        HashTable(int m) {
            size = m;
            used = 0;
            arr = new int[size];

            // initialize the table with -1
            for (int i=0; i<size; i++){
                arr[i] = -1;
            }
        }


        void insert(int key) {
            float load =  ((float) used)/size;


            if (load >= threshold) {
                resizeTable();
            }

            int index = hash(key);

            for (int i = 0; i < size; i++){
                int newIndex = hash(index + i*i);

                if (arr[newIndex] == key) {
                    cout << "Duplicate key insertion is not allowed" << endl;
                    return;
                }

                if (arr[newIndex]==-1){
                    arr[newIndex] = key;
                    used++;
                    return;
                }
            }

            cout << "Max probing limit reached!" << endl;
        }

        void remove(int key) {
            int index = hash(key);


            int originalindex = index;

            for (int i = 0; i < size; i++) {
                int newIndex = hash(index + i*i);

                if (arr[newIndex] == key){
                    arr[newIndex] = -1;
                    used--;
                    return;
                }
            }

            cout << "Element not found" << endl;
        }
        

        void resizeTable() {
            int oldSize = size;
            size = nextPrime(2 * size);
            
            int* newarr = new int[size];

            for (int i = 0; i < size; i++) {
                newarr[i] = -1;
            }

            for (int i = 0; i < size; i++) {
                if (arr[i] != -1) {
                    int key = arr[i];
                    int index = hash(key);
                    if (newarr[index] == -1){
                        newarr[index] = key;
                        continue;
                    }

                    for (int j=1; j<size; j++){
                        int newIndex = hash(index + j*j);
                        if (newarr[newIndex]==-1){
                            newarr[newIndex] = key;
                            break;
                        }
                    }
                }
            }
            delete[] arr;
            arr = newarr;

        }


        int search(int key) {
            int index = hash(key);

            for (int i = 0; i < size; i++) {
                int newIndex = hash(index + i*i);
                if (arr[newIndex] == -1) {
                    return -1;
                }
                if (arr[newIndex] == key) {
                    return newIndex;
                }
            }

            return -1;
        }


        void printTable() {
            for (int i=0; i<size; i++){
                if (arr[i] == -1){
                    cout << "- " ;
                }
                else {
                    cout << arr[i] << " " ;
                }
            }
            cout << endl;
        }


        bool isPrime(int num) {
            if (num <= 1) return false;
            if (num == 2 || num == 3) return true;
            if (num % 2 == 0 || num % 3 == 0) return false;
            for (int i = 5; i * i <= num; i += 6) {
                if (num % i == 0 || num % (i + 2) == 0) return false;
            }
            return true;
        }

        int nextPrime(int n) {
            int primeCandidate = n;
            while (!isPrime(primeCandidate)) {
                primeCandidate++;
            }
            return primeCandidate;
        }
};