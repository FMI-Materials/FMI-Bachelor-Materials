#%%
from math import prod
from typing import List, Tuple
#%%

def gcd(a: int, b: int, verbose=True, offset=''):
    """
        Euclid GCD CMMDC
    """
    if a == 0:
        if verbose:
            print(f"{offset}gcd({a}, {b}) = {b}")
        return b
    if verbose:
        print(f"{offset}gcd({a}, {b}) = ", end='')
    d = gcd(b % a, a, verbose, offset)
    return d

def lcm(a: int, b: int, verbose=True, offset=''):
    if verbose:
        print(f"{offset}lcm({a}, {b}) = {a}*{b}/gcd({a}, {b}) = {a}*{b} / {gcd(a, b, False)} = {a * b // gcd(a, b, False)}")
    return a * b // gcd(a, b, False)

assert gcd(12, 8, False) == gcd(8, 12, False) == 4
# gcd(12, 8)

#%%
def extended_gcd(a: int, b: int, verbose=True, offset=''):
    """
        return (d, coef_a, coef_b)
        CMMDC extins Euclid extins
    """
    d = gcd(a, b, False)
    a //= d
    b //= d

    def solve(x: int, y: int) -> Tuple[int, int]:
        """
        intoarce (d, a, b) a.i.
        d = a * x + b * y
        """
        coef_y = x // y
        rest = x % y
        if verbose:
            print(f"{offset}{x * d} = {y * d} * {coef_y} + {rest * d}")
        if rest == 1:
            if verbose:
                print(f"{offset}Calculam inapoi valorile:")
                print(f"{offset}{d} = {x * d} * 1 + {y * d} * -{coef_y}")
            return (1, -coef_y)

        c_y, c_r = solve(y, rest)
        c_x = c_r
        c_y -= coef_y * c_r
        if verbose:
            print(f"{offset}{d} = {x * d} * {c_x} + {y * d} * {c_y}")
        return (c_x, c_y)

    c_a, c_b = solve(a, b)
    assert c_a * a + c_b * b == 1
    return d, c_a, c_b

d, c_a, c_b = extended_gcd(12, 8, False)
assert d == c_a * 12 + c_b * 8 and d == 4

#%%
def invers_modular(element: int, modul: int, verbose=True, offset = ''):
    """
        modular inverse
    """
    if verbose:
        print(f"{offset}Calculam inversul lui {element} fata de {modul}.")
        print(f"{offset}Calculam coeficientii x si y a.i. x * {element} + y * {modul} = 1 cu euclid:")

    d, x, y = extended_gcd(modul, element, verbose, '    ' + offset)

    if d != 1:
        print(f"{element} nu este prim cu {modul}!")
        raise Exception()

    y = ((y + modul) % modul) % modul 

    if verbose:
        print(f"{offset}{y}*{element} + {x}*{modul} = 1, deci {y} este inversul lui {element} fata de {modul}.")

    return y

assert invers_modular(5, 7, False) == 3
# invers_modular(5, 7)

#%%
def fast_pow(n, power, modulus=-1, verbose=True, offset=''):
    """
    Fast exponentiation algorithm
    pow put lgput exp
    modulus=-1 if no modulus
    """

    ans = n**power
    if modulus != -1:
        ans %= modulus
    
    if ans < 0 and modulus != -1:
        ans += modulus

    if verbose:
        print(f"{offset}Calculam {n}^{power}{'' if modulus == -1 else ' (mod' + str(modulus) + ')'}")
        p_act = 1
        while p_act <= power:
            r = n ** p_act
            if modulus != -1:
                r %= modulus
            print(f"{offset} - {n}^{p_act} = {r}")
            p_act *= 2
        
        print(
            f"{offset}{power} = " +
            " + ".join([str(2**i) for i in range(1000) if ((power >> i) & 1) != 0])
        )
        print(
            f"{offset} => {n}^{power} = " +
            " * ".join([f"{n}^{2**i}" for i in range(1000) if ((power >> i) & 1) != 0])
        )
        print(
            f"{offset} => {n}^{power} = " +
            " * ".join([str(n**(2**i) if modulus == -1 else n**(2**i) % modulus) for i in range(1000) if ((power >> i) & 1) != 0])
        )

        print(f"{offset} => {n}^{power} = {ans}")
    
    return ans

put = fast_pow

assert fast_pow(123, 234, -1, False) == 123 ** 234
assert fast_pow(12, 44, 37, False) == 12**44 % 37

# fast_pow(3, 45, 10)

#%%
def crt(reminders: List[int], modulus: List[int], verbose=True, offset=''):
    """
    Chinese reminder theorem
    Lema chineza a resturilor
    """
    if verbose:
        print(f"{offset}Calculam CRT un X, a.i.:")
        for i in range(len(reminders)):
            print(f"{offset}X % {modulus[i]} = {reminders[i]}")
    
    prod = 1
    for i in modulus:
        prod *= i
    
    if verbose:
        print(f"{offset}Produlus modulelor este {prod}")

    inverses = []
    for i in modulus:
        if verbose:
            print(f"{offset}Calculam inversul lui {prod} / {i} = {prod // i} modulo {i}:")
        invs = invers_modular(prod // i, i, verbose, '    ' + offset)
        inverses.append(invs)

    result = 0
    if verbose:
        print(f"{offset}X = ")
        for i in range(len(modulus)):
            print(f"{offset}   ({prod}/{modulus[i]}) * ({prod}/{modulus[i]})^-1 (mod {modulus[i]}) * {reminders[i]}" + (" +" if i + 1 != len(reminders) else ''))
    
    for i in range(len(modulus)):
        result += (prod // modulus[i]) * inverses[i] * reminders[i]

    result %= prod

    if verbose:
        print(f"{offset}X = {result}")
    
    return result

x = crt([1, 2, 3, 4, 0], [2, 5, 7, 11*13, 666013], False)
assert x % 2 == 1
assert x % 5 == 2
assert x % 7 == 3
assert x % (11*13) == 4
assert x % 666013 == 0

#%%
def lfsr(s_init, coefs, l, verbose=True, offset=''):
    """
        lfsr shift registers linear
        s[i] = coef[0]*s[i-1] + coef[1]*s[i-2] + ... + coef[n-1]*s[i-n]
    """
    rez = s_init
    while len(rez) < l:
        c = 0
        for i in range(len(coefs)):
            c ^= rez[-i] * coefs[i]
        rez.append(c)
    return rez
# TODO: Test


#%%
def cipolla(n: int, p: int, verbose=True, offset=''):
    """
        Cipolla algorithm
        square root sqrt radacina patrata in Fp
        P ESTE PRIM
    """

    # cautam a a.i. a^2-n nu e rest patratic
    squares = [i * i % p for i in range(p)]
    a = 1
    while (a * a - n + p) % p in squares:
        a += 1
    
    if verbose:
        print(f"{offset}Folosim a={a}, care respecta {a}^2 - {n} nu e rest patratic modulo {p}")

        print(f"{offset}Notam cu w = sqrt({a}^2 - {n})")

    # salvam elementele in grupul F[w]:
    # (s, t) -> s + t*w
    # valoarea lui w^2
    w_sq = (a*a - n + p) % p

    if verbose:
        print(f"{offset}Stim ca w^2 = {w_sq}")
    def multiply(s: Tuple[int, int], t: Tuple[int, int]):
        rez = (s[0]*t[0] + s[1]*t[1]*w_sq, s[0]*t[1] + s[1]*t[0])
        rez = (rez[0]%p, rez[1]%p)
        return rez
    
    if verbose:
        print(f"{offset}Calculam (w + a)^(p + 1)/2 = (w + {a})^{(p + 1)//2}")

    act = (1, 0)
    put = (p + 1) // 2

    for i in range(1, put + 1):
        act = multiply(act, (a, 1))

        if verbose and (i & -i) == i:
            print(f"{offset}    (w + a)^{i} = {act[0]} + {act[1]}*w")

    assert(act[1] == 0)
    if verbose:
        print(
            f"{offset}(w + a)^{put} = " +
            " * ".join([f"(w+a)^{i}" for i in range(1, put + 1) if (i & -i) == i and (i & put) != 0]) +
            f" = {act[0]}"
        )

    if verbose:
        print(f"{offset}sqrt({n}) = {act[0]} (mod {p})")

    assert act[0] ** 2 % p == n % p
    return act[0]

inv = cipolla(1236, 666013, False)
assert inv * inv % 666013 == 1236

# cipolla(15, 17)

#%%

"""
Elgamal
Grup `G`, generator `g`.

Cheie secreta: `X`
Cheie publica: `h = g^x`

Encriptare:
 * Alegem `y` random.
 * `c1 = g^y`
 * `c2 = h^y * m` 
 * Mesaj criptat: `(c1, c2) = (g^y, h^y * m)`

Decriptare:
 * Primim `(c1, c2) = (g^y, h^y * m) = (g^y, g^xy * m)`
 * `m = c2 * (c1^x)^-1`


Caz aditiv:
Daca consideram grupul `G` ca fiind `(Zp, +)`, atunci problema logaritmului
discret se poate rezolva cu euclid extins:
    Cautam `x` a.i. `g*x = h`
            `<=> x = h * g^-1`
Daca il stim pe `x` putem decripta mesajul. 
"""
def elgamal_setup(g, modul, sk, multiplicativ=True):
    print(f"Setul Elgamal:\n    Cheie secreta: sk = x = {sk}")
    if multiplicativ:
        pk = (g**sk) % modul
        print(f"    Cheie publica: pk = h = g^sk = {g}^{sk}")
        fast_pow(g, sk, modul, True, "        ")
        print(f"    Cheie publica pk = h = {pk}")
    else:
        pk = (g * sk) % modul
        print(f"    Cheie publica: pk = g*sk = {g}*{sk} = {pk}")
    print('')
    return pk

def elgamal_encrypt(g, modul, pk, mesaj, y, multiplicativ=True):
    print(f"Encriptam m={mesaj}, cu g={g}, valoarea random y={y} si pk={pk}")
    if multiplicativ:
        (c1, c2) = (g**y % modul, mesaj * pk**y % modul)
        print(f"    (c1, c2) = (g^y, pk^y*m) = ({g}^{y}, {pk}^{y} * {mesaj}) = ({c1}, {c2})")
    else:
        (c1, c2) = (g * y % modul, (mesaj + pk*y) % modul)
        print(f"    (c1, c2) = (g*y, pk*y+m) = ({g}*{y}, {pk}*{y}+{mesaj} = ({c1}, {c2})")
    print('')
    return (c1, c2)

def elgamal_decrypt(g, modul, sk, c1, c2, multiplicativ=True):
    print(f"Decriptam mesajul (c1, c2)=({c1}, {c2}), cu g={g}, modul={modul} si cheie secreta sk = x = {sk}")
    if multiplicativ:
        print(f"Calculam inversul lui c1 = {c1} modulo {modul}:")
        inv_c1 = invers_modular(c1, modul, True, "    ")
        print(f"Calculam (c1^-1)^sk = {inv_c1}^{sk}:")
        inv_c1_la_sk = fast_pow(inv_c1, sk, modul, True, "    ")
        m = (c2 * inv_c1_la_sk) % modul
        print(f"Calculam m = c2 * c1^(-sk) = c2 * (c1^-1)^sk = {c2} * {inv_c1}^{sk} = {c2} * {inv_c1_la_sk} = {m}")
    else:
        m = (c2 - c1 * sk) % modul
        m = (m + modul) % modul
        print(f"    m = (c2 - c1 * sk) = ({c2} - {c1} * {sk}) = {m}")
    print('')
    return m

def elgamal_aditiv_break(g, modul, pk):
    """
    Gaseste si intoarce sk pentru un pk dat
    """
    print(f"Spargem elgamal aditiv:\npk = g * sk <=> sk = pk * g^-1 = {pk} * {g}^-1")
    inv_g = invers_modular(g, modul, True, "    ")
    sk = inv_g * pk % modul
    print(f"sk = {pk} * {g}^-1 = {pk} * {inv_g} = {sk}")
    return sk

def elgamal_multiplicativ_break(g, modul, pk):
    for i in range(modul):
        r = g ** i % modul
        print(f"{g}^{i} = {r}")
        if r == pk:
            break

g = 2
modul = 19
# elgamal_setup(g=g, modul=modul, sk=5, multiplicativ=True)
# elgamal_encrypt(g=g, modul=modul, pk=10, y=11, mesaj=9, multiplicativ=False)
# elgamal_decrypt(g=g, modul=modul, sk=5, c1=3, c2=5, multiplicativ=False)

# elgamal_aditiv_break(g=g, modul=modul, pk=10)

# elgamal_multiplicativ_break(g=g, modul=modul, pk=13)

#%%
"""
## Deffie-Hellman

keyword: logaritm discret schimb de chei DLP

Grup `G`, generator `g`.

Alice:
 * Alege `a` random.
 * Transmite lui bob `ca = g^a`.

Bob:
 * Alege `b` random.
 * transmite lui Alice `cb = g^b`.

Alice:
 * Alege secretul `c = cb^a`.

Bob:
 * Alege acelasi secret `c = ca^b`.
"""

#%%
def legendre_is_residue(rest, modul, verbose=True, offset='') -> bool:
    """
    Rest patratic, quadratic residue modul HAS TO BE PRIME!!!!
    """
    if modul == 2:
        if verbose:
            print(f"{offset}modulul este 2, deci {rest} este un rest patratic.")
        return True
    if verbose:
        print(f"{offset}Calculam {rest}^(({modul}-1)/2) = {rest}^{(modul - 1) // 2}:")
        fast_pow(rest, (modul - 1) // 2, modul, True, "    ")
    
    p = rest ** ((modul - 1) // 2) % modul

    if verbose:
        if p == 1:
            print(f"{offset}Valoarea este 1, deci numarul ESTE un rest patratic")
        else:
            print(f"{offset}Valoarea nu este 1, deci numarul NU ESTE un rest patratic")
    return p == 1

assert legendre_is_residue(2, 7, False)
assert not legendre_is_residue(3, 7, False)

# legendre_is_residue(6, 31)

#%%
def phi(n, verbose=True, offset=''):
    factors = []
    n_copy = n
    for i in range(2, n + 1):
        p = 0
        while n_copy % i == 0:
            n_copy, p = n_copy // i, p + 1
        if p > 0:
            factors.append((i, p))
    
    ans = 1
    for p, e in factors:
        ans *= p**(e - 1) * (p - 1)

    if verbose:
        print(
            f"{offset}{n} = " +
            " * ".join([f"{i[0]}^{i[1]}" for i in factors])
        )
        print(
            f"{offset}Phi({n}) = " +
            " * ".join([f"{i[0] - 1}*{i[0]}^{i[1] - 1}" for i in factors])
        )
        print(f"{offset}Phi({n}) = {ans}")
        
    return ans

decomp = phi

assert phi(10, False) == 4
# phi(24)


#%%
def rsa_setup(p, q, e=2, use_lambda=False, verbose=True, offset=''):
    n = p * q
    phi_or_lambda = (lcm(p - 1, q - 1, False) if use_lambda else (p - 1) * (q - 1))

    if verbose:
        print(f"N = {p} * {q} = {n}")
        fun_name = "lambda" if use_lambda else "phi"
        print(f"{fun_name}({n}) = {phi_or_lambda}")

    while gcd(e, phi_or_lambda, False) != 1:
        e += 1

    if verbose:
        print(f"Am ales e = {e}")
        
    inv_e = invers_modular(e, phi_or_lambda, verbose, offset+'    ')

    if verbose:
        print(f"Asadar, cheia publica este N={n}, e={e}, iar cheia privata este d={inv_e}")

def rsa_encrypt(N, e, m):
    """
        N, e: public key
        m: message
    """
    c = m**e % N
    print(f"Encryption is {c}")
    return c

def rsa_decrypt(N, d, c):
    """
        N: modulus
        d: secret key
        c: cypher text
    """
    m = c**d % N
    print(f"\nm = c^d % N = {c}^{d} % {N}")
    fast_pow(c, d, N, True, "    ")
    print(f"Asadar, m = {m}")
    return m

# rsa_setup(p=7, q=13, e=5, use_lambda=True)
# rsa_setup(7, 13, 2)

# rsa_encrypt(7 * 13, e=7, m=57)
# rsa_decrypt(7 * 13, d=7, c=8)

#%%
def recombination_vector(dim):
    """
    returns r a.i.
    f(0) = r[0] * f(1) + r[1] * f(2) + ...
    for polynomials of rank < dim
    """
    def comb(a, b):
        return prod(range(1, a+1)) // prod(range(1, b+1)) // prod(range(1, a-b+1))

    r = [(-1)**(i - 1) * comb(dim, i) for i in range(1, dim + 1)]
    return r

"""
2: [2, -1]
3: [3, -3, 1]
4: [4, -6, 4, -1]
"""
# recombination_vector(4)

def interpolate_recombine(values, verbose=True, offset=""):
    """
    value of polynomial in 1, 2, 3, ..., len(value)
    """
    r = recombination_vector(len(values))
    if verbose:
        print(f"{offset}Avem de combinat vectorul de valori {values}")
        print(f"{offset}Cum avem {len(values)} valori, consideram ca avem un polinom de grad < {len(values)}.")
        print(f"{offset}Vectorul de recombinare este astfel {r}")
    calculus = " + ".join([
        f"{a}*{b}" for a, b in zip(r, values)
    ])
    ans = list(map(lambda x: x[0]*x[1], zip(r, values)))
    if verbose:
        print(f"{offset}Raspunsul este {calculus}")
        print(f"{offset}             = " + ' + '.join([str(i) for i in ans]))
        print(f"{offset}             = {sum(ans)}")
        print("")

    return sum(ans)

def compute_polynomial_values(n, coefs):
    """
    Computes the polynomial in 1, 2, ..., n
    """
    def eval(p):
        ans, p_act = 0, 1
        for i in coefs:
            ans += i * p_act
            p_act *= p
        return ans

    return [eval(i) for i in range(1, n + 1)]

def init_sharing(coefs, offset=""):
    """
    list storing for each user a list of coeficients (first one is their secret)
    dij = ce valoare userul i da userului j
    """
    n = len(coefs)
    print(f"{offset}Initializam protocolul cu {n} useri.")
    for i in range(n):
        print(f"{offset}   * #{i + 1} are secretul {coefs[i][0]} si coeficientii {coefs[i][1:]}")

    ans = [[] for i in coefs]

    for i in range(n):
        print(f"{offset}Userul {i + 1} considera polinomul dat de coeficientii {coefs[i]} si da:")
        values = compute_polynomial_values(n, coefs[i])
        for j in range(n):
            print(f"{offset}   * Lui #{j+1} da d[{i + 1}][{j + 1}]={values[j]}")
            ans[j].append(values[j])
    print("")
    return ans

def multiply_gate(secrets, coefs, offset=""):
    """
    perform a multiplication gate, where each user has the secret from secrets
    **secrets has the two multiplied values already multiplied**
    and the coeficients for its hidden polynomial from coefs
    """
    n = len(secrets)
    print(f"{offset}Dorim sa efectuam o inmultire.\nCoeficientii inmultiti detinuti de fiecare user sunt:")
    for i in range(n):
        print(f"{offset}   * #{i + 1} are secretul {secrets[i]}, si alege {coefs[i]} ca si coeficienti.")

    print(f"{offset}Fiecare user calculeaza un polinom pentru a masca secretul, si il partajeaza:")
    obtained_values = [[] for _ in range(n)]
    for i in range(n):
        print(f"{offset}   * #{i + 1} se uita la polinomul dat de coeficientii {[secrets[i]] + coefs[i]}")
        values = compute_polynomial_values(n, [secrets[i]] + coefs[i])
        print(f"{offset}     Da:")
        for j in range(n):
            print(f"{offset}      * Lui #{j + 1} valoarea {values[j]}")
            obtained_values[j].append(values[j])

    print(f"{offset}Fiecare user recombina valorile obtinute:")
    final_secrets = []
    for i in range(n):
        print(f"{offset}   * #{i + 1} a primit vectorul {obtained_values[i]}. Recombina valorile:")
        recomb = interpolate_recombine(obtained_values[i], True, "       ")
        print(f"{offset}     Obtine asadar {recomb}.")
        final_secrets.append(recomb)

    print("")
    return final_secrets


# 3 - x + 5x^2
# interpolate_recombine([7, 21, 45])
init_sharing([[4, 1], [3, 6], [7, 2]])
# multiply_gate([5 * 9, 6 * 15, 7 * 21], [[7], [2], [3]])


# %%

def goldwasser_micali(modul, numere, use_legendre=False):
    """
    if use_legendre is false, just make the list of residues.
    """
    p = 2
    while modul % p != 0:
        p += 1
    q = modul // p
    print(f"Using {p} and {q} as prime factor as {modul} = {p} * {q}")
    if use_legendre:
        pass
    else:
        print(f"Reziduurile patratice modulo {p} sunt [" + " ".join([f"{i}^2" for i in range(p)]) + "]")
        print("    = " + " ".join([f"{i*i % p}" for i in range(p)]))
        reziduuri_p = set([i * i % p for i in range(p)])
        print("    =", reziduuri_p)

        print(f"Reziduurile patratice modulo {q} sunt [" + " ".join([f"{i}^2" for i in range(q)]) + "]")
        print("    = " + " ".join([f"{i*i % q}" for i in range(q)]))
        reziduuri_q = set([i * i % q for i in range(q)])
        print("    =", reziduuri_q)

        for i in numere:
            if i % p in reziduuri_p and i % q in reziduuri_q:
                print(f"     * {i} = {i % p}%{p} = {i%q}%{q} este reziduu modulo {p} => 0")
            else:
                print(f"     * {i} = {i % p}%{p} = {i%q}%{q} NU este reziduu modulo {p} => 1")
        rez = [0 if i % p in reziduuri_p and i % q in reziduuri_q else 1 for i in numere]
        return rez


# goldwasser_micali(77, [23, 53, 36, 41])
# %%
