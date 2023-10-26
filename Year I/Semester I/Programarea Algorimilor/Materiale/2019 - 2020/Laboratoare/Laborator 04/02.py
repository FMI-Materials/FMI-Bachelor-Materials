from math import pi
def lungime_arie_cerc (r):
    a=pi*r*r
    l=2*pi*r
    return a,l
A,L=lungime_arie_cerc(2)
print(A,L)