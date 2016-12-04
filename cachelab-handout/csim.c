#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define DEBUG 1

/************************************************************

CacheLab of Jinyoug Oh, CS20160385

************************************************************/

//struct for line
typedef struct {
	int birthday; // pointer of data block's array
	unsigned long int Tag; // Tag Bit
	char Valid; // Valid Bit
} LINE;


// Global Variables
FILE *t; // variable for file to test

int main(int argc, char** argv){
	

	// variables    
	int hit_cnt=0, miss_cnt=0, eviction_cnt=0;
	int hit, miss, eviction;
	int i,j,cycle=0;
	int opt, HELP=0, VERBOSE=0,s, S,E,B;
	char* T;// command-line arguments
	LINE** cache;
	char *instruction, *address, *size;
	long address_int, size_int, tag, set_index, block_offset;
	char trace[64];
	long mask;
	// read command-line

	// debug setting
	VERBOSE = DEBUG;

	
	while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1){
		switch(opt){
			case 'h': HELP = 1; break;
			case 'v': VERBOSE = 1; break;
			case 's':
				s = atoi(optarg); 
				S = pow(2,s);
				 break;
			case 'E':
				E = atoi(optarg);
				cache = malloc(S*sizeof(LINE*));
				for(i=0; i<S; i++){
					cache[i] = malloc(E*sizeof(LINE));
				}
				break;
			case 'b': B = atoi(optarg); break;
			case 't': T = optarg; break;
			default : break; //????????????????????

		}

	}

	if(DEBUG) printf("%d\n",HELP);

	t = fopen(T,"r");
	

	while(fgets(trace,64,t)!= NULL){
		
		hit = 0;
		miss = 0;
		eviction = 0;

		if(trace[0] != ' ') continue;


		instruction = strtok(trace, " ,");
		address = strtok(NULL, " ,");
		size = strtok(NULL, " ,");
		address_int = strtol(address,NULL,16);
		size_int = atoi(size);

		////////////////////////////////////////////////////////////////////////////////////

		mask = 0;		

		for(i = 0; i<B; i++){
			mask += 1 << i;
		} // mask for block offset bits
		block_offset = mask & address_int;
		
		mask = 0;
		for(i = B; i<B+s; i++){
			mask += 1 << i;
		} // mask for set index bits
		set_index = (mask & address_int) >> B;

		tag = (unsigned)address_int >> (B+s);

		///////////////////////////////////////////////////////////////////////////////////		

		if(VERBOSE && !DEBUG){
			printf("%s %lx,%ld ",instruction,address_int,size_int);
		}
		if(DEBUG) printf("%s %lx,%ld %ld %ld %ld ", instruction, address_int, size_int, tag, set_index,block_offset);
		//////////////////////////////////////////////////////////////////////////////////

		for(i = 0; i<E; i++){
			if(cache[set_index][i].Valid == 1 && cache[set_index][i].Tag == tag){
				hit = 1;
				cache[set_index][i].birthday = cycle;
				break;	
			}
		}

		if(!hit){
			miss = 1;
			eviction = 1;
			for(i=0; i<E; i++){
				if(cache[set_index][i].Valid == 0){
					cache[set_index][i].Valid = 1;
					cache[set_index][i].Tag = tag;
					eviction = 0;
					cache[set_index][i].birthday = cycle;
					break;
				}
			}
			if(eviction){
				j = 0;
				for(i=0; i<E; i++)	if(cache[set_index][i].birthday < cache[set_index][j].birthday) j = i;
				cache[set_index][j].birthday = cycle;			
				cache[set_index][j].Tag = tag;
			}			
		}

		/////////////////////////////////////////////////////////////////////////////////

		switch(*instruction){
			case 'M': // data modify
				hit_cnt++;
			default	: // data load and store
				if(hit) hit_cnt++;
				if(eviction) eviction_cnt++;
				if(miss) miss_cnt++;
				
		}
		if(VERBOSE){
			if (miss) printf("%s ", "miss");
			if (eviction) printf("%s ", "eviction");
			if (hit) printf("%s ", "hit");
			if (*instruction == 'M') printf("%s ", "hit");
			printf("\n"); 
		}
		cycle++;
		//printf("%d", feof(t));
	}
	 



	

	// skeleton code
	printSummary(hit_cnt,miss_cnt,eviction_cnt);
	/////////////////////////////////////////////
	
	fclose(t);
	for(i = 0; i<S; i++) free(cache[i]);
	free(cache);
	return 0;
}
