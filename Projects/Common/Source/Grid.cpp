#include "Grid.hpp"

#include <algorithm>

namespace CraftWorld {
	template<typename ItemType, typename PositionType>
	typename std::vector<ItemType>::iterator Grid<ItemType, PositionType>::begin() {
		return items_.begin();
	}

	template<typename ItemType, typename PositionType>
	typename std::vector<ItemType>::const_iterator Grid<ItemType, PositionType>::begin() const {
		return items_.cbegin();
	}

	template<typename ItemType, typename PositionType>
	typename std::vector<ItemType>::iterator Grid<ItemType, PositionType>::end() {
		return items_.end();
	}

	template<typename ItemType, typename PositionType>
	typename std::vector<ItemType>::const_iterator Grid<ItemType, PositionType>::end() const {
		return items_.cend();
	}

	template<typename ItemType, typename PositionType>
	std::vector<ItemType> Grid<ItemType, PositionType>::get(const PositionType& position) const {
		std::vector<ItemType> result;

		for(auto iterator = items_.begin(); (iterator = std::find_if(
			iterator, items_.end(), [&](const ItemType& item) {
				return itemPositions_[&item] == position;
			}
		)) != items_.end(); ++iterator) {
			result.push_back(*iterator);
		}

		return result;
	}

	template<typename ItemType, typename PositionType>
	std::vector<ItemType> Grid<ItemType, PositionType>::getAll() const {
		return items_;
	}

	template<typename ItemType, typename PositionType>
	void Grid<ItemType, PositionType>::place(const ItemType& item, const PositionType& position) {
		items_.push_back(item);
		itemPositions_[std::make_shared<ItemType>(*--items_.end())] = position;
	}

	template<typename ItemType, typename PositionType>
	void Grid<ItemType, PositionType>::move(const PositionType& oldPosition, const PositionType& newPosition) {
		for(auto iterator = itemPositions_.begin(); (iterator = std::find_if(
			iterator, itemPositions_.end(), [&](const auto& itemPosition) {
				return itemPosition.second == oldPosition;
			}
		)) != items_.end(); ++iterator) {
			*iterator.second = newPosition;
		}
	}
}
