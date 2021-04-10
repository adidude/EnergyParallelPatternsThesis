#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
        vector<vector<int>> empty;
        return empty;
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

vector<int> split(string s, string del = " ")
{
    vector<int> splitStr;
    int start = 0;
    int end = s.find(del);
    while (end != -1)
    {
        splitStr.push_back(stoi(s.substr(start, end - start)));
        start = end + del.size();
        end = s.find(del, start);
    }
    splitStr.push_back(stoi(s.substr(start, end - start)));
    return splitStr;
}

vector<vector<vector<int>>> readMatricesFromData()
{
    fstream file;
    file.open("matrixDataset");
    string line = "";
    vector<vector<vector<int>>> deliverable;
    while(getline(file,line))
    {
        vector<vector<int>> matrix1;
        vector<vector<int>> matrix2;
        vector<int> row;
        vector<int> data = split(line,",");
        int matrixDimensions[3] = {0,0,0};
        int mat1AreaOffset;
        int lineLength = data.size();
        for(int i=0;i<lineLength;i++)
        {
            if(i < 3)
            {
                matrixDimensions[i] = data[i];
                mat1AreaOffset = matrixDimensions[0] * matrixDimensions[1] + 3;
            }
            else if(i >= 3 && i <= mat1AreaOffset)
            {
                if(i - 3 != 0 && ((i - 3) % matrixDimensions[1]) == 0)
                {
                    matrix1.push_back(row);
                    row.clear();            
                }
                row.push_back(data[i]);
            }
            else
            {
                if(i - mat1AreaOffset != 0 && ((i - mat1AreaOffset) % matrixDimensions[2]) == 0)
                {
                    matrix2.push_back(row);
                    row.clear();
                }
                row.push_back(data[i]);
                if(i == lineLength - 1)
                {
                    matrix2.push_back(row);
                }
            }
        }
        deliverable.push_back(matrix1);
        deliverable.push_back(matrix2);
    }
    file.close();
    return deliverable;
}

int main()
{
    readMatricesFromData();
    // Arrays to be multiplied
    vector<vector<int>> matr2{{1,2},{3,4}};
    vector<vector<int>> matr1{{2,0},{1,2}};

    // printMatrix(multiplyMatrices(matr2,matr1));

    return 0;
}