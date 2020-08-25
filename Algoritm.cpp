#include <iostream>

struct Pair
{
    int key;
    int position;
};

void swap(Pair& a, Pair& b)
{
    Pair c;
    c = a;
    a = b;
    b = c;
}

int Module(int a)
{
    if (a < 0)
        a *= -1;
    return a;
}

void heapify(Pair arr[], int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l].key > arr[largest].key)
        largest = l; 
    if (r < n && arr[r].key > arr[largest].key)
        largest = r;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void HeapSort(Pair*& arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

Pair* GetSumArray(int*& arr, int n)
{
    Pair* Array = new Pair[n];
    Array[0].key = arr[0];
    Array[0].position = 0;
    for (int i = 1; i < n; i++)
    {
        Array[i].key = arr[i] + Array[i - 1].key;
        Array[i].position = i;
    }
    return Array;
}

void FindMin(Pair*& Array, int n, int& StartOfSegment, int& LengthOfSegment)
{
    int MinDifference;
    int h, l;
    MinDifference = Module(Array[0].key);
    h =  Array[0].position;
    l = -1;
    for (int i = 0; i < n - 1; i++)
    {
        if (MinDifference == 0)
            break;
        if (MinDifference > Module(Array[i + 1].key))
        {
            MinDifference = Module(Array[i + 1].key);
            h = Array[i + 1].position;
            l = -1;
        }
        if (MinDifference > Module(Array[i + 1].key - Array[i].key))
        {
            MinDifference = Module(Array[i + 1].key - Array[i].key);
            if (Array[i + 1].position > Array[i].position)
            {
                h = Array[i + 1].position;
                l = Array[i].position;
            }
            else
            {
                l = Array[i + 1].position;
                h = Array[i].position;
            }
        }
    }
    StartOfSegment = l + 1;
    LengthOfSegment = h - l;
}

void Algoritm(int*& arr, int n, int& StartOfSegment, int& LengthOfSegment)
{
    if (n <= 0)
    {
        throw std::exception("No elements in array");
        return;
    }
    if (n == 1)
    {
        StartOfSegment = 0;
        LengthOfSegment = 1;
        return;
    }
    Pair* Array;
    Array = GetSumArray(arr, n);
    HeapSort(Array, n);
    FindMin(Array, n, StartOfSegment, LengthOfSegment);
}
