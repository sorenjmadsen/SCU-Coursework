import math

def calculate_d(e, phi_n):
    (A1, A2, A3) = (1, 0, phi_n)
    (B1, B2, B3) = (0, 1, e)
    while(True):
        if B3 == 0:
            return (A3, -1)
        if B3 == 1:
            return (B3, B2)
        Q = math.floor(A3 / B3)
        (t1, t2, t3) = (A1 - Q * B1, A2 - Q * B2, A3 - Q * B3)
        (A1, A2, A3) = (B1, B2, B3)
        (B1, B2, B3) = (t1, t2, t3)

def modulo_exp(num, modulo, exp):
    val = 1
    for i in range(exp):
        val = (val * num) % modulo
    return val

crack_vals = {}

with open("RSALab.txt", "r") as to_crack:
    for line in to_crack:
        (key, val) = line.split(":")
        crack_vals[key] = val.strip()
    old_arr = crack_vals['ciphertext']
    old_arr = old_arr.split(", ")
    old_arr[0] = old_arr[0].replace('[', '')
    old_arr[-1] = old_arr[-1].replace(']', '')
    new_arr = []
    for num in old_arr:
        new_arr.append(int(num))
    crack_vals['ciphertext'] = new_arr
    crack_vals['e'] = int(crack_vals['e'])
    crack_vals['n'] = int(crack_vals['n'])
    to_crack.close()

prime_list = []
with open("RSALabPrimes.txt", "r") as primes:
    for line in primes:
        prime = int(line.strip())
        prime_list.append(prime)

p = 0
q = 0
for i in range(len(prime_list)):
    for j in range(i+1, len(prime_list)):
        if prime_list[i] * prime_list[j] == crack_vals['n']:
            p = prime_list[i]
            q = prime_list[j]
            break
    if (p > 0 or q > 0):
        break

phi_n = (p-1) * (q-1)
print("p = " + str(p) + ", q = " + str(q) + " \nn = " + str(crack_vals['n']))
(gcd, d) = calculate_d(crack_vals['e'], phi_n)
if (d != 1):
    print("d = " + str(int(d)))

plaintext = []
for char in crack_vals['ciphertext']:
    plain = modulo_exp(char, crack_vals['n'], int(d))
    plaintext.append(chr(plain))

print(plaintext)



    
        