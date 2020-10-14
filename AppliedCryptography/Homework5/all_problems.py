""" Soren Madsen - HW 5
    Functions:
    Problem 1 - inputSHA3()
    Problem 2 - outputSHA3()
    Problem 3 - theta()
    Problem 4 - rho()
    Problem 5 - pi()
"""

def inputSHA3(v):
    a = []
    I = 5
    J = 5
    K = 64
    a = [ [ [0 for k in range(K)] for j in range(J)] for i in range(I)]

    for i in range(0,5):
        for j in range (0,5):
            for k in range (0, 64):
                a[i][j][k] = v[64 * (5 * j + i) + k]
    return a

def outputSHA3(a):
    v = []
    for i in range(0,5):
        for j in range (0,5):
            for k in range (0, 64):
                v[64 * (5 * j + i) + k] = a[i][j][k]
    return v

def theta(a_in):
    I = 5
    J = 5
    K = 64
    a_out = [ [ [0 for k in range(K)] for j in range(J)] for i in range(I)]
    for i in range(0,5):
        for j in range (0,5):
            for k in range (0, 64):
                left = 0
                right = 0
                for j_prime in range (0,5):
                    left = a_in[(i - 1) % 5][j_prime][k]
                    right = a_in[(i + 1) % 5][j_prime][(k - 1) % 64]
                a_out[i][j][k] = (a_in[i][j][k] + left + right) % 2
    return a_out

def rho(a_in):
    I = 5
    J = 5
    K = 64
    a_out = [ [ [0 for k in range(K)] for j in range(J)] for i in range(I)]
    rhomatrix = [[0,36,3,41,18], [1,44,10,45,2],[62,6,43,15,61], [28,55,25,21,56], [27,20,39,8,14]]
    for i in range (0, 5):
        for j in range (0, 5):
            shift_amt = rhomatrix[i][j]
            idx = 0
            for k in range (0, 64):
                a_out[i][j][(k + shift_amt) % 64] = a_in[i][j][k]
    return a_out

def pi(a_in):
    I = 5
    J = 5
    K = 64
    a_out = [ [ [0 for k in range(K)] for j in range(J)] for i in range(I)]
    for i_prime in range (0, 5):
        for j_prime in range (0, 5):
            for k in range (0, 64):
                a_out[j_prime][(2*i_prime + 3*j_prime) % 5][k] = a_in[i_prime][j_prime][k]
    return a_out


sha_file = open("sha3in.txt", "r")
sha_text = sha_file.read()
sha_in = []
for i in range (0, 1600):
    sha_in.append(int(sha_text[i]))

a = inputSHA3(sha_in)
theta_test = theta(a)
print("Theta Test: ")
print("\tExpected output: [0, 0, 1, 1, 0, 1, 1, 0, 0, 0]")
print("\tActual output:   " + str(theta_test[4][3][9:19]))
print("\tSolution output: " + str(theta_test[2][3][11:21]))
theta_test2 = theta(theta_test)
print("Theta Test2: ")
print("\tExpected output: " + str(a[4][3][9:19]))
print("\tActual output:   " + str(theta_test2[4][3][9:19]))
print("\tSolution output: " + str(theta_test2[2][3][11:21]))

rho_test = rho(a)
print("\nRho Test: ")
print("\tExpected output: [0, 1, 1, 0, 0, 1, 1, 0, 0, 1]")
print("\tActual output:   " + str(rho_test[4][3][9:19]))
print("\tSolution output: " + str(rho_test[2][3][11:21]))

pi_test = pi(a)
print("\nPi Test: ")
print("\tExpected output: [0, 1, 1, 0, 1, 1, 0, 0, 0, 1]")
print("\tActual output:   " + str(pi_test[4][3][9:19]))
print("\tSolution output: " + str(pi_test[2][3][11:21]))
