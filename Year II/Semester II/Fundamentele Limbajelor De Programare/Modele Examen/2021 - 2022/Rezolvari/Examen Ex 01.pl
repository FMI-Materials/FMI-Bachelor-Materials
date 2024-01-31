cate_rasp_corecte([],[], _, 0).
cate_rasp_corecte([H1|T1], [H2|T2], Nume, N) :- cate_rasp_corecte(T1, T2, Nume, Numar), ((H1 == H2) -> N is Numar+1; N is Numar).

/**
? - cate_rasp_corecte([a,b,c,d,a],[a,a,a,a,a],Teodora,N).
N = 2.
*/
