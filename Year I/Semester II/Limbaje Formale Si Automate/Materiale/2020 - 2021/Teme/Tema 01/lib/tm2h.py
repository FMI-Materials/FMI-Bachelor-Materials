"""
Copyright © 2021 Alexandru-Sergiu Marton <alexandru.marton@s.unibuc.ro>
Copyright © 2021 Andreea Diana Gherghescu <andreea.gherghescu@s.unibuc.ro>
Copyright © 2021 Daria-Mihaela Broscoțeanu <daria.broscoteanu@s.unibuc.ro>

This file is part of Examen CS112.

Examen CS112 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Examen CS112 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Examen CS112.  If not, see <https://www.gnu.org/licenses/>.
"""

from lib.tm import TM


class TM2H(TM):
    def run(self, input):
        self.tape = list(input)

        def tape_val(pos):
            """
            Return the character at a given position on the tape. If the position is higher than the current length of
            the tape, add one blank and return that.
            :param pos: The position to look at on the tape.
            :return: The character at the given position.
            """
            if pos >= len(self.tape):  # If we need to go further on blank positions we add them to the tape.
                self.tape.append(self.blank)
            return self.tape[pos]

        head1, head2 = 0, 0   # At first, we start with both heads at the leftmost position of the tape,
        curr_state = self.q0  # and that is state q0.

        while curr_state not in [self.qa, self.qr]:   # If we are not on a deciding state,
            key = (curr_state, tape_val(head1), tape_val(head2))
            if key not in self.d.keys():              # If we don't have the possibility to do this transition,
                print("STUCK")                        # it means that we are stuck.
                return

            (qn, write1, write2, dir1, dir2) = self.d[key]

            """
            qn: next state
            write1: the character that head1 will write
            write2: the character that head2 will write
            dir1: the direction head one will go after writing
            dir2: the direction head two will go after writing
            """

            self.tape[head1] = write1       # Head one writes a character in his position.
            self.tape[head2] = write2       # Head two writes a character in his position.
            curr_state = qn                 # We move to the next state qn.

            if dir1 == "L":                 # Head1 moves to the left
                if head1 > 0:               # if it is possible.
                    head1 -= 1
            elif dir1 == "R":               # Head1 moves to the right
                if head1 >= len(tape):      # if it is possible.
                    tape.append(self.blank)
                head1 += 1

            if dir2 == "L":                 # Head2 moves to the left
                if head2 > 0:               # if it is possible.
                    head2 -= 1 
            elif dir2 == "R":               # Head2 moves to the right
                if head2 >= len(tape):      # if it is possible.
                    tape.append(self.blank)
                head2 += 1

        if curr_state == self.qa:           # We are on the accept state.
            print("OK")
        else:                               # We are on the reject state.
            print("NOT OK")
