
/* Copyright 2023 Neil Kirby, not for disclosure */
/* Vraj Shah */
/* structs.h */

struct Sim
{
	double et;
	int score;	/* 2 biliion ought to suffice */

	void *playlist; /* sort by Y */
	void *offlist;
	FILE *fp; /* file pointer */
};

struct Ball
{
	unsigned char bits;
	int color;
	double X, Y, VX, VY;
	double theta, force;
	double duration;
	struct Sim *table;
};

