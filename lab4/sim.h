/* Vraj Shah */

bool always_true(void *data);
int ball_score(struct Ball *bp);
bool balls_in_play(struct Sim *table);
void clear_lists(struct Sim *table);
void dead_balls(struct Sim *table);
void final_actions(struct Sim *table);
void launch_ball(struct Sim *table, struct Ball *sbp);
void playlist_to_offlist(void *data);
void run_sim(struct Sim *table);
bool sort_by_VY(void *data1, void *data2);
bool sort_by_Y(void *data1, void *data2);
void update_table(struct Sim *table);
