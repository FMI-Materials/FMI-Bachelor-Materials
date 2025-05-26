import casadi as ca
import matplotlib.pyplot as plt
import numpy as np


def bsplines_casadi(knot, deg):
    """
    Python/CasADi version of the MATLAB function [b,knot] = bsplines_casadi(knot, deg).
    
    knot : list or array of knot points
    deg  : spline degree
    
    Returns
    -------
    b    : a list-of-lists of CasADi Function objects, representing B-spline basis functions
    knot : the sorted knot array
    """

    # 1) Sort and ensure real values of the knot vector
    knot = sorted(float(x) for x in knot)
    m = len(knot)

    # 2) Check for the minimum knot size based on spline degree
    if m < deg + 2:
        raise ValueError(
            "The knot size (m) and the degree (deg) must satisfy m >= deg + 2."
        )

    # 3) Define a local Heaviside function via CasADi if_else
    #    heaviside(z) = 1 if z >= 0, else 0
    def heaviside(z):
        return ca.if_else(z >= 0, 1, 0)

    # 4) Define the CasADi symbolic variable
    x = ca.SX.sym("x", 1)

    # 5) Prepare a nested list b[k][i], where
    #    k goes from 0 to deg (instead of 1 to deg+1 as in MATLAB),
    #    i will range accordingly for each k.
    b = []
    # For each k in [0..deg], we will have up to (m - k) functions
    for k_ in range(deg + 1):
        b.append([None] * (m - k_))

    # 6) Build the B-spline functions of order 1 (equivalent to k=1 in MATLAB)
    #    b[0][i] corresponds to b{k=1}{i+1} in MATLAB
    #    for i in [0..m-2] <-> MATLAB i in [1..m-1]
    for i in range(m - 1):
        # heaviside(x - knot[i]) - heaviside(x - knot[i+1])
        expr = heaviside(x - knot[i]) - heaviside(x - knot[i + 1])
        b[0][i] = ca.Function(
            f"f_1_{i+1}",  # Function name: "f_1_i" in MATLAB was i in [1..m-1]
            [x], 
            [expr],
        )

    # 7) Apply the recursive B-spline relation for orders 2..(deg+1)
    #    (eq. (2.1) from the original code reference)
    #    In MATLAB: for k=2:deg+1, for i=1:m-k
    #    Here:      for k_ in [1..deg], i in [0..(m - 1 - k_)]
    for k_ in range(1, deg + 1):
        # k_ in [1..deg], which corresponds to B-spline order k_+1 in MATLAB terms
        # so the function name is "f_{k_+1}_{i+1}" to match original naming
        for i in range(m - 1 - k_):
            # We need to evaluate b[k_-1][i] and b[k_-1][i+1] at the symbolic x.
            # In MATLAB: b{k-1}{i}(x) => b[k_-2][i-1] in zero-based
            # But we also need to *call* that CasADi function to get a symbolic expr.

            # First sub-term: 
            denom1 = knot[i + k_] - knot[i]
            if denom1 != 0:
                left_val = b[k_ - 1][i](x)[0] * (x - knot[i]) / denom1
            else:
                left_val = 0

            # Second sub-term:
            denom2 = knot[i + k_ + 1] - knot[i + 1]
            if denom2 != 0:
                right_val = b[k_ - 1][i + 1](x)[0] * (knot[i + k_ + 1] - x) / denom2
            else:
                right_val = 0

            expr = left_val + right_val

            b[k_][i] = ca.Function(
                f"f_{k_+1}_{i+1}",
                [x],
                [expr],
            )

    return b, knot


deg = 4
n_handle = 11
Time = 30


knot_array = np.concatenate((
    np.zeros(deg + 1),
    np.linspace(1.0 / (n_handle - deg),
                (n_handle - deg - 1) / (n_handle - deg),
                n_handle - deg - 1),
    np.ones(deg + 1)
)) * Time

# Call the Python version of bsplines_casadi
b, knot_sorted = bsplines_casadi(knot_array, deg)

# In MATLAB, k=5 is the "fifth order" set of B-spline basis functions.
# IMPORTANT: In Python, b[0] holds the order-1 splines, b[1] holds order-2, etc.
# Hence b[k-1] is the set for "order k".
k_matlab = 5
k_python = k_matlab - 1

# Create a time vector (equivalent to "tt = linspace(min(knot),max(knot)-1e-4,1e3);")
tt = np.linspace(np.min(knot_sorted), np.max(knot_sorted) - 1e-4, int(1e3))

# Plot each B-spline in b[k_python]
plt.figure()
plt.title(f"B-splines of order {k_matlab} (deg={deg})")
plt.xlabel("t")
plt.ylabel("B-spline value")
plt.grid(True)

for i, spline_func in enumerate(b[k_python]):
    # Evaluate the CasADi function at all points in tt
    # spline_func is a CasADi Function. We can evaluate it point by point:
    y_vals = [spline_func([t])[0].full() for t in tt]
    y_vals = np.array([elem[0, 0] for elem in y_vals])
    plt.plot(tt, y_vals, label=f"Spline_{i+1}")

plt.legend()
plt.show()

#  %%
# Equivalent to P = rand(2, n_handle);
P = np.random.rand(2, n_handle + 1) 

# We'll accumulate the resulting [x; y] positions in a list.
z_list = []

# Loop over each time "t" in "tt"
for t_ in tt:
    # We'll build a small vector "bs" that contains the B-spline evaluations
    # at order "k_python" for each i in [0..len(b[k_python]) - 1].
    bs_vals = []

    for i_ in range(len(b[k_python])):
        # b[k_python][i_] is a CasADi Function. Evaluate at t_:
        if b[k_python][i_] is not None:
            val_dm = b[k_python][i_]([t_])  # returns a DM (1×1)
            val_scalar = val_dm.full()[0, 0]
        else:
            val_scalar = 0        
        bs_vals.append(val_scalar)

    # Convert "bs_vals" (a Python list) into a NumPy array of shape (n_handle,)
    bs_array = np.array(bs_vals)

    # In MATLAB, P * bs' is shape (2,1). In Python, we do P.dot(bs_array) => shape (2,).
    z_col = P.dot(bs_array)

    # Append this 2D point to the list
    z_list.append(z_col)

# "z_list" is now a list of length len(tt), each element is shape (2,).
# To plot, it's easiest to convert to a NumPy array of shape (len(tt), 2), 
# then transpose if you want coordinates in z[0,:] / z[1,:].
z = np.array(z_list).T  # final shape => (2, len(tt))

# Plot the resulting trajectory
plt.figure()
plt.grid(True)
plt.plot(z[0, :], z[1, :], label="B-spline Curve")

# Scatter the original control points from P
plt.scatter(P[0, :], P[1, :], color="red", label="Control Points")

plt.legend()
plt.title("B-spline Curve and Control Points")
plt.show()


 