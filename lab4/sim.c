/* COpyright 2023 Neil Kirby */
/* Vraj Shah */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "structs.h"
#include "debug.h"

#include "linklist.h"
#include "memory.h"
#include "output.h"
#include "bits.h"
#include "physics.h"
#include "sim.h"

/* Check if balls are in play */
bool balls_in_play(struct Sim *table)
{
	return( table->playlist != NULL);
}

/* Sort VY */
bool sort_by_VY(void *data1, void *data2)
{
	struct Ball *bp1 = data1, *bp2 = data2;

	return(bp1->VY > bp2->VY);
}

/* Sort by Y */
bool sort_by_Y(void *data1, void *data2)
{
	struct Ball *bp1 = data1, *bp2 = data2;

	return(bp1->Y > bp2->Y);

}

/* Ball score */
int ball_score(struct Ball *bp)
{
	return( (int) abs(bp->VY));
}

/* inplay list to off table list */
void playlist_to_offlist(void *data)
{
	struct Ball *bp = data;
	off_message(bp);
	if(insert(&bp->table->offlist, bp, sort_by_VY, TEXT))
	{
	    int points = ball_score(bp);
	    bp->table->score += points;
	    points_message(points);
	}
	else
	{
	    //Free ball from off table list
	    if(TEXT)printf("ERROR: Unable to insert into off table list, freeing %hhX\n", bp->bits);
	    free_ball(bp);
	}
}

/* delete dead balls */
void dead_balls(struct Sim *table)
{
	deleteSome(&table->playlist, off_table, playlist_to_offlist, TEXT);
}

/* update the table text */
void update_table(struct Sim *table)
{
	iterate(table->playlist, update_ball);
}

/* final actions for outputing table*/
void final_actions(struct Sim *table)
{
	final_output(table);
	clear_lists(table);
}

/* Run simulator */
void run_sim(struct Sim *table)
{

	while(balls_in_play(table))
	{
	    master_output(table);
	    table->et += DELTA_T;
	    update_table(table);
	    dead_balls(table);
	}
	final_actions(table);
}

/* Converts load to launch */
static struct Ball load2launch(struct Ball *inbound)
{
 	// take care of all the fields   
	inbound->color = get_color(inbound->bits);
	inbound->bits = set_in_play(inbound->bits);
	polar2cart(inbound);
	//return the struct, not the pointer.
	return *inbound;
}

/* Launches the ball */
void launch_ball(struct Sim *table, struct Ball *sbp)
{
	struct Ball *dbp;  	// dynamic ball pointer -> dbp
				// static ball pointer -> sbp
	load_message(sbp);
	if( dbp = allocate_ball())
	{
	    *dbp = load2launch(sbp);	// transfer what we read
	    if( insert(&table->playlist, dbp, sort_by_Y, TEXT))
	    {
		launch_message(dbp);
	    }
	    else {
		printf("ERROR: Unable to insert into in-play list, freeing %hhX\n", dbp->bits);
		free_ball(dbp);
	    }
	}

}

/* Always true message */
bool always_true(void *data)
{
	return true;
}

/* Clear linked list */
static void clear_a_list(char *name, void *address_of_head)
{
	int balls = deleteSome(address_of_head, always_true, free_ball, TEXT);
	if(TEXT)printf("Deleted %d balls from %s list.\n", balls, name);
}

/* Clear both off table and in play lists */
void clear_lists(struct Sim *table)
{
	clear_a_list("in play", &table->playlist);
	clear_a_list("off table", &table->offlist);
}

