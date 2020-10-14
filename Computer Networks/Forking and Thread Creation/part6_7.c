// Soren Madsen
// 4 April 2019
// Lab 1 Part 6 and Part 7
// This program calculates values for Circuit Switching and Packet Switching users.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double factorial(int init){
    int i = 1;
    double val = 1;
    for (i = init; i > 1; --i){
        val *= i;
    }
    return val;
}

int main(){
    int linkBandwidth = 200;
    int userBandwidth = 20;
    double tPSuser = 0.1;
    int nPSusers = 19;

    // Part 6
    int nCSusers = linkBandwidth/userBandwidth;
    printf("Number of CS Users: %d\n", nCSusers);

    // Part 7a
    double pPSuser = tPSuser;
    printf("Probability a PS user is busy transmitting: %f\n",pPSuser);
    
    // Part 7b
    double pPSuserNotBusy = 1 - pPSuser;
    printf("Probability a PS user is NOT busy transmitting: %f\n",pPSuserNotBusy);

    // Part 7c
    double tenNot = pow(pPSuserNotBusy, 18);
    printf("Probability 18 PS users are NOT busy transmitting: %f\n",tenNot);

    // Part 7d
    double oneUser = pPSuser * pow(pPSuserNotBusy, 18);
    printf("Probability one user is busy transmitting: %.3e\n", oneUser);

    // Part 7e
    double anyOne = 19 * pPSuser * pow(pPSuserNotBusy, 18);
    printf("Probability any one user is busy transmitting: %.3e\n", anyOne);

    // Part 7f
    double tenUsers = pow(pPSuser, 10) * pow(pPSuserNotBusy, nPSusers - 10);
    printf("Probability ten users are busy transmitting: %.3e\n", tenUsers);

    // Part 7g
    double userCombos = factorial(nPSusers)/ factorial(10) /factorial(nPSusers - 10);
    double anyTen = tenUsers * userCombos;
    printf("Probability any ten users are busy transmitting: %.3e\n", anyTen);

    // Part 7h
    int count = 11;
    double val = 0;
    for (count; count < 20; ++count){
        double countUsers = pow(pPSuser, count) * pow(pPSuserNotBusy, nPSusers - count);
        double combos = factorial(nPSusers)/ factorial(count) /factorial(nPSusers - count);
        val += countUsers * combos;
    }
    printf("Probability more than ten users are busy transmitting: %.3e\n", val);


}