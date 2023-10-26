#include <iostream>
using namespace std;

void count_sort(int arr[],  int n, int place)
{
    const int max = 10;
    
    int i, out[100], count[max];

    for (i = 0; i < max; ++i)
        count[i] = 0;

    for (i = 0; i < n; i++)
        count[(arr[i] / place) % 10]++;

    for (i = 1; i < max; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        out[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = out[i];
}
void radix_sort(int arr[], int n)
{
    int max = arr[0], i, place ;
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    for (place = 1; max / place > 0; place *= 10)
        count_sort(arr, n, place);
}
void af(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main()
{
    int array[] = { 121, 432, 564, 23, 1, 45, 788 };
    int n = 7;
    radix_sort(array, n);
    af(array, n);
}