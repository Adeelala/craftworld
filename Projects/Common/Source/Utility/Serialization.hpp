#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "../Actions/Action.hpp"
#include "../Actions/ConnectAction.hpp"
#include "../Actions/LocatePlayerAction.hpp"
#include "../Actions/FoundPlayerAction.hpp"
#include "../Actions/RefreshWorldAction.hpp"
#include "../Actions/GetWorldAction.hpp"
#include "../Actions/MoveAction.hpp"

namespace CraftWorld::Utility::Serialization {
	std::shared_ptr<Actions::Action> fromString(const std::string& serializedAction);

	template <typename ActionType>
	std::string toString(const std::shared_ptr<ActionType>& action) {
		std::stringstream stringStream;
		boost::archive::text_oarchive archive(stringStream);
		archive.register_type(static_cast<Actions::ConnectAction*>(nullptr));
		archive.register_type(static_cast<Actions::FoundPlayerAction*>(nullptr));
		archive.register_type(static_cast<Actions::GetWorldAction*>(nullptr));
		archive.register_type(static_cast<Actions::LocatePlayerAction*>(nullptr));
		archive.register_type(static_cast<Actions::MoveAction*>(nullptr));
		archive.register_type(static_cast<Actions::RefreshWorldAction*>(nullptr));
		archive << BOOST_SERIALIZATION_NVP(action);

		return stringStream.str();
	}
}