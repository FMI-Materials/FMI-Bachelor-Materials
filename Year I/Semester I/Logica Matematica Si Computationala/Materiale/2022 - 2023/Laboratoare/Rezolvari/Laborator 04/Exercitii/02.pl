word(abalone, a, b, a, l, o, n, e).
word(abandon, a, b, a, n, d, o, n).
word(anagram, a, n, a, g, r, a, m).
word(connect, c, o, n, n, e, c, t).
word(elegant, e, l, e, g, a, n, t).
word(enhance, e, n, h, a, n, c, e).

crosswd(V1, V2, V3, H1, H2, H3):-
    word(V1, _, A, _, B, _, C, _),
    word(V2, _, D, _, E, _, F, _),
    word(V3, _, G, _, H, _, I, _),
    word(H1, _, A, _, D, _, G, _),
    word(H2, _, B, _, E, _, H, _),
    word(H3, _, C, _, F, _, I, _).