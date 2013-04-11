#include "cannibal_support.h"

void uninformed_search(struct state * start, struct state * goal){
	int depth=0;
	int expanded_nodes = 0;
	int i;
	int j;

	//For keeping track of states already visited
	int missionaries = (start->missionary_right + start->missionary_left);
	int cannibals = (start->cannibal_left + start->cannibal_right);
	struct state state_array[DEPTH_MAX];
	char ** state_table = malloc(sizeof(char*) * (missionaries + 1));
	for(i=0;i<(missionaries + 1); i++){
		state_table[i] = malloc(sizeof(char) * (cannibals + 1));
	}

	//Iterated depth search
	for(depth=0;depth<DEPTH_MAX;depth++){
		for(i=0;i<(missionaries + 1);i++){
			for(j=0;j<(cannibals + 1);j++){
				state_table[i][j] = 0;
			}
		}
		if(depth_limited_search(depth, start, goal, &expanded_nodes, state_array, state_table)){
			printf("Solution found at %i depth\n", depth);
			printf("%i nodes expanded\n", expanded_nodes);
			for(i=depth;i>0;i--){
				print_state(&state_array[i]);
			}
			break;
			
		}
	}
}

char depth_limited_search(int depth, struct state * start, struct state * goal, int * expanded_nodes, struct state * state_array, char ** state_table){
	struct state buffer;

	//Was this state visited?
	char visited = state_table[start->missionary_left][start->cannibal_left];

	if((visited & BOAT_LEFT) && (start->boat_left)){
		return 0;
	}
	else if((visited & BOAT_RIGHT) && (start->boat_right)){
		return 0;
	}
	else if(start->boat_left){
		state_table[start->missionary_left][start->cannibal_left] |= BOAT_LEFT;
	}
	else if(start->boat_right){
		state_table[start->missionary_left][start->cannibal_left] |= BOAT_RIGHT;
	}

	//Keep expanded node counter running
	*expanded_nodes += 1;

	//Already done?
	if(check_state(start, goal) > 0){
		return 1;
	}
	//Cannibals eat missionaries?
	else if(check_state(start, goal) < 0){
//		printf("Cannibals eat missionaries\n");
		return 0;
	}
	//Too deep?
	else if(depth < 0){
		return 0;
	}
	//Dive deeper!
	else{
		//if right shore
		if(start->boat_right){
//			printf("on right shore\n");

			//move cannibal
			if(start->cannibal_right > 0){
//				printf("sending a cannibal left\n");
				buffer = *start;
				buffer.cannibal_right --;
				buffer.cannibal_left ++;
				buffer.boat_right = 0;
				buffer.boat_left = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("1 cannibal left\n");
					state_array[depth] = buffer;
					return 1;
				}
			}
			//move 2 cannibals
			if(start->cannibal_right > 1){
				buffer = *start;
				buffer.cannibal_right -= 2;
				buffer.cannibal_left += 2;
				buffer.boat_right = 0;
				buffer.boat_left = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("2 cannibals left\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 1 missionary
			if(start->missionary_right > 0){
				buffer = *start;
				buffer.missionary_right -= 1;
				buffer.missionary_left += 1;
				buffer.boat_right = 0;
				buffer.boat_left = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes,state_array, state_table)){
					//printf("1 missionary left\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 2 missionaries
			if(start->missionary_right > 1){
				buffer = *start;
				buffer.missionary_right -= 2;
				buffer.missionary_left += 2;
				buffer.boat_right = 0;
				buffer.boat_left = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("2 missionaries left\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 1 missionary 1 cannibal
			if(start->missionary_right && start->cannibal_right){
				buffer = *start;
				buffer.missionary_right -= 1;
				buffer.missionary_left += 1;
				buffer.cannibal_right -= 1;
				buffer.cannibal_left += 1;
				buffer.boat_right = 0;
				buffer.boat_left = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("1 missionary 1 cannibal  left\n");
					state_array[depth] = buffer;

					return 1;
				}
			}

		


				

		}

		//if left shore
		else if(start->boat_left){
			//printf("on left shore\n");
			//move cannibal
			if(start->cannibal_left > 0){
//				printf("sending a cannibal right\n");

				buffer = *start;
				buffer.cannibal_left --;
				buffer.cannibal_right ++;
				buffer.boat_left = 0;
				buffer.boat_right = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("1 cannibal right\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 2 cannibals
			if(start->cannibal_left > 1){
				buffer = *start;
				buffer.cannibal_left -= 2;
				buffer.cannibal_right += 2;
				buffer.boat_left = 0;
				buffer.boat_right = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("2 cannibals right\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 1 missionary
			if(start->missionary_left > 0){
				buffer = *start;
				buffer.missionary_left -= 1;
				buffer.missionary_right += 1;
				buffer.boat_left = 0;
				buffer.boat_right = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("1 missionary right\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 2 missionaries
			if(start->missionary_left > 1){
				buffer = *start;
				buffer.missionary_left -= 2;
				buffer.missionary_right += 2;
				buffer.boat_left = 0;
				buffer.boat_right = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("2 missionaries right\n");
					state_array[depth] = buffer;

					return 1;
				}
			}
			//move 1 missionary 1 cannibal
			if(start->missionary_left && start->cannibal_left){
				buffer = *start;
				buffer.missionary_left -= 1;
				buffer.missionary_right += 1;
				buffer.cannibal_left -= 1;
				buffer.cannibal_right += 1;
				buffer.boat_left = 0;
				buffer.boat_right = 1;
				if(depth_limited_search(depth-1, &buffer, goal, expanded_nodes, state_array, state_table)){
					//printf("1 missionary 1 cannibal right\n");
					state_array[depth] = buffer;

					return 1;
				}
			}


		}
	}
	return 0;
}

char check_state(struct state * current, struct state * goal){
	if((current->missionary_left == goal->missionary_left) &&
		(current->cannibal_left == goal->cannibal_left) &&
		(current->boat_left == goal->boat_left) &&
		(current->missionary_right == goal->missionary_right) &&
		(current->cannibal_right == goal->cannibal_right) &&
		(current->boat_right == goal->boat_right)){
			return 1;
	}
	else if((current->missionary_left) && (current->missionary_left < current->cannibal_left)){
		return -1;
	}
	else if((current->missionary_right) && (current->missionary_right < current->cannibal_right)){
		return -1;
	}
	
	else{
		return 0;
	}
}

void print_state(struct state * input){
	printf("%i,%i,%i\n%i,%i,%i\n\n", input->missionary_left, input->cannibal_left, input->boat_left, input->missionary_right, input->cannibal_right, input->boat_right);
}
