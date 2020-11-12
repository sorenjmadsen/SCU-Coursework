#include "lab5.h"
#include <stdio.h>
#include <stdlib.h>

int get_cksum(Packet packet){
	packet.header.cksum = 0;
	int cksum = 0;
	char * bytes = (char *) &packet;
	int chunks = sizeof(packet.header) + packet.header.len;
	int i;
	for (i = 0; i < chunks; ++i){
		cksum ^= bytes[i];
	}
	cksum = (rand() % 10 == 9)? 0: cksum;
	return cksum;
}

