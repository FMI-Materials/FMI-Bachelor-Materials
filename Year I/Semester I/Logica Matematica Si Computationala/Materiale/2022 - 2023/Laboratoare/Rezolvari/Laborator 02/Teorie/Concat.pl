concat_lists([], List, List).
concat_lists([Elem|List1], List2, [Elem|List3]):-
    concat_lists(List1, List2, List3).