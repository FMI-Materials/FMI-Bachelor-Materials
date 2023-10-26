#include<iostream>
#include<string.h>
#define maxchar "~~~~~~~~~~~~"
using namespace std;
struct arbore
{
	char info[100];
	arbore* stang, * drept;
};
arbore* p;

char* min(char x[], char y[])
{
	if (strcmp(x,y)<0)
		return x;
	else
		return y;
}
void calcul(int n, int& r, int& doi_la_r)
{
	doi_la_r = 1;
	r = -1;
	while (doi_la_r < n)
	{
		doi_la_r *= 2;
		r++;
	}
}
arbore* creare(int niv, char a[20][20], int r, int &v, int &u, int x, int y)
{
	arbore* q=NULL;
	if (niv < r)
	{
		q = new arbore;
		q->stang = creare(niv + 1, a, r, v, u, x, y);
		q->drept = creare(niv + 1, a, r, v, u, x, y);
		strcpy_s(q->info , min(q->stang->info, q->drept->info));

	}
	else
		if (niv == r)
		{
			u++;
			if (u <= x / 2)//nr de noduri neterminale =x/2
			{
				q = new arbore;
				q->stang = creare(niv + 1, a, r, v, u, x, y);
				q->drept = creare(niv + 1, a, r, v, u, x, y);
				strcpy_s(q->info ,min(q->stang->info, q->drept->info));
			}

			else
				if (y != 0)
				{
					v++;//evidenta nodurilor terminale
					q = new arbore;
					strcpy_s(q->info, a[v]);
					q->stang = q->drept = NULL;
				}
		}
				else
				{
					v++;
					q = new arbore;
					strcpy_s(q->info ,a[v]);
					q->stang = q->drept = NULL;
				}
		
	return q;
}
void cautare(arbore* q)
{
	if (q->stang == NULL)
		strcpy_s(q->info , maxchar);
	else
		if (strcmp(q->info, maxchar)!=0)
		{
			if (strcmp(q->stang->info , q->info)==0)
				cautare(q->stang);
			else
				cautare(q->drept);
			strcpy_s(q->info ,min(q->stang->info, q->drept->info));

		}

}

int main()
{
	int n, r, x, y, doi_la_r, u, v, i;
	char a[20][20];
	cout << "n= ";
	cin >> n;
	cin.get();
	cout << "sirul: " << endl;
	for (i = 1; i <= n; i++)
	{
		cout << "a[" << i << "]=";
		cin.getline(a[i], 20);
		
	}
	
	calcul(n, r, doi_la_r);
	
	y = doi_la_r-n;//nr de varfuri de pe nivelul r
	x = n - y;//nr de varfuri de pe nivelul r+1 (x+y=n=> x=n-y)
	u = v = 0;
	
	p = creare(0, a, r, v, u, x, y);
	
	
	strcpy_s(a[1], p->info);
	
	for (i = 2; i <= n; i++)
	{
		
		cautare(p);
		strcpy_s(a[i], p->info);
	}
	cout << "sirul ordonat: " << endl;
	for (i = 1; i <= n; i++)
		cout << a[i] << " ";
	
}