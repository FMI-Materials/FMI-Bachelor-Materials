def rezolva_direct(pa,ua,pb,ub):
    m = min(a[pa],a[ua],b[pb],b[ub])
    M = max(a[pa], a[ua], b[pb], b[ub])
    return (sum([a[pa],a[ua],b[pb],b[ub]]) - m - M)/2
def mediana1(v,p,u):
    if (p-u)%2==0:
        return v[(p+u)//2]
    return (v[(p+u)//2] + v[(p+u)//2+1])/2
def mediana(pa,ua,pb,ub):
    print(a[pa:ua+1],b[pb:ub+1])
    if ua-pa<2:
        return rezolva_direct(pa,ua,pb,ub)
    ma=mediana1(a,pa,ua)
    mb=mediana1(b,pb,ub)
    print(ma,mb)
    if ma==mb:
        return ma
    n=ua-pa+1
    if ma<mb:
        return mediana(pa+(n-1)//2, ua, pb,pb+n//2)
    else:
        return mediana(pa, pa+n//2, pb+(n-1)//2, ub)

a=[1,12,15,16,38,40]
b=[2,13,17,30,45,50]
n=len(a)
"""
a=[1,12,15,16,38 ]
b=[2,13,17,30,45 ]
n=len(a)
"""
print(mediana(0,n-1,0,n-1))