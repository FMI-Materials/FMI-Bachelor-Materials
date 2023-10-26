#!/usr/bin/env python3

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

from lib.parser import TMParser, ParserError
import sys


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: ./tm_simulator.py tm_config_file input")
        sys.exit(1)
    config_file_name = sys.argv[1]
    input = sys.argv[2]
    
    with open(config_file_name, "r") as f:
        try:
            parser = TMParser(f)
            tm = parser.parse()
            tm.run(input)
            # The tape contains only blanks following the last symbol from Σ - on the tape.
            tape = "".join(tm.tape).rstrip(tm.blank)
            # We remove the blanks from the end of the tape.
            print("Tape:", tape)
            # The result = the number of characters on the tape = length(tape).
            print("Decodified number:", len(tape))

        except ParserError as e:
            print(e)
