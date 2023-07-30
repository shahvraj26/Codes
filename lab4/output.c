/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Vraj Shah */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>

#include "libpb.h"
#include "n2.h"
#include "linklist.h"

/* includes for constants and types are next */
#include "debug.h"
#include "constants.h"
#include "structs.h"

/* includes for functions go last */
#include "bits.h"
#include "sim.h"
#include "output.h"

/* functions internal to this file go here at the top */

/* Print the header in TEXT mode */
static void print_header(double et, int score)
{
	/* VY can hit -100, so it needs more room */
	printf("\n%7s %2s    %9s %9s    %9s %10s    ET=%9.6lf  Score=%4d\n",
	"Color", "ST", "___X_____", "___Y_____", "___VX____", "____VY____", et,score);

}

/* an action function: print ball scores in TEXT mode */
void print_ball_scores(void *data)
{
	struct Ball *bp = data;

	int colorName = get_color(bp->bits);
	printf("%7s %02X    %3d points\n", getColorName(colorName), bp->bits, ball_score(bp) );
}

/* an action function: Print balll data in TEXT mode */
void print_ball(void *data)
{
	struct Ball *bp = data;
	int colorName = get_color(bp->bits);
	/* VY can hit -100, so it needs more room */
	printf("%7s %02X    %9.5lf %9.5lf    %9.5lf %10.5lf\n",
	    getColorName(colorName), bp->bits, bp->X, bp->Y, bp->VX, bp->VY );
}

/* an action function: Draw ball in GRAPHICS mode */
static void draw_ball(void *data)
{
	struct Ball *bp = data;
	int colorName = get_color(bp->bits);
	pb_ball(colorName, bp->X, bp->Y);
}

/* Print all text */
static void master_text(struct Sim *table)
{
	sort(table->playlist, sort_by_Y);
	print_header(table->et, table->score);
	iterate( table->playlist, print_ball);
	printf("\n");
}

/* Print all graphics */
static void master_graphics(struct Sim *table)
{
	pb_clear();
	pb_time( (int) (table->et * 1000.0));
	pb_score(table->score);
	iterate( table->playlist, draw_ball);
	pb_refresh();

	microsleep( (unsigned int)(DELTA_T * 1000000.0));
}

/* Print the final graphics */
static void final_graphics(struct Sim *table)
{
        double wait = 0.0;

        while(wait < 4.0)
        {
            pb_clear();
            pb_time( (int) table->et * 1000);
	    pb_score(table->score);
            pb_refresh();

            microsleep( (unsigned int)(DELTA_T * 1000000.0));
            wait += DELTA_T;
        }
}

/* Print final text at the end */
static void final_text(struct Sim *table)
{
	printf("\nThe final scores was %d points:\n", table->score);
	iterate(table->offlist, print_ball_scores);
	printf("\n");
}
/* public functions below here **********************************/

/* Print Master output */
void master_output(struct Sim *table)
{
	if(TEXT)master_text(table);
	if(GRAPHICS)master_graphics(table);
}

/* Prints final output */
void final_output(struct Sim *table)
{
	if(TEXT) final_text(table);
	if(GRAPHICS)final_graphics(table);
}

/* Load message print */
void load_message( struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
	if(GRAPHICS)pb_status("Loaded");
if(TEXT)printf("Loaded %02X %7s ball at %9.5lf, %9.5lf %9.5lf deg %9.5lf ips\n",
    		bp->bits, getColorName(color), bp->X, bp->Y, bp->theta, bp->force);

}

/* Launch Message print */
void launch_message( struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
	if(GRAPHICS)pb_status("Launch");
if(TEXT)printf("Launched %02X %7s ball at %9.5lf, %9.5lf at %9.5lf, %9.5lf\n",
    		bp->bits, getColorName(color), bp->X, bp->Y, bp->VX, bp->VY);

}


/* not technically public but it goes right next to the funcitons that call
 * it */
static void x_message( char *string,  struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
    if(TEXT) printf("%s: %7s %02X    %9.5lf %9.5lf    %9.5lf %10.5lf\n",
	    string, getColorName(color), bp->bits, bp->X, bp->Y, bp->VX, bp->VY );

	if(GRAPHICS)pb_status(string);
}

/* Left wall message */
void left_message( struct Ball *bp)
{
    x_message("Left_ wall", bp);
}

/* Right wall message */
void right_message( struct Ball *bp)
{
    x_message("Right wall", bp);
}

/* Top wall message */
void top_message( struct Ball *bp)
{
    x_message("Upper wall", bp);
}

/* Off table message */
void off_message( struct Ball *bp)
{
    x_message("Off table", bp);
}

/* Left flipper message */
void left_flipper_message( struct Ball *bp)
{
    x_message("Left_ flipper", bp);
    if(GRAPHICS) pb_left();
}

/* right flipper message */
void right_flipper_message( struct Ball *bp)
{
    x_message("Right flipper", bp);
    if(GRAPHICS) pb_right();
}

/* Points message */
void points_message(int points)
{
	if(TEXT)printf("%d points\n", points);
	// graphics mode does score every frame
}

