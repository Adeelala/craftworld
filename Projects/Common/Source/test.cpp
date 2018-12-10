//g++ test.cpp -o test_exe
//https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm
#include <iostream>
#include <vector>

typedef std::vector<int> int_vec_t;

/*
These functions will check if you can move in a certain direction.
These functions will return either true or false. The function that calls these
functions will have to send the current coordinates of the player and what the next block
is in that specific direction.

North = z-axis + 1
South = z-axis - 1
East = x-axis + 1
West = x-axis - 1

Assuming: 
dirt = 0
air = 1
player_self = 2
and player_other = 3



*/


int_vec_t moveNorth(int_vec_t map, int_vec_t player){
	/*When accessing the 3d vector it might be easier to use it as
	a single contiguous array*/
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	/*The array is saved as X-values, Y-values, Z-values so to
	make it easier to access it, we will calculate where all the values
	are placed in the vector.*/

	/* the x-values are located between 0 and map_vector_dimension_size(mvds) - 1 */
	//int map_x_loc_end = map_vector_dimension_size - 1;
	/* the y-values are located between mvds and (mvds * 2) - 1 */
	//int map_y_loc_end = (map_vector_dimension_size * 2) - 1;
	/* the z-values are located between mvds * 2 and (mvds * 3) - 1 */
	//int map_z_loc_end = (map_vector_dimension_size * 3) - 1;

	/*The player vector should only contain an x,y,z coordinate of the bottom half.
	Which we will have to use for the calculations.
	*/
	int player_x = player[0];
	int player_y = player[1];
	int player_z = player[2];

	/*Now that we have all the necessary data, we can start moving the character*/

	/*Check if the player is trying to move out of bounds into a different map*/
	if(player_z + 1 > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(player_y + 1 > map_vector_dimension_size - 1){
			/*!!Need to discuss what needs to be returned if the player cannot move*/
			return map, player;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player_x][player_y][player_z + 1] == 0 && map[player_x][player_y + 1][player_z + 1]){
			/*Old position gets filled with air*/
			map[player_x][player_y][player_z] = 1;
			map[player_x][player_y][player_z] = 1;

			/*New position gets filled with player*/
			map[player_x][player_y][player_z + 1] = 2;
			map[player_x][player_y + 1][player_z + 1] = 2;

			player[0] = player_x;
			player[1] = player_y;
			player[2] = player_z + 1;

		}
		else{
			/*!!Need to discuss what needs to be returned if the player cannot move*/
			return map, player;
		}	

	}




}



int main()
{
  std::cout << "Hello World!";
}