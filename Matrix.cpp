#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Displays a matrix
void display(int size, int **matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Adds two matrices then displays result
void add(int size, int **matrix1, int **matrix2) {
    // Creates new array
    int **addition = new int *[size];
    for (int i = 0; i < size; i++) {
        addition[i] = new int[size];
        
        for (int j = 0; j < size; j++) {
            addition[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    display(size, addition);

    // Free memory
    for (int i = 0; i < size; ++i) {
        delete[] addition[i];
    }
    delete[] addition;
}

// Subtracts the 1st matrix from the 2nd, then displays result
void sub(int size, int **matrix1, int **matrix2) {
    // Creates new matrix
    int **subtraction = new int *[size];
    for (int i = 0; i < size; i++) {
        subtraction[i] = new int[size];
        
        for (int j = 0; j < size; j++) {
            subtraction[i][j] = matrix2[i][j] - matrix1[i][j];
        }
    }

    display(size, subtraction);

    // Free memory
    for (int i = 0; i < size; ++i) {
        delete[] subtraction[i];
    }
    delete[] subtraction;
}

// Multiplies two matrices then displays the result
void mult(int size, int **matrix1, int **matrix2) {
    // Creates a new matrix
    int **multiple = new int *[size];
    for (int i = 0; i < size; i++) {
        multiple[i] = new int[size]();

        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                multiple[i][j] += matrix1[i][k] * matrix2[k][j]; // Takes dot product of each row and column
            }
        }
    }

    display(size, multiple);

    // Free memory
    for (int i = 0; i < size; ++i) {
        delete[] multiple[i];
    }
    delete[] multiple;
}

// Updates a value in a matrix. then displays updated matrix
void update(int size, int row, int column, int value, int **matrix) {
    // Tests validity of coordinates
    if (row < 0 | column < 0 | row >= size | column >= size) {
        cout << "Invalid indices for update" << endl;
    } else {
        matrix[row][column] = value;
        display(size, matrix);
    }

}

// Finds the maximum value of a matrix
int max(int size, int **matrix) {
    int max_val = matrix[0][0];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] > max_val) {
                max_val = matrix[i][j]; // If new value is bigger, the new value is the biggest
            }
        }
    }
    return max_val;
}

// Transposes a matrix and displays it
void transpose(int size, int **matrix) {
    // Creates a new matrix
    int **trans_matrix = new int *[size];
    for (int i = 0; i < size; i++) {
        trans_matrix[i] = new int[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            trans_matrix[j][i] = matrix[i][j]; // Rows swap with columns
        }
    }

    display(size, trans_matrix);

    // Free memory
    for (int i = 0; i < size; ++i) {
        delete[] trans_matrix[i];
    }
    delete[] trans_matrix;
}


int main() {
    // Initializes the file
    ifstream inputFile("matrix_input");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    int size;
    inputFile >> size; // Read matrix size from file's first number
    int **matrix1 = new int *[size];
    int **matrix2 = new int *[size];

    for (int i = 0; i < size; i++) {
        matrix1[i] = new int[size]();
        matrix2[i] = new int[size]();
        for (int j = 0; j < size; j++) {
            inputFile >> matrix1[i][j]; // Read matrix1 elements from file
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inputFile >> matrix2[i][j]; // Read matrix2 elements from file
        }
    }

    inputFile.close();

    cout << "Addition of Matrix1 and Matrix2:\n";
    add(size, matrix1, matrix2);

    cout << "Multiplication of Matrix1 and Matrix2:\n";
    mult(size, matrix1, matrix2);

    cout << "Subtraction of Matrix1 from Matrix2: \n";
    sub(size, matrix1, matrix2);

    cout << "Updated Matrix1 value:\n";
    update(size, 0, 0, 5, matrix1);

    cout << "Maximum value in Matrix1: " << max(size, matrix1) << endl << endl;
    
    cout << "Transpose of Matrix1:\n";
    transpose(size, matrix1);

    // Free memory
    for (int i = 0; i < size; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
    }
    delete[] matrix1;
    delete[] matrix2;

    return 0;
}

