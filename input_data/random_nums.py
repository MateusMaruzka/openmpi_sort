import random

res = random.sample(range(0, 2048), 32)

with open("seq1.in", "w") as f:
    f.write(str(32))
    f.write(" ")
    for i in res:
        f.write(str(i))
        f.write(" ")