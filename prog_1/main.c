#include <stdio.h>
#include <stdlib.h>
#include "cannibal_support.h"

//First arument is start, second is goal

int main(int argc, char* argv[]){
	int i;

	struct state start;
	struct state goal;

	//Parse start and goal states
	FILE *start_state = fopen(argv[1], "r");
	FILE *goal_state = fopen(argv[2], "r");

	fscanf(start_state, "%i,%i,%i", &(start.missionary_left), &(start.cannibal_left), &(start.boat_left));
	fscanf(start_state, "%i,%i,%i", &(start.missionary_right), &(start.cannibal_right), &(start.boat_right));

	fscanf(goal_state, "%i,%i,%i", &(goal.missionary_left), &(goal.cannibal_left), &(goal.boat_left));
	fscanf(goal_state, "%i,%i,%i", &(goal.missionary_right), &(goal.cannibal_right), &(goal.boat_right));

	fclose(start_state);
	fclose(goal_state);

	//solving
	uninformed_search(&start, &goal);

	
	return 0;
}
