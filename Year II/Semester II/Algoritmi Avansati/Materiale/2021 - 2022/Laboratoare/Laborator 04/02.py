from scipy.optimize import linprog

function = [1, 1, 1, 1, 1]

# deoarece inecuatiile date au semnul >= si noi avem
# nevoie de <= vom inmulti coeficientii cu (-1)
left = [[-1, -1, 0, -1, 0], [-1, 0, -1, 0, -1], [0, -1, 0, -1, -1]]
right = [-1, -1, -1]

# limitele valorilor x1, x2, x3, x4 si x5
bounds = [(0, 1), (0, 1), (0, 1), (0, 1), (0, 1)]

result = linprog(c = function, A_ub = left, b_ub = right, bounds = bounds, method = "revised simplex")

x1, x2, x3, x4, x5 = result.x
print(f"x1 = {x1}, x2 = {x2}, x3 = {x3}, x4 = {x4}, x5 = {x5}")

# obtinerea solutiei 3-aproximative

l = [x1, x2, x3, x4, x5]
boolean = [True if elem > 1/3 else False for elem in l]

print(f"x1 = {boolean[0]}, x2 = {boolean[1]}, x3 = {boolean[2]}, x4 = {boolean[3]}, x5 = {boolean[4]}")