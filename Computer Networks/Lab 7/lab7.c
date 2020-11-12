/*
 * Soren Madsen
 * Lab 7: Link State Routing
 * 23 May 2019
 * Simulates the algorithm involved in link state routing using a network of machines.
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "lab7.h"

int machine_count;				// Keeps track of how many machines in the network
int machine_label;				// Keeps track of which machine a particular instance of Lab7 is
int ** costs;					// Stores the costs between links
Machine * machines;				// Stores the information of the machines
pthread_mutex_t lock;			// Prevents concurrent access of costs

void * thread_recv (void * skt)
{
	int socket = *((int *) skt);
	int router;
	int neighbor;
	int cost;
	Message received;

	while (1)
	{
		// Receive updated link cost
		recv(socket, &received, sizeof(Message), 0);
		router = received.router_id;
		neighbor = received.neighbor_id;
		cost = received.new_cost;

		// Assign to costs table
		pthread_mutex_lock(&lock);
		costs[router][neighbor] = cost;
		costs[neighbor][router] = cost;
		pthread_mutex_unlock(&lock);

		if(debug) printf("received updated link costs\n")

		printTable();
	}
	
}

void * thread_alg (void * arg)
{
	int * opt = malloc(sizeof(int) * (machine_count));
	int * nPrime = malloc(sizeof(int) * (machine_count));

	int nodes_covered = 0;
	int tracker = 0;
	int min;

	int i;	// for the loops

	nPrime[machine_label] = 1;
	
	while (1)
	{
		for (i = 0; i < machine_count; ++i)
		{
			opt[i] = costs[machine_label][i];
			nPrime[i] = 0;
		}

		while (nodes_covered < machine_count)
		{	
			min = 1000;				// Set the min to the equivalent of infinity in this context

			// Find the minimum value of N
			for (i = 0; i < machine_count; ++i)
			{
				if (nPrime[i] != 1 && (opt[i] < min))
				{
					tracker = i;
					min = opt[i];
				}
			}

			// Add it to nPrime
			nPrime[tracker] = 1;
			++nodes_covered;

			// Update d(v) for all v adjacent to node and not in Nprime
			for (i = 0; i < machine_count; ++i)
			{
				if (nPrime[i] != 1 && costs[tracker][i] != 1000)
					{
				opt[i] = (opt[i] < opt[tracker] + costs[tracker][i]) ? opt[i] : opt[tracker] + costs[tracker][i];
				}
			}
		}

		for (i = 0; i < machine_count; ++i)
			printf("%d ", opt[i]);

		printf("\n\n");
		// Reset for continued calculation
		memset(opt, 0, sizeof(int *) * machine_count);
		memset(nPrime, 0, sizeof(int *) * machine_count);
		nodes_covered = 0;

		sleep((rand() % 10) + 10);	
	}
}

void printTable(){
	int i, j;
	for (i = 0; i < machine_count; ++i){
		for (j = 0; j < machine_count; ++j){
			printf("%d\t", costs[i][j]);
		}
		printf("\n\n");
	}
}

int main(int argc, char * argv[])
{	
	int debug;
	FILE * costsfp;
	FILE * machinesfp;

	int sock;
	struct sockaddr_in * machine_addrs;
	struct hostent *host;
	socklen_t addr_len;

	pthread_t recv_id, alg_id;

	Message toSend;
	
	// Usage: ./lab7 <N> <costs.txt> <machines.txt> <M> <optional debug>
	if (argc < 4)
	{
		printf("Usage: ./lab7 <number of machines> <costs file> <machines file> <machine label> <optional debug>\n");
		exit(1);
	}

	machine_count = atoi(argv[1]);
	machine_label = atoi(argv[4]);
	if (argv[5]) debug = 1;
	if (debug) printf("count:%d  label:%d\n", machine_count, machine_label);

	// Open costs
	if (!(costsfp = fopen(argv[2], "r")))
	{
		perror("fopen - costs");
		exit(1);
	}
	if (debug) printf("opened costs\n");

	// Open machines
	if (!(machinesfp = fopen(argv[3], "r")))
	{
		perror("fopen - machines");
		exit(1);
	}
	if (debug) printf("opened machines\n");

	// Initialize arrays
	costs = malloc(sizeof(int *) * machine_count);
	machines = malloc(sizeof(Machine) * machine_count);
	machine_addrs = malloc(sizeof(struct sockaddr_in) * machine_count);

	// Assign costs,machines arrays
	int row, col;
	for (row = 0; row < machine_count; ++row)
	{
		costs[row] = malloc(sizeof(int) * machine_count);	
		machines[row].ip_addr = malloc(16 * sizeof(char));

		// Assign the machine
		fscanf(machinesfp, "%d %s %d", &machines[row].label, machines[row].ip_addr, &machines[row].socket);
		if (debug) printf("%d %s %d\n", machines[row].label, machines[row].ip_addr, machines[row].socket);

		// Assign the machine addresses
		machine_addrs[row].sin_family = AF_INET;
		machine_addrs[row].sin_port = htons(machines[row].socket);
		host = (struct hostent *) gethostbyname(machines[row].ip_addr);
		machine_addrs[row].sin_addr = *((struct in_addr *)host->h_addr);

		// Move on to costs
		for(col = 0; col < machine_count; ++col)
			fscanf(costsfp, "%d", &costs[row][col]);
	}

	// Open socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	// Bind the socket
    if (bind(sock,(struct sockaddr *)&machine_addrs[machine_label], sizeof(struct sockaddr)) == -1)
    {
    	perror("bind");
    	exit(1);
    }
    addr_len = sizeof(struct sockaddr);

	if (debug) printf("creating threads\n");
	pthread_create(&recv_id, NULL, thread_recv, &sock);			// Begin thread_recv
	pthread_create(&alg_id, NULL, thread_alg, NULL);			// Begin thread_alg
	

	// Prepare to send information
	toSend.router_id = machine_label;

	while (1){
		// Get updated link info from console
		scanf("%d %d", &toSend.neighbor_id, &toSend.new_cost);
		if(toSend.neighbor_id == machine_label) toSend.new_cost = 0;

		// Update the machine table
		pthread_mutex_lock(&lock);
		costs[machine_label][toSend.neighbor_id] = toSend.new_cost;
		costs[toSend.neighbor_id][machine_label] = toSend.new_cost;
		pthread_mutex_unlock(&lock);

		if (debug) printf("sending updated costs\n");

		// Send to all other machines
		for (row = 0; row < machine_count; ++row){
			if (row == machine_label) continue;
			sendto(sock, &toSend, sizeof(Message), 0, (struct sockaddr *)&machine_addrs[row], addr_len);
		}

		if (debug) printf("sent updated costs\n");

		printf("\n");
		printTable();
	}
}

	
	

