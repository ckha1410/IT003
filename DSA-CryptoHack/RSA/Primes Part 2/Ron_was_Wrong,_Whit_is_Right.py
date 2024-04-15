from glob import glob
from math import gcd
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
moduli = [RSA.import_key(open(f_name, 'r').read()).n for f_name in glob("*.pem")]
vuln_key = RSA.import_key(open("21.pem", 'r').read())
n = vuln_key.n
e = vuln_key.e
ciphertext = bytes.fromhex(open("21.ciphertext", 'r').read())
p = max([gcd(n,m) for m in moduli if n!=m])
q = n // p
d = pow(e, -1, (p-1)*(q-1))
private_key = RSA.construct((n,e,d))
cipher = PKCS1_OAEP.new(private_key)
print(cipher.decrypt(ciphertext))
