#pragma once
#include <map>
#include "input.h"

namespace GameLib{

class Keyboard : public Input{

public:
	Keyboard();
	virtual void Update() override;

	static std::map< int, std::string> keys;


protected:

};

}// GameLib
