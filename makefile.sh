#g++ -std=c++11 -I $FF_ROOT -O3 $1 -o a.out -pthread
g++ -std=c++11 -I $FF_ROOT -O3 Tests/matrixMultiplication.cpp -o a.out -pthread
sudo ./a.out