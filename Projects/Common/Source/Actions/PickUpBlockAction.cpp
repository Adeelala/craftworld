#include "PickUpBlockAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::PickUpBlockAction, "PickUpBlockAction")

namespace CraftWorld::Actions {
	PickUpBlockAction::PickUpBlockAction(const int& source, const Direction& direction) : Action("PickUpBlockAction", source), direction(direction) {
	}
}