#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <assert.h>
#include <ff/parallel_for.hpp>
#include <ff/pipeline.hpp>
#include "strassen.h"

using namespace std;
using namespace std::chrono;
using namespace ff;

// Gets the number of cores - 1 to utilize a single core to take readings.
const auto noOfProcessors = thread::hardware_concurrency()-1;
string fileToOpen = "PyScripts/Output/matrixDataset";

//struct 

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

void printMatrix(lld** print,int rowLen,int colLen)
{
    for (int i = 0; i < rowLen; i++)
    {
        for (int j = 0; j < colLen; j++)
        {
            printf("%lld ", print[i][j]);
        }
        printf("\n");
    }
}

void assertMultiplicationValidity(int col, int row)
{
    // If the columns of the first matrix is the same as the rows of the second matrix then continue with calculation.
    if (col != row)
    {
        cout << "The number or rows of matrix 1 != columns of matrix 2." << endl;
        assert(false);        
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

    assertMultiplicationValidity(col1,row2);

    //Create and initialise a matrix
    vector<vector<int>> finalMatrix;

    for (int i = 0; i < row1; i++)
    {
        vector<int> row;
        for (int j = 0; j < col2; j++)
        {
            for (int k = 0; k < col1; k++)
            {
                if (row.size() < col2)
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
    file.open(fileToOpen);
    if(!file.is_open())
    {
        cout << "Failed to open file" << endl;
        assert(false);
    }
    string line = "";
    vector<vector<vector<int>>> deliverable;
    while (getline(file, line))
    {
        vector<vector<int>> matrix1;
        vector<vector<int>> matrix2;
        vector<int> row;
        vector<int> data = split(line, ",");
        int matrixDimensions[3] = {0, 0, 0};
        int mat1AreaOffset;
        int lineLength = data.size();
        for (int i = 0; i < lineLength; i++)
        {
            if (i < 3)
            {
                matrixDimensions[i] = data[i];
                mat1AreaOffset = matrixDimensions[0] * matrixDimensions[1] + 3;
            }
            else if (i >= 3 && i <= mat1AreaOffset)
            {
                if (i - 3 != 0 && ((i - 3) % matrixDimensions[1]) == 0)
                {
                    matrix1.push_back(row);
                    row.clear();
                }
                row.push_back(data[i]);
            }
            else
            {
                if (i - mat1AreaOffset != 0 && ((i - mat1AreaOffset) % matrixDimensions[2]) == 0)
                {
                    matrix2.push_back(row);
                    row.clear();
                }
                row.push_back(data[i]);
                if (i == lineLength - 1)
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

lld** convertToPointer(vector<vector<int>> convertee, bool print)
{
    int rowLen = convertee.size();
    int colLen = convertee[0].size();
    lld** matrix;
    matrix = new lld*[rowLen];
    for (int i = 0; i < rowLen; i++)
    {
        matrix[i] = new lld[colLen];
    }

    for(int i = 0;i < rowLen; i++)
    {
        for(int j = 0; j < colLen;j++)
        {
            matrix[i][j] = convertee[i][j];
        }
    }

    if (print)
    {
        for (int i = 0; i < rowLen; i++)
        {
            for (int j = 0; j < colLen; j++)
            {
                printf("%lld ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    return matrix;
}

void testAccuracy(lld** point, vector<vector<int>> vect,int rows, int cols)
{
    bool test = true;

    for(int i = 0;i < rows;i++)
    {
        for(int j = 0; j < cols;j++)
        {
            if(point[i][j] != vect[i][j])
            {
                test = false;
                break;
            }
        }
        if(!test)
        {
            break;
        }
    }
}

vector<vector<int>> parallelMatrixMultiplication(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int threads)
{
    // Get the number of columns and rows for the matrices
    int row1 = matrix1.size();
    int col1 = matrix1[0].size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    assertMultiplicationValidity(col1,row2);

    vector<vector<int>> finalMatrix;
    vector<int> startRows(col2);
    for (int i = 0; i < row1; i++)
    {
        finalMatrix.push_back(startRows);
    }

    //Terminates if too many threads exist or too little. Each thread will utilize 100% of a core, having more than the physical amount can lead to resource starvation.
    assert(threads <= noOfProcessors && threads > 0);
    ParallelFor paraLoop(threads);
    paraLoop.parallel_for(0,row1,[col2,col1,matrix1,matrix2,&finalMatrix](const long i)
    {
        for (int j = 0; j < col2; j++)
        {
            for (int k = 0; k < col1; k++)
            {
                // Calculate current value in row.
                finalMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    });

    return finalMatrix;

}

void dataGatherer(int repetitions)
{
    cout << "Serial Start (ms),Serial End (ms),Serial Duration (ms),Parallel Start (ms),Parallel End (ms),Parallel Duration (ms),Cores,Speedup" << endl;
    vector<vector<vector<int>>> matrices = readMatricesFromData();
    
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1);
    auto executionStart = high_resolution_clock::now();
    for(int i = 0; i < repetitions; i++)
    {
        for(int j = 0;j < matrices.size();j=j+2)
        {
            t1 = high_resolution_clock::now();
            vector<vector<int>> ans1 = multiplyMatrices(matrices[j],matrices[j+1]);
            t2 = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(t2 - t1);
            int serialTime = duration.count();
            string serialData = to_string(duration_cast<milliseconds>(t1 - executionStart).count()) + "," + to_string(duration_cast<milliseconds>(t2 - executionStart).count()) + "," + to_string(serialTime);

            for(int k = 1; k <= noOfProcessors; k++)
            {
                t1 = high_resolution_clock::now();
                vector<vector<int>> ans2 = parallelMatrixMultiplication(matrices[j], matrices[j + 1], k);
                t2 = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(t2 - t1);
                int speedup = serialTime/duration.count();
                string printData = serialData + "," + to_string(duration_cast<milliseconds>(t1-executionStart).count()) + "," + to_string(duration_cast<milliseconds>(t2-executionStart).count()) + "," + to_string(duration.count()) + "," + to_string(k) + "," + to_string(speedup);
                cout << printData << endl;
            }
        }
    }
}

int main()
{
    dataGatherer(1);
    return 0;
}