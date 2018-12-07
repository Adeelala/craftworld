
#ifndef DELEGATE_HPP
#define DELEGATE_HPP


#include <vector>
#include "Grid.hpp"
#include "Chunk.hpp"

namespace CraftWorld {
	class World :
		public Grid<Chunk, int>  {
            
        };
}

#endif /* DELEGATE_HPP */

