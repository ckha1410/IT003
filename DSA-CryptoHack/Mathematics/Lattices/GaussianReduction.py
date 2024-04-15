import math
def gaussian_lattice_reduction(v1, v2):
    while True:
        if math.sqrt(v2[0]**2 + v2[1]**2) < math.sqrt(v1[0]**2 + v1[1]**2):
            v1, v2 = v2, v1
        m = math.floor((v1[0]*v2[0] + v1[1]*v2[1]) / (v1[0]**2 + v1[1]**2))
        if m == 0:
            return v1, v2
        v2 = (v2[0] - m*v1[0], v2[1] - m*v1[1])
v = (846835985, 9834798552)
u = (87502093, 123094980)
v1, v2 = gaussian_lattice_reduction(v, u)
inner_product = v1[0]*v2[0] + v1[1]*v2[1]
print("Inner product of the new basis vectors:", inner_product)
