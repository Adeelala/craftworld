#include "Action.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::Action, "Action")

namespace CraftWorld::Actions {
	Action::Action(const std::string& name, const std::string& source) : name(name), source(source) {
	}
}