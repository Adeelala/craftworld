#include "LocatePlayerAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::LocatePlayerAction, "LocatePlayerAction")

namespace CraftWorld::Actions {
	LocatePlayerAction::LocatePlayerAction(const std::string& source, const std::string& username) : Action("LocatePlayerAction", source), username(username) {
	}
}