//g++ test.cpp -o test_exe
//https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm
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
player_self = 2
and player_other = 3
*/


int_vec_t moveNorth(int_vec_t map, player_coord player, int playerID){
	/*When accessing the 3d vector it might be easier to use it as
	a single contiguous array*/
	int map_vector_dimension_size = map.size() / 3;
	int single_2d_row = (map.size() / map_vector_dimension_size) / map_vector_dimension_size;
	/*The array is saved as X-values, Y-values, Z-values so to
	make it easier to access it, we will calculate where all the values
	are placed in the vector.*/

	/* the x-values are located between 0 and map_vector_dimension_size(mvds) - 1 */
	/* the y-values are located between mvds and (mvds * 2) - 1 */
	/* the z-values are located between mvds * 2 and (mvds * 3) - 1 */

	/*The player vector should only contain an x,y,z coordinate of the bottom half.
	Which we will have to use for the calculations.
	*/

	/*Now that we have all the necessary data, we can start moving the character*/

	/*Check if the player is trying to move out of bounds into a different map*/
	if(player.z + 1 > map_vector_dimension_size - 1){
		/*!!Need to discuss how to swap to another map!!*/
	}
	else{
		/*Check if the players upper body will stay in the map*/
		if(player.y + 1 > map_vector_dimension_size - 1){
			/*If the player cannot be moved just return the map and player as is*/
			return map;

		}

		/*Check if the block in the northern direction of the players'lower body half 
		is a dirt block
			&&
		Check if the block in the northern direction near the upper half of the body 
		is a dirk block*/
		//if(map[(map_y_loc_end + 1) + player_z] == 0 && map[(map_y_loc_end + 1) + player_z] == 0){

		else if(map[player.x][player.y][player.z + 1] == 0 && map[player.x][player.y + 1][player.z + 1]){
			/*Old position gets filled with air*/
			map[player.x][player.y][player.z] = 1;
			map[player.x][player.y][player.z] = 1;

			/*New position gets filled with player*/
			map[player.x][player.y][player.z + 1] = playerID;
			map[player.x][player.y + 1][player.z + 1] = playerID;

			
			//player_z = player.z + 1;

		}
		else{
			/*If the player cannot be moved just return the map as is*/
			return map;
		}	

	}




}



// int main()
// {
//   std::cout << "Hello World!";
// }