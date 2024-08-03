"""
1.	Se dă un vector a=(a1,…an) de tip munte (există un indice i astfel încât a1<a2<…<ai > ai+1>…>an;
ai se numește vârful muntelui). Propuneți un algoritm O(log n) care determină vârful muntelui
(în calculul complexității algoritmului nu se consideră și citirea vectorului)
"""
def varf(a, p, u):
	if u-p<2:
		return max(a[p],a[u])

	mij=(p+u)//2
	if a[mij-1]<a[mij] and a[mij]>a[mij+1]:
		return a[mij]
	if a[mij-1]<a[mij] and a[mij]<a[mij+1]:
		return varf(a,mij+1,u)
	return varf(a,p,mij-1)

def get_varf(v):
	return varf(v,0,len(v)-1)

ls=[6,4,2]
print(get_varf(ls))