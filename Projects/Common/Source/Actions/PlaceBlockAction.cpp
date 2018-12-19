#include "PlaceBlockAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::PlaceBlockAction, "PlaceBlockAction")

namespace CraftWorld::Actions {
	PlaceBlockAction::PlaceBlockAction(const int& source, const Direction& direction) : Action("PlaceBlockAction", source), direction(direction) {
	}
}