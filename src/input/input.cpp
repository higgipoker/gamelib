#include "input.h"

namespace GameLib {

// ------------------------------------------------------------
// Input
// ------------------------------------------------------------
Input::Input() {
	Reset();
}

// ------------------------------------------------------------
// ~Input
// ------------------------------------------------------------
Input::~Input() {
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Input::Update() {
}

// ------------------------------------------------------------
// Reset
// ------------------------------------------------------------
void Input::Reset() {
	event_states[UP] = 0;
	event_states[DOWN] = 0;
	event_states[LEFT] = 0;
	event_states[RIGHT] = 0;
	event_states[FIRE_DOWN] = 0;
	event_states[FIRE_UP] = 0;
	event_states[FIRE_LENGTH] = 0;
	event_states[SINGLE_TAP] = 0;
	event_states[DOUBLE_TAP] = 0;
}
} // GameLib
