import shutil
from argparse import ArgumentParser

from uniform_cost_search import *
from a_star import *
from a_star_optimized import *
from ida_star import *


def initialize_parser():
    """
    Inițializare parser
    :return: parser
    """
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-i/--folder-in FILE_PATH '
                                             '-o/--folder-out FILE_PATH'
                                             '-n/--nsol INT'
                                             '-t/--timeout INT',
                            description='')

    parser.add_argument('-i', '--folder-in',
                        dest='fin',
                        help='Folder fisiere de input')
    parser.add_argument('-o', '--folder-out',
                        dest='fout',
                        help='Folder fisiere de output')
    parser.add_argument('-n', '--nsol',
                        dest='nsol',
                        help='primele NSOL soluții returnate de fiecare algoritm')
    parser.add_argument('-t', '--timeout',
                        dest='timeout',
                        help='Timeout algoritmi (ms)')
    return parser


def write_solutions(solutions, output_file):
    """
    Afișare soluții generate
    :param solutions: soluțiile generate
    :param output_file: locație fișier output
    """
    if len(solutions) == 0:
        return
    with open(output_file, "w") as w:
        i = 1
        for solution in solutions:
            w.write(str(solution))
            i += 1


def get_value(arg, input_title, type="string"):
    """
    :param arg: Valoare curenta
    :param input_title: Text input
    :param type: Tip variabila - int sau string
    :return: Valoare preluată din arg sau din input
    """
    if arg is not None:
        if type == "string":
            return arg
        return int(arg)
    if type == "string":
        return input(input_title)
    elif type == "int":
        while True:
            try:
                return int(input(input_title))
            except Exception:
                print("Input invalid")
    return None


def main():
    # Inițializare parser
    parser = initialize_parser()

    # Parsare argumente primite
    args = vars(parser.parse_args())

    # Preluare input folder, output folder, nsol și timeout
    input_folder = get_value(args["fin"], "Input folder: ")
    input_folder = path.realpath(join(path.dirname(path.realpath(__file__)), "..", input_folder))
    output_folder = get_value(args["fout"], "Output folder: ")
    output_folder = path.realpath(join(path.dirname(path.realpath(__file__)), "..", output_folder))
    nsol = get_value(args["nsol"], "NSOL: ", "int")
    timeout = get_value(args["timeout"], "Timeout (ms): ", "int") / 1000

    if exists(output_folder):
        shutil.rmtree(output_folder, ignore_errors=True)
    mkdir(output_folder)

    input_files = get_folder_files(input_folder)

    print(f"Folder input: {input_folder}")
    print(f"Folder output: {output_folder}")
    print(f"NSOL: {nsol}")
    print(f"Timeout: {timeout * 1000}")

    algorithms = ["ucs", "a_star", "a_star_opt", "ida_star"]
    heuristics = ["banala", "admisibila_1", "admisibila_2", "neadmisibila"]

    while True:
        try:
            algorithm = int(input("Tip algoritm (UCS [1], A* [2], A* Optimizat [3],  IDA* [4], Toate [5]):\n"))
            heuristic = int(input("Tip euristică (Banală [1], Admisibilă 1 [2], Admisibilă 2 [3], Neadmisibilă ["
                                  "4], Toate [5]):\n"))
            if 0 < heuristic <= len(algorithms) + 1 and 0 < algorithm <= len(heuristics) + 1:
                if heuristic != 5:
                    heuristics = [heuristics[heuristic-1]]
                if algorithm != 5:
                    algorithms = [algorithms[algorithm-1]]
                break
        except Exception:
            pass
        print("Nu ați ales o variantă corectă.")

    if DEBUG:
        input_files = ["example.txt"]
    for input_file in input_files:
        print(f"\nCompilare `{input_file}`...")
        # Prepare output
        current_output_folder = join(output_folder, extract_file_name(input_file))
        if not exists(current_output_folder):
            mkdir(current_output_folder)
        output_file = join(current_output_folder, input_file)

        # Inițializare graf
        try:
            g = Graph(join(input_folder, input_file))
        except Exception as e:
            print(f"Eroare `{input_file}`: {str(e)}")
            continue

        for algorithm in algorithms:
            for heuristic in heuristics:
                g.heuristic = heuristic
                solutions = []
                if algorithm == "ucs":
                    solutions = uniform_cost_search(g, nsol, timeout)
                elif algorithm == "a_star":
                    solutions = a_star(g, nsol, timeout)
                elif algorithm == "a_star_opt":
                    solutions = a_star_optimized(g, nsol, timeout)
                elif algorithm == "ida_star":
                    solutions = ida_star(g, nsol, timeout)

                if len(solutions) > 0:
                    write_solutions(solutions,  join(current_output_folder, f"{algorithm}_{heuristic}.txt"))
                    if len(solutions) > 1:
                        print(f"Au fost găsite {len(solutions)} soluții", end=" ")
                    else:
                        print(f"A fost găsită o soluție", end=" ")
                    print(
                        f"în {round(solutions[-1].time * 1000)} ms, folosind algoritmul '{algorithm}' si euristica '{heuristic}'")
                else:
                    print(f"Nu a fost găsită nicio soluție, folosind algoritmul '{algorithm}' si euristica '{heuristic}'")


if __name__ == '__main__':
    main()
