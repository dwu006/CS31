#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value)
{
    int arrLen = sizeof(a) / sizeof(a[0]);
    if(n < 0 || n > arrLen-1)
    {
        return -1;
    }
    for(size_t i = 0; i < n; i++)
    {
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    int arrLen = sizeof(a) / sizeof(a[0]);
    if(n < 0 || n > arrLen-1)
    {
        return -1;
    }
    for(size_t i = 0; i < n; i++)
    {
        if(a[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    int arrLen = sizeof(a) / sizeof(a[0]);
    if(n <= 0 || n > arrLen-1)
    {
        return -1;
    }
    int maxPos = 0;
    for(size_t i = 0; i < n-1; i++)
    {
        if(a[i] > a[i+1])
        {
            maxPos = i;
        } else {
            maxPos = i+1;
        }
    }
    return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
    int arrLen = sizeof(a) / sizeof(a[0]);
    if(n < 0 || n > arrLen-1 || pos < 0 || pos > arrLen-1 || pos > n)
    {
        return -1;
    }
    string temp = a[pos];
    for(size_t i = pos; i < n-1; i++)
    {
        a[i] = a[i+1];
    }
    a[n] = temp;
    return pos;
}

int countRuns(const string a[], int n)
{

}

int flip(string a[], int n)
{
    int arrLen = sizeof(a) / sizeof(a[0]);
    if(n < 0 || n > arrLen-1)
    {
        return -1;
    }
    for(size_t i = 0; i < n/2; i++)
    {
        string temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    int arrLen1 = sizeof(a1) / sizeof(a1[0]);
    int arrLen2 = sizeof(a2) / sizeof(a2[0]);
    if(n1 < 0 || n1 > arrLen1-1 || n2< 0 || n2 > arrLen2-1)
    {
        return -1;
    }
    int n = (n1 < n2) ? n1 : n2;
    for(size_t i = 0; i < n; i++)
    {
        if(a1[i] != a2[i])
        {
            return i;
        }
    }
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2);

int lookupAny(const string a1[], int n1, const string a2[], int n2);

int separate(string a[], int n, string separator);


int main()
{

}