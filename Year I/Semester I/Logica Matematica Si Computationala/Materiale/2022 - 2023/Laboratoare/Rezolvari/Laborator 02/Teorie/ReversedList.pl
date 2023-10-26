reverse_list_helper([], Acc, Acc).
reverse_list_helper([H|T], Acc, ReversedList):-
    reverse_list_helper(T, [H|Acc], ReversedList).
reverseList([H|T], ReversedList):-
    reverse_list_helper(T, [H], ReversedList).
