def fis_dict(numef):
    f=open(numef, "r")
    l=[]
    for line in f:
        v=line.split()
        d={}
        d['plecare']=v[0]
        d['sosire']=v[2]
        d['ora_plecare']=v[3]
        d['ora_sosire']=v[4]
        l.append(d)
    f.close()
    return l
def timp_c(ora_p, ora_s):
    x=ora_p.split(":")
    y=ora_s.split(":")
    s=60*int(y[0])+int(y[1])-60*int(x[0])-int(x[1])
    h=s//60
    m=int((s/60-h)*60)


    if h*60+m>1439:
        print("calatoria depaseste o zi")
        return None
    else:
        return h,m
def calatorie(l):
    L=[]


print(fis_dict('program.txt'))
print(timp_c("00:00", "00:00"))