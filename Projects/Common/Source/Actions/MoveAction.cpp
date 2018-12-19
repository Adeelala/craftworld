#include "MoveAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::MoveAction, "MoveAction")

namespace CraftWorld::Actions {
	MoveAction::MoveAction(const int& source, const Direction& direction) : Action("MoveAction", source), direction(direction) {
	}
}