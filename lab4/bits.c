/* Copyright 2023 Neil Kirby, not for disclosure */
/* Vraj Shah */

#define COLOR_SHIFT 3
#define COLOR_MASK 7

#define STATUS_SHIFT 6
#define STATUS_MASK 7

#define STATUS_IN_PLAY 2

/* No change to function: Sets bits in play */
unsigned char set_in_play(unsigned char bits)
{
	/* don't take this as mgic, work out how it works */
	bits = bits &  ( ~( (unsigned char)STATUS_MASK << STATUS_SHIFT));
	bits = bits | ( (unsigned char)STATUS_IN_PLAY <<STATUS_SHIFT);
	return bits;
}

/* No change to function: Gets the color of color */
int get_color(unsigned char bits)
{
	int color = (bits >> COLOR_SHIFT) & COLOR_MASK;
	//Returns integer value for color based on shifts
	return color;
}

/* Get the color name from get_color function */
char *getColorName(int color){
	//colorArray which returns the color
	char *colorArr[] = {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};
	return colorArr[color];
}
