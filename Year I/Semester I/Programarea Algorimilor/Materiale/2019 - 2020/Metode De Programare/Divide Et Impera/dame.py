from itertools import permutations
n=int(input())
l=range(1,n+1)
x=y=0
ok=0
ok2=1
lista=list()
for i in permutations(l):
  ok2=1
  ok=0
  x=y=0
  for z in i:
    if ok==0:
      if x!=0:
        y=z
      else:
        x=z
    if ok==1:
      y=z
    if x!=0 and y!=0:
      ok=1
      if abs(x-y)<2:
        ok2=0
        lista=[]
        break
      else:
        lista.append(x)
        x=y
  if ok2==1:
    lista.append(x)
    indice_tabla=0
    print("********************")
    for k in lista:
      tabla = [0] * (n)
      tabla[k-1]=1
      print(tabla)