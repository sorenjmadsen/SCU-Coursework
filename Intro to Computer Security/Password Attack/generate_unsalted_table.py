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
    hashed_pwds[hashed] = password


with open('unsalted_table.txt', 'w') as out:
    for key in hashed_pwds:
        out.write(key + " " + hashed_pwds[key] + "\n")
    out.close()
