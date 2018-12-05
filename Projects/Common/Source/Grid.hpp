#pragma once

#include <map>
#include <memory>
#include <vector>
#include <utility>

#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	template<typename ItemType, typename PositionValueType>
	class Grid {
			using PositionType = Utility::Vector3D<PositionValueType>;

			std::vector<ItemType> items_;

			std::map<std::shared_ptr<ItemType>, PositionType> itemPositions_;

		public:
			typename std::vector<ItemType>::iterator begin();

			typename std::vector<ItemType>::const_iterator begin() const;

			typename std::vector<ItemType>::iterator end();

			typename std::vector<ItemType>::const_iterator end() const;

			/**
			 * Gets the items at the specified position.
			 * @param position The position to retrieve.
			 * @return The items.
			 */
			std::vector<ItemType> get(const PositionType& position) const;

			/**
			 * Gets all items in this grid.
			 * @return All items.
			 */
			std::vector<ItemType> getAll() const;

			/**
			 * Places a new item at the specified position.
			 * @param item The item to place.
			 * @param position The position to place the item.
			 */
			void place(const ItemType& item, const PositionType& position);

			/**
			 * Moves all items from the specified old position to a new position.
			 * @param oldPosition The old position.
			 * @param newPosition The new position.
			 */
			void move(const PositionType& oldPosition, const PositionType& newPosition);
	};
}
