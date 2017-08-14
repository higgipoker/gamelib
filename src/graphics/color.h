#pragma once

namespace GameLib{

class Color{
public:
	/**
	 * @brief constructor
	 */
	Color();

	/**
	 * @brief constructor
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	Color(int red, int green, int blue, int alpha);

	/// components
	int r, g, b, a;
};

}// GameLib
