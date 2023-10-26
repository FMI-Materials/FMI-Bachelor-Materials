#include <bits/stdc++.h> // contine, printre altele, toate bibliotecile STL

using namespace std;

const int Nmax = 1e5 + 5; // 10^5 + 5
int A[Nmax];
int N, M, leftQ, rightQ;

void VariantaBrut()
{
    while(M--)
    {
        cin >> leftQ >> rightQ;
        int Min = INT_MAX; // constanta predefinita in C++, 2^31 - 1

        for(int i = leftQ; i <= rightQ; ++i)
            Min = min(Min, A[i]);

        cout << Min << '\n';
    }
}

void VariantapreCalcMatriceFaraMemoizareMinim()
{
    vector<vector<int>> preCalc(N + 1, vector<int> (N + 1));
    //echivalent cu a scrie preCalc[N + 1][N + 1]. Se umple automat cu zerouri

    for(int i = 1; i <= N; ++i)
        for(int j = i + 1; j <= N; ++j)
        {
            int Min = INT_MAX;
            for(int k = i; k <= j; ++k)
                Min = min(Min, A[k]);
            preCalc[i][j] = Min;
        }

    while(M--)
    {
        cin >> leftQ >> rightQ;
        cout << preCalc[leftQ][rightQ] << '\n';
    }
}


void VariantapreCalcMatriceCuMemoizareMinim()
{
    vector<vector<int>> preCalc(N + 1, vector<int> (N + 1));
    //echivalent cu a scrie preCalc[N + 1][N + 1]. Se umple automat cu zerouri

    for(int i = 1; i <= N; ++i)
    {
        preCalc[i][i] = A[i];
        for(int j = i + 1; j <= N; ++j)
            preCalc[i][j] = min(preCalc[i][j - 1], A[j]);
    }

    while(M--)
    {
        cin >> leftQ >> rightQ;
        cout << preCalc[leftQ][rightQ] << '\n';
    }
}

void VariantaSqrtDecomposition()
{
    const int blockSize = sqrt(N);
    int blocks[blockSize] = {INT_MAX};

    for(int i = 1; i <= N; ++i)
    {
        int pozBlock = (i - 1) / blockSize; // calculam asa din cauza indexarii de la 1 ca sa nu punem
        // elementele pe pozitii multiplu de blockSize in urmatorul bloc
        blocks[pozBlock] = min(blocks[pozBlock], A[i]);
    }

    while(M--)
    {
        cin >> leftQ >> rightQ;

        int ans = INT_MAX;

        while(leftQ <= rightQ && (leftQ - 1) % blockSize)
            ans = min(ans, A[leftQ++]);
        while(leftQ + blockSize - 1 <= rightQ)
        {
            ans = min(ans, blocks[leftQ / blockSize]);
            leftQ += blockSize;
        }
        while(leftQ <= rightQ)
            ans = min(ans, A[leftQ++]);

        cout << ans << '\n';
    }
}

void VariantaRMQ()
{
     vector<vector<int>> dp(N + 1, vector<int> (int(log2(N) + 10), 0));
    for(int i = 0; i < N; ++i)
        dp[i][0] = A[i];

    for(int j = 1; (1 << j) <= N; ++j)
        for(int i = 0; i + (1 << j) <= N; ++i)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);

    while(M--)
    {
        cin >> leftQ >> rightQ;
        leftQ--, rightQ--;
        int len = log2(r - l + 1);
        cout << min(dp[l][len], dp[r - (1 << len) + 1][len]) << '\n';
    }
}

void readSolve()
{
    cin >> N;
    for(int i = 1; i <= N; ++i)
        cin >> A[i];
    cin >> M;

    int varianta;
    cin >> varianta;

    switch(varianta)
    {
    case 1:
        VariantaBrut();
        break;
    case 2:
        VariantapreCalcMatriceFaraMemoizareMinim();
        break;
    case 3:
        VariantapreCalcMatriceCuMemoizareMinim();
        break;
    case 4:
        VariantaSqrtDecomposition();
        break;
    case 5:
        VariantaRMQ();
        break;
    }
}

int main()
{
    readSolve();
    return 0;
}
