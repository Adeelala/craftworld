/*
useable functions

All movement functions returns int_vec_t map:
int_vec_t moveNorth(int_vec_t map, player_coord player, int playerID);
int_vec_t moveEast(int_vec_t map, player_coord player, int playerID);
int_vec_t moveSouth(int_vec_t map, player_coord player, int playerID);
int_vec_t moveWest(int_vec_t map, player_coord player, int playerID);

All remove and put block functions returns int_vec_t map;
int_vec_t removeBlockNorth(int_vec_t map, player_coord player, int playerID);
int_vec_t removeBlockNorth(int_vec_t map, player_coord player, int playerID);
int_vec_t removeBlockNorth(int_vec_t map, player_coord player, int playerID);
int_vec_t removeBlockNorth(int_vec_t map, player_coord player, int playerID);


int_vec_t standStill(int_vec_t map, player_coord player, int playerID);


*/
#include <iostream>
#include <vector>
#include "Utility/Vector3D.hpp"

typedef std::vector<std::vector<std::vector<int> > >  int_vec_t;
typedef CraftWorld::Utility::Vector3D<int> player_coord;

/*
These functions will check if you can move in a certain direction.

North = z-axis + 1
South = z-axis - 1
East = x-axis + 1
West = x-axis - 1

Assuming: 
dirt = 0
air = 1
player = playerID
*/

/*

===============================================================

Movement functions

===============================================================

*/

int_vec_t moveNorth(int_vec_t map, player_coord player, int playerID){
	/*When accessing the 3d vector it might be easier to use it as
	a single contiguous array*/
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	/*The array is saved as X-values, Y-values, Z-values so to
	make it easier to access it, we will access them as array[X][Y][Z].*/

	/*The player vector should only contain an x,y,z coordinate of the bottom half.
	Which we will have to use for the calculations.
	*/

	/*Now that we have all the necessary data, we can start moving the character*/
	/*Check if the player is trying to move out of bounds into a different map*/
	if(abs(player.z + 1) > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
		/*For now the player has to manually change server, so we will just keep them at the location they are in*/
		/*!!Maybe we can remove the player at this point?*/
		return map;
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(abs(player.y + 1) > map_vector_dimension_size - 1){
			/*If the player cannot be moved just return the map and player as is*/
			return map;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player.x][player.y][player.z + 1] != 0 && map[player.x][player.y + 1][player.z + 1] != 0){
			/*Old position gets filled with air*/
			map[player.x][player.y][player.z] = 1;
			map[player.x][player.y][player.z] = 1;

			/*New position gets filled with player*/
			map[player.x][player.y][player.z + 1] = playerID;
			map[player.x][player.y + 1][player.z + 1] = playerID;

		}
		else{
			/*If the player cannot be moved just return the map as is*/
			return map;
		}	

	}

}

int_vec_t moveEast(int_vec_t map, player_coord player, int playerID){
	
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*Check if the player is trying to move out of bounds into a different map*/
	if(abs(player.x + 1) > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
		return map;
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(abs(player.y + 1) > map_vector_dimension_size - 1){
			/*If the player cannot be moved just return the map and player as is*/
			return map;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player.x + 1][player.y][player.z] != 0 && map[player.x + 1][player.y + 1][player.z] != 0){
			/*Old position gets filled with air*/
			map[player.x][player.y][player.z] = 1;
			map[player.x][player.y][player.z] = 1;

			/*New position gets filled with player*/
			map[player.x + 1][player.y][player.z] = playerID;
			map[player.x + 1][player.y + 1][player.z] = playerID;;

		}
		else{
			/*If the player cannot be moved just return the map as is*/
			return map;
		}	

	}

}

int_vec_t moveSouth(int_vec_t map, player_coord player, int playerID){
	/*When accessing the 3d vector it might be easier to use it as
	a single contiguous array*/
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	if(abs(player.z - 1) > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
		/*For now the player has to manually change server, so we will just keep them at the location they are in*/
		/*!!Maybe we can remove the player at this point?*/
		return map;
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(abs(player.y) - 1 > map_vector_dimension_size - 1){
			/*If the player cannot be moved just return the map and player as is*/
			return map;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player.x][player.y][player.z - 1] != 0 && map[player.x][player.y + 1][player.z - 1] != 0){
			/*Old position gets filled with air*/
			map[player.x][player.y][player.z] = 1;
			map[player.x][player.y][player.z] = 1;

			/*New position gets filled with player*/
			map[player.x][player.y][player.z - 1] = playerID;
			map[player.x][player.y + 1][player.z - 1] = playerID;

		}
		else{
			/*If the player cannot be moved just return the map as is*/
			return map;
		}	

	}

}


int_vec_t moveWest(int_vec_t map, player_coord player, int playerID){
	
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*Check if the player is trying to move out of bounds into a different map*/
	if(abs(player.x - 1) > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
		return map;
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(abs(player.y + 1) > map_vector_dimension_size - 1){
			/*If the player cannot be moved just return the map and player as is*/
			return map;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player.x - 1][player.y][player.z] != 0 && map[player.x - 1][player.y + 1][player.z] != 0){
			/*Old position gets filled with air*/
			map[player.x][player.y][player.z] = 1;
			map[player.x][player.y][player.z] = 1;

			/*New position gets filled with player*/
			map[player.x - 1][player.y][player.z] = playerID;
			map[player.x - 1][player.y + 1][player.z] = playerID;;

		}
		else{
			/*If the player cannot be moved just return the map as is*/
			return map;
		}	

	}

}

int_vec_t standStill(int_vec_t map, player_coord player, int playerID){
	return map;
}

/*

===============================================================

Removing blocks

===============================================================

*/



int_vec_t removeBlockNorth(int_vec_t map, player_coord player, int playerID){
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*If the block in front of the player is something you can grab, then remove it*/
	if(abs(player.z + 1) < map_vector_dimension_size - 1){
		if(map[player.x][player.y][player.z + 1] == 0){

			/*Old block position gets filled with air*/
			map[player.x][player.y][player.z + 1] = 1;
		}
		else{
			/*If there is no block to remove just return the map*/
			return map;
		}	

	}
}

int_vec_t removeBlockSouth(int_vec_t map, player_coord player, int playerID){
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*If the block in front of the player is something you can grab, then remove it*/
	if(abs(player.z - 1) < map_vector_dimension_size - 1){
		if(map[player.x][player.y][player.z - 1] == 0){

			/*Old block position gets filled with air*/
			map[player.x][player.y][player.z - 1] = 1;
		}
		else{
			/*If there is no block to remove just return the map*/
			return map;
		}	

	}
}

int_vec_t removeBlockEast(int_vec_t map, player_coord player, int playerID){
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*If the block in front of the player is something you can grab, then remove it*/
	if(abs(player.x + 1) < map_vector_dimension_size - 1){
		if(map[player.x + 1][player.y][player.z] == 0){

			/*Old block position gets filled with air*/
			map[player.x + 1][player.y][player.z] = 1;
		}
		else{
			/*If there is no block to remove just return the map*/
			return map;
		}	

	}
}

int_vec_t removeBlockWest(int_vec_t map, player_coord player, int playerID){
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	

	/*If the block in front of the player is something you can grab, then remove it*/
	if(abs(player.x - 1) < map_vector_dimension_size - 1){
		if(map[player.x - 1][player.y][player.z] == 0){

			/*Old block position gets filled with air*/
			map[player.x - 1][player.y][player.z] = 1;
		}
		else{
			/*If there is no block to remove just return the map*/
			return map;
		}	

	}
}



