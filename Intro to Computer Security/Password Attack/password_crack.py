import hashlib
import time

start = time.clock()
hash_table = {}
with open('unsalted_table.txt', 'r') as dictionary:
    for line in dictionary:
        [key, val] = line.split()
        key.strip()
        val.strip()
        hash_table[key] = val
    dictionary.close()

breached_data = {}
with open('breached_data.txt', 'r') as data:
    for line in data:
        [key, val] = line.split()
        key.strip()
        val.strip()
        breached_data[key] = val
    data.close()

cracked_passwords = {}
for key in breached_data:
    if breached_data[key] in hash_table:
        cracked_passwords[key] = hash_table[breached_data[key]]

end = time.clock()
with open('cracked_passwords.txt', 'w') as out:
    out.write("Total Passwords Cracked: " + str(len(cracked_passwords)) + "\n")
    out.write("Time elapsed: " + str(end - start) + " s\n\n")
    for key in cracked_passwords:
        out.write(key + ": " + cracked_passwords[key] + "\n")
    
    out.close()

start = time.clock()
hash_table = {}
with open('salted_table.txt', 'r') as dictionary:
    for line in dictionary:
        [key, val] = line.split()
        key.strip()
        val.strip()
        hash_table[key] = val
    dictionary.close()

breached_data = {}
with open('breached_data.txt', 'r') as data:
    for line in data:
        [key, val] = line.split()
        key.strip()
        val.strip()
        breached_data[key] = val
    data.close()

cracked_passwords = {}
for key in breached_data:
    print(key + " " + breached_data[key])
    if breached_data[key] in hash_table:
        cracked_passwords[key] = hash_table[breached_data[key]]

end = time.clock()
with open('salted_cracked_passwords.txt', 'w') as out:
    out.write("Total Passwords Cracked: " + str(len(cracked_passwords)) + "\n")
    out.write("Time elapsed: " + str(end - start) + " s\n\n")
    for key in cracked_passwords:
        out.write(key + ": " + cracked_passwords[key] + "\n")
    
    out.close()