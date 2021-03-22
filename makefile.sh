g++ -std=c++11 $1 -o a.out -pthread
sudo ./a.out
#g++ -std=c++11 -I $FF_ROOT -O3 test.cpp -o test -pthread