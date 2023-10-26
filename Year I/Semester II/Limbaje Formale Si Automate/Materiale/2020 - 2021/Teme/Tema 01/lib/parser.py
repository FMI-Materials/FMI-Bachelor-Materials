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

from lib.tm2h import TM2H
from lib.tm import TM
from lib.utils import flatten
from enum import Enum


class BlockError(Enum):
    UNEXPECTED_EOF = "Unexpected EOF."
    INVALID_END = "Invalid block end syntax."
    COMMENT_START = "Comments can only start at the beginning of the line."
    INVALID_SYNTAX = "Invalid syntax."


class ParserError(Exception):
    def __init__(self, line, message):
        self.line = line
        self.message = message

    def __str__(self):
        return f'Error at line {self.line}: {repr(self.message)}'

    def __repr__(self):
        return self.__str__()


class ColonParser:
    """
    A parser that understands a configuration file with sections of the general form "Head: body".
    """
    def __init__(self, file):
        self.file = file
        # We need a place to store temporarily rejected lines by one of the colon parsers.
        self.backbuf = []
        self.lineno = 0

    def raise_error(self, error_message):
        raise ParserError(self.lineno, error_message)

    def parse_colon(self, topic):
        """
        Parse a block from the configuration file.

        The configuration format for Turing Machines follows a simple
        `Variable: Value` rule. Each `X: y` pair is called a "rule", composed
        of a "head" (`X`) and a "body" (`y`).

        A rule can span multiple lines, only if the part of its body that in
        on different rows than its head is indented with at least a space
        character. Empty lines are ignored.

        :param topic: The value that the head of the block must have.
        :return: An array containing the non-empty lines of the block.
        """
        # If we have lines in the buffer, take the last one from there, else try to read a new one.
        if len(self.backbuf) > 0:
            line = self.backbuf.pop()
        else:
            line = self.file.readline()
        if len(line) == 0:
            self.raise_error("Reached EOF.")

        self.lineno += 1
        if line[0].isspace():
            if not line.isspace():
                self.raise_error("Topic line must start with no whitespace.")
            else:
                return self.parse_colon(topic)

        if not line.startswith(topic + ":"):
            self.raise_error("Topic doesn't match!")

        # First element of the results will be the content right after the colon, on the same line.
        res = [line.split(":", 1)[1].strip()]

        # Read the following lines and if no new block is started, or the line isn't empty, add it to the results.
        line = self.file.readline()
        while len(line) > 0 and line[0].isspace():
            if not line.isspace():
                res.append(line.strip())
            line = self.file.readline()
        if len(line) > 0:
            self.backbuf.append(line)
        return res


class TMParser(ColonParser):
    """
    A specialized type of colon parser that works for Turing Machines with one tape and one head.
    """
    def __init__(self, file):
        super().__init__(file)
        self.file = file

    def multi_values(self, topic, sep=","):
        """
        Parse a topic and split the results by commas.
        :param topic: The name of the head to parse.
        :param sep: The string to use as a separator for the values in the body.
        :return: An array with all the separated values.
        """
        res = self.parse_colon(topic)
        res = [[x.strip() for x in row.split(sep)] for row in res]
        return flatten(res)

    def single_value(self, topic):
        """
        Parse a topic and treat the contents as a single value.
        :param topic: The name of the head to parse.
        :return: A single value
        :exception: Throws in case the block contains multiple rows.
        """
        res = self.parse_colon(topic)
        if len(res) != 1:
            self.raise_error(f"Invalid format for {topic}.")
        return res[0].strip()

    def parse_states(self):
        return self.multi_values("Q")

    def parse_alphabet(self):
        return self.multi_values("Σ")

    def parse_tape_alphabet(self):
        return self.multi_values("Γ")

    def parse_transitions(self):
        res = self.parse_colon("δ")

        # Tranform the content of res, which at this point looks like this: ["q0, 0 -> q0, 0, R", ...], into a
        # list of tuples fit for a dictionary conversion: [(('q0', '0'), ('q0', '0', 'R')), ...]
        res = [tuple(tuple(map(lambda y: y.strip(), x.strip().split(",")))
                     for x in row.split("->"))
               for row in res]

        # Encode the transitions as a dictionary so that it can be treated as a function.
        return dict(res)

    def parse_start_state(self):
        return self.single_value("q0")

    def parse_accept_state(self):
        return self.single_value("qa")

    def parse_reject_state(self):
        return self.single_value("qr")

    def validate_transitions(self, q, g, d):
        for (k, v) in d.items():
            if len(k) != 2 or len(v) != 3:
                self.raise_error("Transitions are defined on Q x Γ -> Q x Γ x {L, R}.")
            if k[0] not in q or v[0] not in q:
                self.raise_error("Transition states are not in Q.")
            if k[1] not in g or v[1] not in g:
                self.raise_error("Transition symbols not in Γ.")
            if v[2] not in ["L", "R"]:
                self.raise_error("Transition direction not in {L, R}.")

    def parse(self):
        q = self.parse_states()
        s = self.parse_alphabet()
        g = self.parse_tape_alphabet()
        d = self.parse_transitions()
        q0 = self.parse_start_state()
        qa = self.parse_accept_state()
        qr = self.parse_reject_state()

        if q0 not in q:
            self.raise_error("Q0 not in Q.")
        if qa not in q:
            self.raise_error("Qaccept not in Q.")
        if qr not in q:
            self.raise_error("Qreject not in Q.")

        # Last symbol from Γ is treated as the blank symbol.
        if g[-1] in s:
            self.raise_error("Blank symbol can't be in Σ.")

        self.validate_transitions(q, g, d)

        return TM(q, s, g, d, q0, qa, qr)


class TM2HParser(TMParser):
    """
    A specialized type of colon parser that works for Turing Machines with one tape and two heads.
    """
    def validate_transitions(self, q, g, d):
        """
        :param q: states
        :param g: gamma
        :param d: delta - transitions
        """
        for (k, v) in d.items():
            if len(k) != 3 or len(v) != 5:
                self.raise_error("Transitions are defined on Q x Γ² -> Q x Γ² x {L, R, S}².")
            if k[0] not in q or v[0] not in q:
                self.raise_error("Transition states are not in Q.")
            if k[1] not in g or k[2] not in g \
                    or v[1] not in g or v[2] not in g:
                self.raise_error("Transition symbols not in Γ.")
            if v[3] not in ["L", "R", "S"] or v[4] not in ["L", "R", "S"]:
                self.raise_error("Transition direction not in {L, R}.")

    def parse(self):
        tm = super().parse()
        return TM2H(tm.q, tm.s, tm.g, tm.d, tm.q0, tm.qa, tm.qr)
