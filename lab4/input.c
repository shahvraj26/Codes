/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Vraj Shah */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* includes for constants and tyupes are next */
#include "debug.h"
#include "structs.h"

/* includes for functions go last */
#include "input.h"
#include "lab4.h"
#include "sim.h"

/* Read file and launch the ball */
void read_all(struct Sim *table)
{
	/* at this point we need to declare out data */
	struct Ball steel, *b = &steel;
	int tokens;
	
	b->table = table;  // do this earlyl
	
	//Changed to fscanf
	while( 5 == (tokens = 
		fscanf(b->table->fp, "%hhx %lf %lf %lf %lf",&b->bits,
		&b->X, &b->Y, &b->theta, &b->force)
		    )
	    )
	{
	    launch_ball(table, b);
	}
	if(TEXT)printf("Final scanf call returned %d\n", tokens);

	run_sim(table);
}

/* FileI/O arguments */
int arguments(int argc, char *argv[], struct Sim *table){
	int results = 1;
	//Extract filename through second command line argument
	char *filename = argv[1];
	if(argc < 2){
		printf("ERROR: Insufficient arguments (argc is %d).\n", argc);
		results=0;
	}
	if(argc == 2){
		//Open file and read into filepointer
		table->fp = fopen(filename, "r");
		if(table->fp == NULL){
			printf("ERROR: Unable to open %s for reading.\n", filename);
			results=0;
		}
		else {
			printf("DIAGNOSTICS: Successfully opened %s for reading.\n", filename);
			// Run read_all when two argcs are found 
			read_all(table);
		}	
		//Close file
		fclose(table->fp);
		printf("DIAGNOSTIC: Input file closed.\n");
	}
	if(argc == 3 && GRAPHICS){
		printf("ERROR: Bonus Code is not present.\n");
		results=0;
	}
	if(argc == 3 && !GRAPHICS){
		printf("ERROR: TEXT mode enabled.\n");
		results=0;
	}
	return results;
}
