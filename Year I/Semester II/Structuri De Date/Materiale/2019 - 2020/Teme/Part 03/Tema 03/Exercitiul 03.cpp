#include <iostream>
using namespace std;

void count_sort(int arr[], int n)
{
    
    int out[10], count[10], max = arr[0],i;
    //count vector de frecvente 
    for (i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];//maximul pe vectorul arr
    }

    for (i = 0; i <= max; ++i)
    {
        count[i] = 0;//initializare vector de frecv cu 0
    }

    for (i = 0; i < n; i++)
    {
        count[arr[i]]++;//frecventele fiecaruia
    }
    for (i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }
    for ( i = n - 1; i >= 0; i--)
    {
        out[count[arr[i]] - 1] = arr[i];//refacere vector arr dar sortat
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = out[i];//copiere in arr vectorul sortat
    }
}
void af(int arr[], int n)//afisare
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main()
{
    //int arr[] = { 4, 2, 2, 8, 3, 3, 1 }, n = 7;
    int i, n, arr[100];
    cout << "dati n lungime vector n=";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "arr[" << i << "]=";
        cin >> arr[i];
    }
    cout << "vectorul inainte de COUNT SORT:";
    af(arr, n);
    count_sort(arr, n);
    cout << "vectorul dupa de COUNT SORT:";
    af(arr, n);
}