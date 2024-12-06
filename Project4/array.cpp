#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// adds value to the end of each element in array a
int appendToAll(string a[], int n, string value)
{
    if(n < 0) // checks if array size is negative    
    {
        return -1;
    }
    for(size_t i = 0; i < n; i++) // loops through array a
    {
        a[i] += value; // adds value to the end of each element
    }
    return n;
}

// returns the position of target in the array 
int lookup(const string a[], int n, string target)
{
    if(n < 0) // checks if array size is negative
    {
        return -1;
    }
    for(size_t i = 0; i < n; i++) // loops through array a
    {
        if(a[i] == target) // checks if the element at i in array is equal to target
        {
            return i;
        }
    }
    return -1; // returns -1 if no elements in array is equal to target
}

// returns the position of the largest string in array
int positionOfMax(const string a[], int n)
{
    if(n <= 0) // checks if array size is negative
    {
        return -1;
    }
    int maxPos = 0;
    string max = a[0]; // sets max as first element
    for(size_t i = 0; i < n; i++) // loops thorugh array
    {
        if(a[i] > max) //checks if element is larger than the max
        {
            maxPos = i; // changes max to new value
            max = a[i];
        }
    }
    return maxPos;
}

// move element at pos to the end of array and everything else shifts left
int rotateLeft(string a[], int n, int pos)
{
    if(n < 0 || pos < 0 || pos >= n) // check if array size and pos is negative and if pos is over the array size (n)
    {
        return -1;
    }
    string temp = a[pos]; // creates temp var to store string at pos
    for(size_t i = pos; i < n-1; i++) // loops through array
    {
        a[i] = a[i+1]; //shifts the array elements after pos to the left
    }
    a[n-1] = temp; //sets last element in array to seleced element
    return pos;
}

// counts the number of sequences of 1+ consecutive items
int countRuns(const string a[], int n)
{
    if(n < 0) // checks if array size is negative
    {
        return -1;
    } else if (n == 0) //checks if array is empty
    {
        return 0;
    }
    
    int count = 1;
    int i = 0;
    while(i < n-1) // loops through array
    {
        if(a[i] != a[i+1]) //checks if the string changes value
        {
            count++; //adds 1 if string changes value
            i++;
        } else {
            i++;
        }
    }
    return count;
}

// reverse order of elements of array 
int flip(string a[], int n)
{
    if(n < 0) //checks if array size is negative
    {
        return -1;
    }
    for(size_t i = 0; i < n/2; i++) //loops through half the array
    {
        string temp = a[i]; //switches front and end strings
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

//return first pos that the 2 arrays are different
int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0) // checks if either array size is negative
    {
        return -1;
    }
    int n = (n1 < n2) ? n1 : n2; //sets n to the smaller value between n1 and n2
    for(size_t i = 0; i < n; i++) // loops through array
    {
        if(a1[i] != a2[i]) // if they are not equal return that pos
        {
            return i;
        }
    }
    return n;
}

// return the pos where the sequence of a2 appears in a1
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0 || n2 > n1) // checks if array sizes are negative or if the sequence of n2 is larger than a1 array
    {
        return -1;
    } else if (n2 == 0)
    {
        return 0;
    }
    int count = 0;
    int j = 0;
    for(size_t i = 0; i < n1; i++) // loops through array
    {
        if (a1[i] == a2[j]) // checks if values from both arrays are equal
        {
            count++; // increments if values equal
            j++;
        } else {
            count = 0; //reset f values arent equal
        }
        if(count == n2) //if counter equal to the size of sequnce returns the starting pos in a1
        {
            return i-n2+1;
        }

    }
    return -1;
}

// returns smallest pos in a1 that is also in a2
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0) // checks if array sizes are negative
    {
        return -1;
    }
    int smallestPos = n1;
    for(size_t i = 0; i < n1; i++) // loops through a1 array
    {
        for(size_t j = 0; j < n2; j++) //loops through a2 array
        {
            if(a1[i] == a2[j] && i < smallestPos) // checks if values are equal and if the pos is smallest pos value
            {
                smallestPos = i;
            }
        }
    }
    if(smallestPos == n1) //if smallest pos doesnt change no element is equal 
    {
        return -1;
    }
    return smallestPos;
}

// rearange elements based their value < or > than separator, < in the front and rest behind, returns first pos where it is not less than value
int separate(string a[], int n, string separator)
{   
    if(n < 0) // checks if array size is negative
    {
        return -1;
    }
    int count = 0;
    int greaterCount = 0;
    for(size_t i = 0; i < n; i++) // loops through array
    {
        // counts the number of less thans and greater or equal to separator values
        if (a[i] < separator) 
        {
            count++;
        } else {
            greaterCount++;
        }
    }
    if(count == 0) // if all values >=seperator return 0
    {
        return 0;
    }
    for(size_t j = 0; j < greaterCount; j++) // loops for the number of times there are values >= separator
    {
        int k = 0;
        while(a[j] >= separator && k <= greaterCount) // loops for values >= separator 
        {
            rotateLeft(a, n, j); //shifts the value at j to the end and rest one left
            k++;
        }
    }
    return count;
}

int main()
	{
        //Test Cases
	    string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	    assert(lookup(h, 7, "doug") == 5);
	    assert(lookup(h, 7, "donald") == 2);
	    assert(lookup(h, 2, "donald") == -1);
	    assert(positionOfMax(h, 7) == 3);

	    string g[4] = { "melania", "kamala", "jd", "usha" };
	    assert(differ(h, 4, g, 4) == 2);
	    assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
	    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");

	    string e[4] = { "donald", "tim", "", "doug" };
	    assert(subsequence(h, 7, e, 4) == 2);

	    string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	    assert(countRuns(d, 5) == 2);
	
	    string f[3] = { "jd", "donald", "gwen" };
	    assert(lookupAny(h, 7, f, 3) == 2);
	    assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");
	
	    assert(separate(h, 7, "jd") == 3);
	
	    cout << "All tests succeeded" << endl;
	}