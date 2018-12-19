#include "ConnectAction.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Actions::ConnectAction, "ConnectAction")

namespace CraftWorld::Actions {
	ConnectAction::ConnectAction(const int& source, const std::string& username) : Action("ConnectAction", source), username(username) {
	}
}