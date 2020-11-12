// Useful types and functions for packet processing

#ifndef LAB5_H
#define LAB5_H

#define SIZE 10

typedef struct {
	int seq_ack;
	int len;
	int cksum;
} Header;

typedef struct {
	Header header;
	char data[SIZE];
} Packet;

int get_cksum(Packet);

#endif
