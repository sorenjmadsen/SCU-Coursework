import hashlib

passwords = []
with open('passes_real.txt', 'r') as dictionary:
    for line in dictionary:
        passwords.append(line.strip())
    dictionary.close()

# Hash the passwords and add to dictionary
hashed_pwds = {}
for password in passwords:
    hashed = hashlib.sha256(password).hexdigest()
    hashed_pwds[password] = hashed

salts = []
with open('breached_data_salted.txt', 'r') as salted:
    i = 0
    for line in salted:
        if i >= 100:
            break
        (key, salt, hashed) = line.split()
        salt.strip()
        if not salt in salts:
            salts.append(salt)
            i += 1
    salted.close()

salted_pwds = {}
for password in hashed_pwds:
    for salt in salts:
        salted_hash = hashlib.sha256(salt + hashed_pwds[password]).hexdigest()
        salted_pwds[salted_hash] = password

with open('salted_table.txt', 'w') as out:
    for key in salted_pwds:
        out.write(key + " " + salted_pwds[key] + "\n")
    out.close()