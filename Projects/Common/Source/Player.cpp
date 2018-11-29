#include "Player.hpp"

namespace CraftWorld {
	Entity Player::removeFromInventory(const int& itemIndex) {
		// Get the entity
		Entity entity = inventory[itemIndex];

		// Remove from the inventory
		inventory.erase(inventory.begin() + itemIndex);

		// Return the entity
		return entity;
	}

	void Player::putInInventory(const Entity& entity) {
		inventory.push_back(entity);
	}

	void Player::clearInventory() {
		inventory.clear();
	}
}
