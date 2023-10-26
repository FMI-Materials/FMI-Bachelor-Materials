val(V, [(V, A)|_], A).
val(V, [_|T], A):-
    val(V, T, A).