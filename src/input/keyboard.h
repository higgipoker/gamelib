#pragma once
#include "input.h"
#include <map>

namespace GameLib {

/**
* @brief The Keyboard class
*/
class Keyboard : public Input {

  public:
	/**
	 * @brief Keyboard
	 */
	Keyboard();

	/**
	 * @brief Update
	 */
	virtual void Update() override;

	static std::map<int, std::string> keys;
};

} // GameLib
