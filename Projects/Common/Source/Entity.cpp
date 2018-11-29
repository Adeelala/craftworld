#include "Entity.hpp"

namespace CraftWorld {
	Entity::Entity(const Entity::Position& position, Entity::Velocity& velocity) : position(position), velocity(velocity) {
	}

	void Entity::update() {
		// Update position based on velocity
		position += velocity;
	}

	void Entity::speedUp(const Entity::Velocity& velocity) {
		this->velocity += velocity;
	}

	void Entity::slowDown(const Entity::Velocity& velocity) {
		this->velocity -= velocity;
	}

	void Entity::stop() {
		this->velocity = Entity::Velocity(0, 0, 0);
	}
}
