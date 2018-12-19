#include "RefreshWorldAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::RefreshWorldAction, "RefreshWorldAction")

namespace CraftWorld::Actions {
	RefreshWorldAction::RefreshWorldAction(const int& source, const World& world) : Action("RefreshWorldAction", source), world(world) {
	}
}