#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ff/parallel_for.hpp>

using namespace std;
using namespace ff;

const auto processors = std::thread::hardware_concurrency();

/** Prints a 2D matrix stored in a 2D vector.
 * matrix - matrix to be printed
 */
void printMatrix(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        string line = "|    ";
        for (int j = 0; j < matrix[i].size(); j++)
        {
            // concatenate value to output string.
            line += to_string(matrix[i][j]);
            line += "   |   ";
        }
        cout << line << endl;
    }
}

/** Multiplies 2 matrices together.
 * matrix1 - First matrix to multiply
 * matrix2 - Second matrix to multiply
 */
vector<vector<int>> multiplyMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
    // Get the number of columns and rows for the matrices
    int row1 = matrix1.size();
    int col1 = matrix1[0].size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    // If the columns of the first matrix is the same as the rows of the second matrix then continue with calculation.
    if(col1 != row2)
    {
        cout << "The number or rows of matrix 1 != columns of matrix 2." << endl;
        vector<vector<int>> matri{{}};
        return matri;
    }
    vector<vector<int>> finalMatrix;
    
    for(int i = 0; i < row1; i++)
    {
        vector<int> row;
        for(int j = 0; j < col2; j++)
        {
            for(int k = 0; k < col1; k++)
            {
                if(row.size() < col2)
                {
                    row.push_back(0);
                }
                // Calculate current value in row.
                row[j] += matrix1[i][k] * matrix2[k][j];
            }
        }
        finalMatrix.push_back(row);
    }
    return finalMatrix;
}

int main()
{
    // Arrays to be multiplied
    vector<vector<int>> matr2{{2,1,5,3},{0,7,1,6},{9,2,4,4},{3,6,7,2}};
    vector<vector<int>> matr1{{6,1,2,3},{4,5,6,5},{1,9,8,-8},{4,0,-8,5}};

    printMatrix(multiplyMatrices(matr2,matr1));

    return 0; 
}