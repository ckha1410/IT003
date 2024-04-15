 a^(p-2) % p = a^(-1)  
from Crypto.Util.number import inverse
print(inverse(3, 13)) 
 def mod_inv(x, y):
     for i in range(y):
         if x*i % y == 1:
             return i
print(mod_inv(3, 13))
