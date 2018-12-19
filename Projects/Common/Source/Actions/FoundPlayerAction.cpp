#include "FoundPlayerAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::FoundPlayerAction, "FoundPlayerAction")

namespace CraftWorld::Actions {
	FoundPlayerAction::FoundPlayerAction(const int& source, const std::string& username) : Action("FoundPlayerAction", source), username(username) {
	}
}