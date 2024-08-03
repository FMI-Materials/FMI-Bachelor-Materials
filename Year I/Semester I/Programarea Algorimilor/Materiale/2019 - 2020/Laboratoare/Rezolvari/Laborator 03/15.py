f=open("persoane.txt","r")
l=[]
for line in f:
   d=[]
   v=line.split(',')
   for i in range(5):
       if i==0 or i==1:
           a=v[i].split(':')
           d[a[0]]=a[1]