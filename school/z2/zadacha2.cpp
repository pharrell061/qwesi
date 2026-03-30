#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> generateMatrix(int size, int maxValue = 100) {
    vector<int> matrix;
    
    for (int i = 0; i < size; i++) {
        matrix.push_back(rand() % maxValue + 1);
    }
    
    return matrix;
}

void displayArray(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool containsDigit(int num, int digit) {
    num = abs(num);
    
    if (num == 0 && digit == 0) {
        return true;
    }
    
    while (num > 0) {
        if (num % 10 == digit) {
            return true;
        }
        num /= 10;
    }
    
    return false;
}

int generateMatrixSize() {
    int size;
    
    cout << "Enter the number of elements for the matrix: ";
    cin >> size;
    
    while (size < 1) {
        cout << "Invalid input! Please enter a positive number: ";
        cin >> size;
    }
    
    return size;
}

int magicSum(const vector<int>& arr, int targetDigit) {
    int sum = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        int num = arr[i];
        if (num % 2 != 0 && containsDigit(num, targetDigit)) {
            sum += num;
        }
    }
    
    return sum;
}

int magicSum3(const vector<int>& arr) {
    return magicSum(arr, 3);
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    cout << "=== MAGIC SUM CALCULATOR ===" << endl << endl;
    
    cout << "--- MATRIX GENERATION ---" << endl;
    int matrixSize = generateMatrixSize();
    cout << endl;
    
    vector<int> generatedMatrix = generateMatrix(matrixSize, 100);
    
    cout << "Generated Matrix: ";
    displayArray(generatedMatrix);
    cout << endl;
    
    cout << "--- RESULTS ---" << endl;
    cout << "Magic Sum (digit 3): " << magicSum3(generatedMatrix) << endl << endl;
    
    return 0;
}
