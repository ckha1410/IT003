def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)
def mod_inverse(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    else:
        return x % m
def chinese_remainder_theorem(moduli, residues):
    product = 1
    for m in moduli:
        product *= m
    result = 0
    for i in range(len(moduli)):
        Mi = product // moduli[i]
        Mi_inverse = mod_inverse(Mi, moduli[i])
        result += residues[i] * Mi * Mi_inverse
    
    return result % product
moduli = [5, 11, 17]
residues = [2, 3, 5]
result = chinese_remainder_theorem(moduli, residues)
print("Solution:", result)
