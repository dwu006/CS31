#include <iostream>
using namespace std;

char* strcat(char* destination, const char* source)
{
    char* temp = destination + strlen(destination);
    for(int i = 0; i < strlen(source); i++)
    {
        *temp = source[i];
        temp++; 
    }
    return temp;
}

int main()
{
    char* a = 'hello';
    const char* s = 'hi'; 
    cout << strcat('hello', 'hi')
    return 0;
}