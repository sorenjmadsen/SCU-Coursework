/*
 * Soren Madsen
 * Lab 8: Page Swapping Algoriths
 * 9 March 2020
 * This lab simulates three page swapping algorithms: LRU, FIFO, and SC Replacement with a user defined cache size.
 * Usage: cat accesses.txt | ./sim -<algorithm> <cache size>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
    int pageno;
    int ref_bit;
} ref_page;

int search_cache(int target, ref_page * cache, int size){
    int i;
    for (i = 0; i < size; ++i){
        if (cache[i].pageno == target)
            return i;
    }
    return -1;
}


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[2]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    bool lru = false;       // Least Recently Used
    bool fifo = false;      // First in first out
    bool scr = false;       // Second chance replacement
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int pages = 0;
    
    for (i = 0; i < C_SIZE; i++){// initialise cache array  
         cache[i].pageno = -1;
         cache[i].ref_bit = 0;
    }

    if (strcmp(argv[1], "-lru") == 0)
        lru = true;
    
    else if (strcmp(argv[1], "-fifo") == 0)
        fifo = true;

    else if (strcmp(argv[1], "-scr") == 0)
        scr = true;

    else {
        printf("Select an algorithm: -lru, -fifo, -scr. \n");
        return 0;
    }

    int hits = 0;
    int total_pages = 0;

    if (lru){    
        printf("LRU selected...\n");
        while (fgets(pageCache, 100, stdin)){
            ++total_pages;
    	    int page_num = atoi(pageCache); // Stores number read from file as an int
            int idx = search_cache(page_num, cache, C_SIZE);
            if (idx == -1){
                ++totalFaults;
                printf("Page %d causes a page fault\n", page_num);
                int temp1 = page_num;
                int temp2 = -1;
                for (i = 0; i < C_SIZE; ++i){
                    temp2 = cache[i].pageno;
                    cache[i].pageno = temp1;
                    temp1 = temp2;
                }
            }
            else {
                ++hits;
                int temp = -1;
                for (i = idx; i > 0; --i){
                    temp = cache[i - 1].pageno;
                    cache[i].pageno = temp;
                }
                cache[0].pageno = page_num;
            }
                
            
        }  
    }

    else if (fifo){    
        printf("FIFO selected...\n");
        int c_idx = 0;
        while (fgets(pageCache, 100, stdin)){
            ++total_pages;
    	    int page_num = atoi(pageCache); // Stores number read from file as an int
            int idx = search_cache(page_num, cache, C_SIZE);
            if (idx == -1){
                ++totalFaults;
                printf("Page %d causes a page fault\n", page_num);
                cache[c_idx].pageno = page_num;
                c_idx = (c_idx + 1) % C_SIZE;
            }
            else {
                ++hits;
            }
        }  
    }

    else if (scr){
        printf("Second Chance selected...\n");
        int c_idx = 0;
        while (fgets(pageCache, 100, stdin)){
            ++total_pages;
    	    int page_num = atoi(pageCache); // Stores number read from file as an int
            int idx = search_cache(page_num, cache, C_SIZE);
            if (idx == -1){
                ++totalFaults;
                printf("Page %d causes a page fault\n", page_num);
                while (cache[c_idx].ref_bit != 0) {
                    if (cache[c_idx].pageno == -1){
                        cache[c_idx].pageno = page_num;
                        // DON'T set the reference bit yet
                        break;
                    }
                    if (cache[c_idx].ref_bit == 1){ // Set the ref_bit to 0 if checking it
                        cache[c_idx].ref_bit = 0;
                    }
                    c_idx = (c_idx + 1) % C_SIZE;
                } 
                cache[c_idx].pageno = page_num;
                c_idx = (c_idx + 1) % C_SIZE;
            }
            else {
                ++hits;
                cache[idx].ref_bit = 1;
            }
        }

    }

    float hit_rate = ((float)total_pages - (float)totalFaults) / (float)total_pages;

    printf("  %d \tTotal Page Faults\n", totalFaults);
    printf(" %d \tTotal Requests\n", total_pages);
    printf("%.4f \tHit Rate\n", hit_rate);

    
    return 0;



}
