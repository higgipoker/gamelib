#include "converter.h"

namespace GameLib {

// ------------------------------------------------------------
// IntToString
// ------------------------------------------------------------
std::string IntToString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

// ------------------------------------------------------------
// split a string
// ------------------------------------------------------------
std::vector<std::string> split(std::string str) {
	std::vector<std::string> internal;
	std::stringstream ss(str);  // Turn the string into a stream.
	std::string tok;

	while (std::getline(ss, tok, ' ')) {
		internal.push_back(tok);
	}

	return internal;
}

}// GameLib
