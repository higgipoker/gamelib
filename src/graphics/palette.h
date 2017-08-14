#pragma once

#include <vector>
#include "color.h"

namespace GameLib{

/**
	* @brief color swapping palette
	*/
class Palette{

public:
	/// color map
	std::vector< std::pair< Color, Color > > colors;

};

}// GameLib
