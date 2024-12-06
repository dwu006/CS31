#include<iostream>

using namespace std;

// int main()
// {
//         int arr[3] = { 5, 10, 15 };
//         int* ptr = arr;

//         *ptr = 30;
//         ptr++;
//         *ptr = 20;
//         ptr++;
//         *ptr = 10;

//         ptr = arr;

//         while (ptr <= arr+2)
//         {
//             cout << *ptr << endl; 
//             ptr++;   // print values
//         }
// }

// void findMax(int arr[], int n, int*& pToMax)
// {
//     if (n <= 0) 
//         return;      // no items, no maximum!

//     pToMax = arr;

//     for (int i = 1; i < n; i++)
//     {
//         if (arr[i] > *pToMax)
//                 pToMax = arr + i;
//     }
// }       

// int main()
// {
//     int nums[4] = { 5, 3, 15, 6 };
//     int* ptr = &nums[0];

//     findMax(nums, 4, ptr);
//     cout << "The maximum is at address " << ptr << endl;
//     cout << "It's at position " << ptr - nums << endl;
//     cout << "Its value is " << *ptr << endl;
// }

// void computeCube(int n, int* ncubed)
// {
//     *ncubed = n * n * n;
// }

// int main()
// {
//     int a = 1;
//     int* ptr = &a;
//     computeCube(5, ptr);
//     cout << "Five cubed is " << *ptr << endl;
// }

bool strequal(const char str1[], const char str2[])
{
    while (*str1 != 0  &&  *str2 != 0)  // zero bytes at ends
    {
        cout << str1 << endl;
        cout << str2 << endl;
        if (*str1 != *str2)  // compare corresponding characters
            return false;
        str1++;            // advance to the next character
        str2++;
        
    }
    cout << "str1: " << str1 << endl << "str2: " << str2 << endl;

    return *str1 == '\0' && *str2 == '\0';   // both ended at same time?
}

int main()
{
    char a[15] = "Alex B";
    char b[15] = "Alex B.";

    if (strequal(a,b))
        cout << "They're the same person!\n";
    else
        cout << "doesnt work";
}

// int* nochange(int* p)
// {
//     return p;
// }

// int* getPtrToArray(int& m)
// {
//     int anArray[100];
//     for (int j = 0; j < 100; j++)
//         anArray[j] = 100-j;
//     m = 100;
//     return nochange(anArray);
// }

// void f()
// {
//     int junk[100];
//     for (int k = 0; k < 100; k++)
//         junk[k] = 123400000 + k;
//     junk[50]++;
// }

// int main()
// {
//     int n;
//     int* ptr = getPtrToArray(n);
//     f();
//     for (int i = 0; i < 3; i++)
//         cout << *ptr << ' ';
//     for (int i = n-3; i < n; i++)
//         cout << *ptr << ' ';
//     cout << endl;
// }

// const char* findTheChar2(const char str[], char chr)
// {
//     for (int k = 0; *(str+k) != '\0'; k++)
//         if (*(str+k) == chr)
//             return (str+k);

//     return nullptr;
// }


// const char* findTheChar(const char str[], char chr)
// {
//     for (int k = 0; str[k] != 0; k++)
//         if (str[k] == chr)
//             return &str[k];

//     return nullptr;
// }

// const char* findTheChar3(const char str[], char chr)
// {
//     while(*str != '\0')
//     {
//         if(*str == chr){return str;}
//         str++;
//     }
//     return nullptr;
// }


// int main()
// {
//     char str[20] = "hellosaerhbaehaehs";
//     cout << findTheChar(str, 'a') << endl;
//     cout << findTheChar2(str, 'a') << endl;
//     cout << findTheChar3(str, 'a');
// }

// int* maxwell(int* a, int* b)
// {
//     if (*a > *b)
//         return a;
//     else
//         return b;
// }

// void swap1(int* a, int* b)
// {
//     int* temp = a;
//     a = b;
//     b = temp;
// }

// void swap2(int* a, int* b)
// {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// int main()
// {
//     int array[6] = { 5, 3, 4, 17, 22, 19 };

//     int* ptr = maxwell(array, &array[2]);
//     *ptr = -1;
//     ptr += 2;
//     ptr[1] = 9;
//     *(array+1) = 79;

//     cout << &array[5] - ptr << endl;

//     swap1(&array[0], &array[1]);
//     swap2(array, &array[2]);

//     for (int i = 0; i < 6; i++)
//         cout << array[i] << endl;
// } 

// void removeS(char* ptr)
// {
//     char* temp = ptr;
//     while(*ptr != '\0')
//     {
//         if(tolower(*temp) != 's'){*ptr = *temp; ptr++;}
//         temp++;
//     }
// }

// int main()
// {
//     char msg[50] = "She'll blossom like a massless princess.";
//     removeS(msg);
//     cout << msg;  // prints   he'll bloom like a male prince.
// }