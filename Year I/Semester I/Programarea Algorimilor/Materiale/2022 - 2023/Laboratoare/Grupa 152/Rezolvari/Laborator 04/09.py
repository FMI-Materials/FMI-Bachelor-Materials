def gen_f(k):
    def F(x):
        return x < k
    return F


f_100 = gen_f(100)
f_200 = gen_f(200)

print(f_200(150))
print(f_100(150))
