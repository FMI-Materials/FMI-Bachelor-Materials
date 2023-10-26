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

from lib.parser import TM2HParser, ParserError
import sys


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: ./tm2h_validation_engine.py tm_config_file")
        sys.exit(1)
    config_file_name = sys.argv[1]
    with open(config_file_name, "r") as f:
        try:
            parser = TM2HParser(f)
            tm = parser.parse()
            print("Config is ok")
        except ParserError as e:
            print(e)
