""" Soren Madsen - HW 2 """
""" Problem 2 """
def DecimalToBinary(number, bit_count):
    bit_arr = []
    temp = number
    i = bit_count - 1
    while i >= 0:
        bit = (int(temp / (2**i)))
        bit_arr.append(bit)
        temp -= (2**i) * bit
        i -= 1
    return bit_arr

def ConvertBitArrayToInt(k, n):
    int_arr = []
    for i in range(0, len(k), n):
        num = 0
        for j in range(3):
            num += k[i + j] * (2**(n - 1 - j))
        int_arr.append(num)
    return int_arr

""" Get the inputs """
n = int(input("Enter n: "))
l = int(input("Enter length of plaintext: "))
k = []
""" This is how I decided to get the k bits """
input_str = input("Enter k bits separated by spaces: ")
k_list = input_str.split();
for bit in k_list:
    k.append(int(bit))

print(k)

""" Initialization """
k_int = ConvertBitArrayToInt(k, n)
S = []
T = []
for i in range(0, 2**n):
    S.append(i)
    T.append(k_int[i % len(k_int)])

""" Permutation """
j = 0
for i in range(0, 2**n):
    j = (j + S[i] + T[i]) % (2**n)
    """ Swap """
    temp = S[i]
    S[i] = S[j]
    S[j] = temp

""" Key Generation """
ks = []
j = 0
for i in range(0, l):
    i = (i + 1) % (2**n)
    j = (j + S[i]) % (2**n)
    """ Swap """
    temp = S[i]
    S[i] = S[j]
    S[j] = temp
    t = (S[i] + S[j]) % (2**n)
    ks.append(S[t])

""" Convert KeyStream to bits """
ks_arr = []
for i in range(0, len(ks)):
    for bit in DecimalToBinary(ks[i],n):
        ks_arr.append(bit)

print(ks)
print(ks_arr)

""" Answers """
