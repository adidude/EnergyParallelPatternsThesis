#include <iostream>
#include <pthread.h>
using namespace std;

#if defined(__cplusplus)
extern "C"
#endif
void *print_message(void*)
{
    cout << "Threading\n";
}



int main() 
{
    pthread_t t1;

    pthread_create(&t1, NULL, &print_message, NULL);
    cout << "Hello";

    void* result;
    pthread_join(t1,&result);

    return 0;
}