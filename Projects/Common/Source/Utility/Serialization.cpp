#include "Serialization.hpp"

namespace CraftWorld::Utility::Serialization {
	std::shared_ptr<Actions::Action> fromString(const std::string& serializedAction) {
		std::stringstream stringStream;
		stringStream << serializedAction;
		boost::archive::text_iarchive archive(stringStream);
		archive.register_type(static_cast<Actions::ConnectAction*>(nullptr));
		archive.register_type(static_cast<Actions::FoundPlayerAction*>(nullptr));
		archive.register_type(static_cast<Actions::GetWorldAction*>(nullptr));
		archive.register_type(static_cast<Actions::LocatePlayerAction*>(nullptr));
		archive.register_type(static_cast<Actions::MoveAction*>(nullptr));
		archive.register_type(static_cast<Actions::PlaceBlockAction*>(nullptr));
		archive.register_type(static_cast<Actions::PickUpBlockAction*>(nullptr));
		archive.register_type(static_cast<Actions::RefreshWorldAction*>(nullptr));

		std::shared_ptr<Actions::Action> action;
		archive >> BOOST_SERIALIZATION_NVP(action);

		return action;
	}
}