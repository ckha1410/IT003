def legendre_symbol(a, p):
    return pow(a, (p - 1) // 2, p)
def tonelli_shanks(n, p):
    if legendre_symbol(n, p) != 1:
        return None  # No modular square root exists
    q = p - 1
    s = 0
    while q % 2 == 0:
        q //= 2
        s += 1
    if s == 1:
        return pow(n, (p + 1) // 4, p)
    for z in range(2, p):
        if p - 1 == legendre_symbol(z, p):
            break
    c = pow(z, q, p)
    r = pow(n, (q + 1) // 2, p)
    t = pow(n, q, p)
    m = s
    while True:
        if t == 1:
            return r
        i = 0
        temp = t
        while temp != 1:
            temp = (temp * temp) % p
            i += 1
            if i == m:
                return None  # No modular square root exists
        b = pow(c, pow(2, m - i - 1, p - 1), p)
        r = (r * b) % p
        t = (t * b * b) % p
        c = (b * b) % p
        m = i
