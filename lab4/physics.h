/* Vraj Shah */

void constraints( struct Ball *bp);
void move(double dt, struct Ball *bp);
bool off_table(void *data);
bool on_table(struct Ball *bp);
void polar2cart(struct Ball *bp);
void update_ball( void * data);
