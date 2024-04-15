from pwn import *
from json import *
from Crypto.Util.number import *
s = connect("socket.cryptohack.org", "13376")
print(s.recv().decode())
def get_publickey() -> tuple:
    tmp = {"option":"get_pubkey"}
    s.send(dumps(tmp).encode())
    a = loads(s.recv())
    return int(a["N"], 16), int(a["e"], 16)
def send_msg(msg: str) -> str:
    tmp = {"option":"sign", "msg" : str(hex(bytes_to_long(msg))[2:])}
    s.send(dumps(tmp).encode())
    a = loads(s.recv())
    return  int(a["signature"], 16)
def check(msg: str, signature):
    tmp = {"option" : "verify", "msg" : str(hex(bytes_to_long(msg))[2:]), "signature" : signature}
    s.send(dumps(tmp).encode())
    a = loads(s.recv())
    return a
msg = b"admin=True"
N, e = get_publickey()
enc_1 = send_msg(long_to_bytes(bytes_to_long(b"admin=True") * 80))
enc_2 = send_msg(long_to_bytes(80))
enc = pow(enc_1 * pow(enc_2, -1, N), 1, N)
print(check(b"admin=True", hex(enc)))
