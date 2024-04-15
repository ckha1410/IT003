import requests
import json
from pwn import *

def encrypt(pt_hex):
    url = f"http://aes.cryptohack.org/lazy_cbc/encrypt/{pt_hex}/"
    r = requests.get(url)
    enc = (json.loads(r.text))['ciphertext']
    return enc

def check(ct_hex):
    url = f"http://aes.cryptohack.org/lazy_cbc/receive/{ct_hex}/"
    r = requests.get(url)
    try:
        p = json.loads(r.text)['error'].split(": ")[-1]
        return p
    except:
        return "nothing useful"

def get_flag(key_hex):
    url = f"http://aes.cryptohack.org/lazy_cbc/get_flag/{key_hex}/"
    r = requests.get(url)
    try:
        flag = (json.loads(r.text))['plaintext']
        return bytes.fromhex(flag).decode()
    except:
        return "flag not found"

#p1 = a*16, p2 = a*16
p = (b'a'*32).hex()
ct = encrypt(p)
c0 = ct[:32]
c1 = ct[32:]

p2 = b'a'*16
p21 = check(c1)
iv = xor(p2, bytes.fromhex(p21), bytes.fromhex(c0)).hex()
print(get_flag(iv))
