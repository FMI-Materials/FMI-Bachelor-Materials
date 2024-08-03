def  caut(cuv, nume_out, *nume_in ):
    g=open(nume_out,"w")
    for x in nume_in:
        f=open(x, "r")
        li=1
        a=""
        for line in f:
            if cuv in line:
                a+=str(li)+" "
            li+=1
        if a!="":
            g.write(x+" "+a+"\n")
        else:
            g.write(x+" "+"nu s-a gasit cuvantul \n")
        f.close()
    g.close()

caut("ana","scrie.txt","bacovia.txt", "eminescu.txt")