def citire():
    f=open("copaci.in","r")
    line=f.readline()
    v=line.split()
    sjx=int(v[0])
    sjy=int(v[1])
    line = f.readline()
    v = line.split()
    dsx = int(v[0])
    dsy = int(v[1])
    #a=(dsx-sjx)*(dsy-sjy)
    copac=[]
    for line in f:
        v = line.split()
        x = int(v[0])
        y = int(v[1])
        copac.append((x,y))
    return sjx, sjy, dsx, dsy, copac
def dr_a_max(sjx, sjy, dsx, dsy):
    global l
    max=0

    for x in l:
        a=x[0]
        b=x[1]
        if sjx<a<dsx and sjy<b<dsy:
            ok=True
            dr_a_max(sjx, b, a, dsy)
            dr_a_max(sjx, sjy, a, b)
            dr_a_max(a, sjy, dsx, b)
            dr_a_max(a, b, dsx, dsy)

sjx, sjy, dsx, dsy, copac=citire()