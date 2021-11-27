import random

N = 2**20
res = random.sample(range(0, N), N)

with open("seqX.in", "w") as f:
    f.write(str(N))
    f.write(" ")
    for i in res:
        f.write(str(i))
        f.write(" ")