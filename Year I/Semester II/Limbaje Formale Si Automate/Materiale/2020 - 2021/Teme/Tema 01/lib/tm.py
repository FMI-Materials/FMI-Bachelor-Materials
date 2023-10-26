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

class TM():
    def __init__(self, q, s, g, d, q0, qa, qr):
        self.q = q
        self.s = s
        self.g = g
        self.d = d
        self.q0 = q0
        self.qa = qa
        self.qr = qr

        self.blank = self.g[-1]
        self.tape = []

    def __repr__(self):
        return f"Q: {self.q}\n" \
               f"Σ: {self.s}\n" \
               f"Γ: {self.g}\n" \
               f"δ: {self.d}\n" \
               f"q0: {self.q0}\n" \
               f"qa: {self.qa}\n" \
               f"qr: {self.qr}"

    def __str__(self):
        return self.__repr__()

    def run(self, input):
        self.tape = list(input)

        def tape_val(pos):
            if pos >= len(self.tape):
                self.tape.append(self.blank)
            return self.tape[pos]

        pos = 0
        curr_state = self.q0

        while curr_state not in [self.qa, self.qr]:
            key = (curr_state, tape_val(pos))
            if key not in self.d.keys():             # If we don't have the possibility to do this transition,
                print("STUCK")                       # it means that we are stuck.
                return

            (qn, gn, dir) = self.d[key]
            self.tape[pos] = gn
            curr_state = qn

            if dir == "L":                           # Head moves to the left
                if pos > 0:                          # if it is possible.
                    pos -= 1
            elif dir == "R":                         # Head moves to the right.
                if pos >= len(self.tape):
                    self.tape.append(self.blank)
                pos += 1

        if curr_state == self.qa:                    # We are on the accept state.
            print("OK")
        else:
            print("NOT OK")                           # We are on the reject state.
