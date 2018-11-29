#pragma once

#include "Vector3D.hpp"

namespace CraftWorld {
	class Entity {
			using Position = Vector3D<int>;
			using Velocity = Vector3D<int>;

			/**
			 * The current location in the world.
			 */
			Position position;

			/**
			 * The current velocity in the x, y and z directions.
			 */
			Velocity velocity;

		public:
			Entity(const Position& position, Velocity& velocity);

			virtual void update();

			void speedUp(const Velocity& velocity);

			void slowDown(const Velocity& velocity);

			void stop();
	};
}
