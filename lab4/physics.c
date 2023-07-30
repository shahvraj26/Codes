
/* Copyright 2023 Neil Kirby, not for disclosure */
/* Vraj Shah */
/* All physics goes here */

#define GRAVITY	(-47.052534795)	/* inches per second per second */
#define LEFT_LIMIT	(-12.0)
#define RIGHT_LIMIT	(12.0)
#define UPPER_LIMIT	(48.0)
#define LOWER_LIMIT	(0.0)
#define INELASTIC	(0.95)

/* and now for the flippers */
#define FLIPPER_MAX_X_LEFT -2.0
#define FLIPPER_MAX_Y_LEFT 1.0
#define FLIPPER_MIN_X_LEFT -5.0
#define FLIPPER_MIN_Y_LEFT 0.0

#define FLIPPER_MAX_X_RIGHT 5.0
#define FLIPPER_MAX_Y_RIGHT 1.0
#define FLIPPER_MIN_X_RIGHT 2.0
#define FLIPPER_MIN_Y_RIGHT 0.0

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "constants.h"
#include "structs.h"

#include "output.h"

/* validate my own header file */
#include "physics.h"

/* Check if ball is on table */
bool on_table(struct Ball *bp)
{
	return( bp->Y >= LOWER_LIMIT);
}

/* check if ball is off table */
bool off_table(void *data)	
{
	// criteria function
	struct Ball *bp = data;

	return (!on_table(bp));
}

/*Left wall Computations */
static void left_wall(struct Ball *bp)
{
	if(bp->X < LEFT_LIMIT)
	{
	    left_message(bp);
	    bp->X = 2.0 * LEFT_LIMIT - bp->X;
	    bp->VX = -bp->VX;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

/* Right wall computations */
static void right_wall( struct Ball *bp)
{
	if(bp->X > RIGHT_LIMIT)
	{
	    right_message(bp);
	    bp->X = 2.0 * RIGHT_LIMIT - bp->X;
	    bp->VX = -bp->VX;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

/* Top wall computations */
static void top_wall( struct Ball *bp)
{
	if(bp->Y > UPPER_LIMIT)
	{
	    top_message(bp);
	    bp->Y = 2.0 * UPPER_LIMIT - bp->Y;
	    bp->VY = -bp->VY;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

/* Left flipper computations */
static void left_flipper( struct Ball *bp)
{
	if(
		(bp->X >= FLIPPER_MIN_X_LEFT) &&
		(bp->X <= FLIPPER_MAX_X_LEFT) &&
		(bp->Y >= FLIPPER_MIN_Y_LEFT) &&
		(bp->Y <= FLIPPER_MAX_Y_LEFT) 
	    )
	    {
	    	left_flipper_message(bp);
		bp->VY += 75.0;
		bp->VX += 6.4;
		bp->Y += 1.0;
	    }
}

/* Right flipper computations */
static void right_flipper( struct Ball *bp)
{
	if(
		(bp->X >= FLIPPER_MIN_X_RIGHT) &&
		(bp->X <= FLIPPER_MAX_X_RIGHT) &&
		(bp->Y >= FLIPPER_MIN_Y_RIGHT) &&
		(bp->Y <= FLIPPER_MAX_Y_RIGHT) 
	    )
	    {
	    	right_flipper_message(bp);
		bp->VY += 75.0;
		bp->VX += -6.4;
		bp->Y += 1.0;
	    }
}

/* Wall constraints */
void constraints( struct Ball *bp)
{
	void (*todo[])(struct Ball *bp) = { left_wall, right_wall, 
		top_wall, left_flipper, right_flipper};
	int i, count = sizeof(todo)/sizeof(todo[0]);

	for(i=0; i<count; i++)todo[i](bp);

}

/* Action Function: Update one ball */
void update_ball( void * data)	
{
	//action function
	struct Ball *bp = data;

	move(DELTA_T, bp);
	constraints(bp);
}

/*Move equations */
void move(double dt, struct Ball *bp)
{
	/* position first, then velocity */
	bp->X += bp->VX * dt;
	bp->Y += bp->VY * dt + 0.5 * GRAVITY * dt * dt;
	/* no change in VX */
	bp->VY += GRAVITY * dt;
}

/* Rectangular conversion */
void polar2cart(struct Ball *bp)
{
	double computedVX = bp->force * cos( bp->theta * M_PI / 180.0 );
	double computedVY = bp->force * sin( bp->theta * M_PI / 180.0 );

	bp->VX = computedVX;
	bp->VY = computedVY;
}
