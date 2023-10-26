def mediana2(v,w):
    print(v,w)
    #if len(v)<=2 and len(w)-len(v)<2:
    if len(v)<=2 or len(w)<2:

        #interclasare
       a=0
       b=0
       x=[]
       while a<len(v) and b<len(w):
           if v[a]<w[b]:
               x.append(v[a])

               a+=1
           else:
               x.append(w[b])

               b+=1
       while a<len(v):
            x.append(v[a])
            a+=1
       while b<len(w):
            x.append(w[b])
            b+=1
       k=len(x)//2

       if len(x) % 2 == 0:

           return(x[k - 1] + x[k]) / 2
       else:
           return x[k]


    i=len(v)//2
    j=len(w)//2
    if len(v)%2==0:

            m1=(v[i-1]+v[i])//2
    else:
            m1=v[i]

    if len(w)%2==0:
            m2 = (w[j - 1] + w[j]) // 2
    else:
        m2=w[j]



    if m1<m2:
        v=v[i:]
        w=w[:(len(w)-i)]
    else:

        w=w[i:]
        if len(v)%2!=0:
            v=v[:i+1]
        else:
           v=v[:i]

    return mediana2(v,w)

x=[4,6,8,10,12,14,16,18,20]
y=[1,23,25]
#x=[2,3,9,13,20,50]
#y=[2,5,6,10,30,35]
#x=[1,3,8,9,15]
#y=[7,11,18,19,21,25]

print(mediana2(x,y))
