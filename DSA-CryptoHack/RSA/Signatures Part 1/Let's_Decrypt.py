from Crypto.Util.number import bytes_to_long, long_to_bytes
import telnetlib
import json
import re
from pkcs1 import emsa_pkcs1_v15
from sage.all import *
HOST = "socket.cryptohack.org"
PORT = 13391
def readline():
    return tn.read_until(b"\n")
def json_recv():
    line = readline().decode()
    st = line[line.find('{'):]
    return json.loads(st)
def json_send(hsh):
    request = json.dumps(hsh).encode()
    tn.write(request)
tn = telnetlib.Telnet(HOST, PORT)
msg = "I am Mallory1111own CryptoHack.org"
digest = bytes_to_long(emsa_pkcs1_v15.encode(msg.encode(), 256))
print(readline())
to_send = json.loads(json.dumps({"option" : "get_signature"}))
json_send(to_send)
sig = int(json_recv()["signature"],0)
n = sig - digest
e = 1
json_p = {"option":"verify","msg":"I am Mallory1111own CryptoHack.org","N": hex(n)[2:],"e":hex(e)[2:]}
json_p = json.dumps(json_p)
to_send = json.loads(json_p)
json_send(to_send)
print(readline())
