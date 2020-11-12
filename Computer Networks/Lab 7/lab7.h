/*
 * Soren Madsen
 * Lab 7: Link State Routing
 * 23 May 2019
 * Simulates the algorithm involved in link state routing.
*/

#ifndef LAB7_H
#define LAB7_H

typedef struct {
	int label;
	char * ip_addr;
	int socket;
} Machine;

typedef struct {
	int router_id;
	int neighbor_id;
	int new_cost;
} Message;

void * thread_recv (void * skt);		// for thread 1 to receive updates
void * thread_alg (void * arg);			// for thread 3 to run the ls algorithm
void printTable();

#endif
