#include <iostream>
#include <vector>
using namespace std;

// Define a type alias for a matrix
using Matrix = vector<vector<int>>;

// Function to multiply two matrices
Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to raise a matrix to a non-negative integer power
Matrix matrixExponentiation(const Matrix& base, int power) {
    int n = base.size();
    Matrix result(n, vector<int>(n, 0));

    // Initialize result as identity matrix
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    Matrix A = base;

    // Exponentiation by squaring
    while (power > 0) {
        if (power % 2 == 1) {
            result = multiply(result, A);
        }
        A = multiply(A, A);
        power /= 2;
    }

    return result;
}

int main() {
    // Example: Compute A^3, where A is a 2x2 matrix
    Matrix A = {{1, 1},
                {1, 0}};
    int power = 10;

    // Compute A^3
    Matrix result = matrixExponentiation(A, power);

    // Output the result
    cout << "A^3 = " << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
