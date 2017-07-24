#include "converter.h"

namespace GameLib {

// ------------------------------------------------------------
// IntToString
// ------------------------------------------------------------
std::string IntToString (int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

}// GameLib
