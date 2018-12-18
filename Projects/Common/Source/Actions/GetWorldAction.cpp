#include "GetWorldAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::GetWorldAction, "GetWorldAction")

namespace CraftWorld::Actions {
	GetWorldAction::GetWorldAction(const std::string& source) : Action("GetWorldAction", source) {
	}
}