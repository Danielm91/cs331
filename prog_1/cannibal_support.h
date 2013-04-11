#include <stdio.h>
#include <stdlib.h>

#define DEPTH_MAX 20
#define BOAT_LEFT 1
#define BOAT_RIGHT 2

struct state{
	int missionary_left;
	int missionary_right;
	int cannibal_left;
	int cannibal_right;
	int boat_left;
	int boat_right;
};

void uninformed_search(struct state * start, struct state * goal);

char depth_limited_search(int depth, struct state * start, struct state * goal, int * expanded_nodes, struct state * state_array, char ** state_table);

char check_state(struct state * current, struct state * goal);

void print_state(struct state * input);

