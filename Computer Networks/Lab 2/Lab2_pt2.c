// Soren Madsen
// 11 April 2019
// Lab 2 Part 2
// This program performs calculations on given data.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	// RTT in milliseconds
	int RTT1 = 3;
	int RTT2 = 20;
	int RTT3 = 26;
	int RTTHTTP = 47;
	int total = 0;

	int par_con;

	// Part A
	total = RTT1 + RTT2 + RTT3 + 2 * RTTHTTP;	// RTT to iniate + RTT HTTP request
	printf("Part A: %d ms\n", total);	

	// Part B
	total = RTT1 + RTT2 + RTT3 + 2 * RTTHTTP + 12 * RTTHTTP;
	printf("Part B: %d ms\n", total);

	// Part C
	if (argc < 2) printf("Usage: Lab2_pt2 parallel_connection_count\n");
	else {
		par_con = atoi(argv[1]);
		double packets = 6/par_con;
		int max_req = (packets - (int)packets < 0.5) ? (int)packets : (int)packets + 1;
		total = RTT1 + RTT2 + RTT3 + 2 * RTTHTTP + max_req * RTTHTTP;
		printf("Part C: %d ms\n", total);
	}
	return 0;
}
