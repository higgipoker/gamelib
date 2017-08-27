#pragma once

#include <SFML/System/Clock.hpp>

namespace GameLib{

enum input_event {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	FIRE_DOWN,
	FIRE_UP,
	FIRE_LENGTH,
	FIRE_LENGTH_CACHED,
	SINGLE_TAP,
	DOUBLE_TAP,
    FIRE_PRESS,
	TOTAL_EVENTS
};

class Input {
public:

	Input();
	virtual ~Input(){};
	virtual void Update();

	/// event states
	int event_states[TOTAL_EVENTS];


protected:
	sf::Clock fire_timer;
};

}// GameLib
