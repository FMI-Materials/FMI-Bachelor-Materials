from scipy.optimize import linprog

# cu ajutorul bibliotecii instalate putem sa minimizam
# o functie data, asadar pentru a a afla rezultatul maxim
# vom inmultii coeficientii ecuatiei cu (-1)
function = [-180, -200]

# coeficientii din stanga, respectiv din dreapta
# ai inecuatiilor date pentru testare
left = [[5, 4], [10, 20]]
right = [80, 200]

# limitele valorilor x si y
infinity = float('inf')
bounds = [(0, infinity), (0, infinity)]

# functia de programare liniara ce returneaza rezultatul
result = linprog(c = function, A_ub = left, b_ub = right, bounds = bounds, method = "simplex")

xMax, yMax = result.x
print(f"x={xMax}, y={yMax}")