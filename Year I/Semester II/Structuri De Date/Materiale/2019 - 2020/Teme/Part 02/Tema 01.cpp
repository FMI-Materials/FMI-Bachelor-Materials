#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <functional>

#define LL long long

#define MaxBubble 1e4
#define MaxCount 1e7

using namespace std;

ifstream fin("text.in");

vector<int> other;

LL get_max(vector<LL> a){
    LL maxi = -9e5;
    for(auto x: a)
        if(x>maxi) maxi = x;
    return maxi;
}

LL rand_between(LL a, LL b){
    LL r = a + ( std::rand() % ( b - a) );
    if(r<a || r>b) throw EXIT_FAILURE;
    return r;
}

int partition(vector<LL> &arr, int l, int r){
    //int pivot = r;
    //int pivot = l;
    int pivot = rand_between(l, r);

    if(pivot!=r) swap(arr[pivot], arr[r]);
    int x = arr[r], i = (l - 1);
    for (int j = l; j <= r - 1; j++)
        if (arr[j] < x){
            i++;
            swap(arr[i], arr[j]);
        }
    swap(arr[i + 1], arr[r]);
    return (i + 1);
}

void quicksort(vector<LL> &arr, int l, int r){
    if(l>=r) return;
    int pi = partition(arr, l, r);

    quicksort(arr, l, pi - 1);
    quicksort(arr, pi + 1, r);
}

void mergesort(vector<LL> &a, int l, int r){
    if(l>=r)
        return;
    int m = (l+r)/2;
    mergesort(a, l, m);
    mergesort(a, m+1, r);

    merge(a.begin() + l, a.begin() + m + 1, a.begin() + m + 1, a.begin() + r + 1, other.begin());
    for(int i=l;i<=r;++i)
        a[i] = other[i-l];
}

void countsort_by_exp(vector<LL> &a, LL exp){
    vector<LL> b;
    b.resize(a.size());

    vector<LL> count;
    count.resize(10);

    for(auto x: a)
        count[(x/exp)%10]++;

    for(int i=1;i<10;i++)
        count[i]+=count[i-1];

    for(int i=a.size()-1;i>=0;i--)
        b[--count[(a[i]/exp)%10]] = a[i];

    for(int i=0;i<a.size();i++)
        a[i] = b[i];
}

bool countsort(vector<LL> &a){

    vector<LL> b ;
    b.resize(a.size());

    LL maxi = get_max(a);

    if(maxi>MaxCount)
        return false;

    vector<LL> count;
    count.resize(++maxi);

    for(auto x: a)
        count[x]++;

    for(int i=1;i<maxi;i++)
        count[i]+=count[i-1];

    for(int i=0;i<a.size();i++)
        b[--count[a[i]]] = a[i];

    for(int i=0;i<a.size();i++)
        a[i] = b[i];

    return true;
}

void radixsort(vector<LL> &a){
    LL maxi = get_max(a);
    for (LL exp = 1; maxi/exp > 0; exp *= 10)
        countsort_by_exp(a, exp);
}

bool bubblesort(vector<LL> &a){
    bool sch;
    int n = a.size();
    if(n>MaxBubble)
        return false;
    do{
        sch = false;
        n--;
        for(int i=0;i<n;i++)
            if(a[i]>a[i+1]){
                swap(a[i], a[i+1]);
                sch = true;
            }
    }while(sch);
    return true;
}

void write_list(vector<LL> a, string text){
    cout<<"\n"<<text<<" ";
    for(auto e : a)
        cout<<e<<" ";
}

void write_time_elapsed(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, string sort_method){
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout<< "\nSorting list using "+sort_method+"sort"+" in: " << elapsed_seconds.count() << "s";
}

void read_list(vector<LL> &a){
    LL n, x;
    fin>>n>>x;
    for(int i=0;i<n;i++)
        a.push_back(random()%x);
}

bool check_response(vector<LL> answer){
    LL last = -9e5;
    for(auto e: answer){
        if(last>e)
            return false;
        last = e;
    }
    return true;
}

void sort_using(string sort_method, vector<LL> b){
    auto start = chrono::system_clock::now();

    if(sort_method=="quick") quicksort(b, 0, b.size()-1);
    else if(sort_method=="merge") {
        other.resize(b.size());
        mergesort(b, 0, b.size()-1);
    }
    else if(sort_method=="radix") radixsort(b);
    else if(sort_method=="count"){
        if(!countsort(b)){
            cout << "\nError: list or numbers to big, could not use countsort";
            return;
        }
    }
    else if(sort_method=="bubble"){
        if(!bubblesort(b)){
            cout << "\nError: list or numbers to big, could not use bubblesort";
            return;
        }
    }
    else{
        sort_method = "stl";
        sort(b.begin(), b.end());
    }

    auto end = chrono::system_clock::now();
    write_time_elapsed(start, end, sort_method);
    //write_list(b, "Result:");
    cout<<(check_response(b)?" (Verified)":" (Wrong answer)");
}

int main() {

    vector<LL> b;

    write_list(b, "Loaded lists from text.in:\n");

    int nr_lists;
    fin>>nr_lists;

    for(int i=0;i<nr_lists;i++){
        read_list(b);
        //write_list(b, "\nUnsorted list"+to_string(i+1)+": ");
        cout<<'\n';
        sort_using("quick", b);
        sort_using("merge", b);
        sort_using("radix", b);
        sort_using("count", b);
        sort_using("bubble", b);
        sort_using("stl", b);
        b.clear();
    }

    return 0;
}
