#include <iostream>
#include "keyboard.h"
#include <SFML/Window/Keyboard.hpp>

namespace GameLib {
std::map< int, std::string> Keyboard::keys;
Keyboard::Keyboard(){
	int code = 0;
	keys.insert(std::make_pair(code++, "a"));
	keys.insert(std::make_pair(code++, "b"));
	keys.insert(std::make_pair(code++, "c"));
	keys.insert(std::make_pair(code++, "d"));
	keys.insert(std::make_pair(code++, "e"));
	keys.insert(std::make_pair(code++, "f"));
	keys.insert(std::make_pair(code++, "g"));
	keys.insert(std::make_pair(code++, "h"));
	keys.insert(std::make_pair(code++, "i"));
	keys.insert(std::make_pair(code++, "j"));
	keys.insert(std::make_pair(code++, "k"));
	keys.insert(std::make_pair(code++, "l"));
	keys.insert(std::make_pair(code++, "m"));
	keys.insert(std::make_pair(code++, "n"));
	keys.insert(std::make_pair(code++, "o"));
	keys.insert(std::make_pair(code++, "p"));
	keys.insert(std::make_pair(code++, "q"));
	keys.insert(std::make_pair(code++, "r"));
	keys.insert(std::make_pair(code++, "s"));
	keys.insert(std::make_pair(code++, "t"));
	keys.insert(std::make_pair(code++, "u"));
	keys.insert(std::make_pair(code++, "v"));
	keys.insert(std::make_pair(code++, "w"));
	keys.insert(std::make_pair(code++, "x"));
	keys.insert(std::make_pair(code++, "y"));
	keys.insert(std::make_pair(code++, "z"));

	code = 26;
	keys.insert(std::make_pair(code++, "0"));
	keys.insert(std::make_pair(code++, "1"));
	keys.insert(std::make_pair(code++, "2"));
	keys.insert(std::make_pair(code++, "3"));
	keys.insert(std::make_pair(code++, "4"));
	keys.insert(std::make_pair(code++, "5"));
	keys.insert(std::make_pair(code++, "6"));
	keys.insert(std::make_pair(code++, "7"));
	keys.insert(std::make_pair(code++, "8"));
	keys.insert(std::make_pair(code++, "9"));

	keys.insert(std::make_pair(57, " "));

	keys.insert(std::make_pair(58, "return"));
	keys.insert(std::make_pair(60, "tab"));
	keys.insert(std::make_pair(59, "backspace"));
	keys.insert(std::make_pair(73, "up"));
	keys.insert(std::make_pair(74, "down"));
}

void Keyboard::Update() {
	event_states[FIRE_UP] = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		event_states[UP] = 1;
	}else{
		event_states[UP] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		event_states[DOWN] = 1;
	}else{
		event_states[DOWN] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		event_states[LEFT] = 1;
	}else{
		event_states[LEFT] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		event_states[RIGHT] = 1;
	}else{
		event_states[RIGHT] = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
		if(event_states[FIRE_DOWN] == 0){
			fire_timer.restart();
			event_states[FIRE_DOWN] = 1;
		}else{
			event_states[FIRE_LENGTH] = fire_timer.getElapsedTime().asMilliseconds();
		}
	}else if (event_states[FIRE_DOWN] == 1){
		event_states[FIRE_UP] = 1;
		event_states[FIRE_DOWN] = 0;
		event_states[FIRE_LENGTH_CACHED] = fire_timer.getElapsedTime().asMilliseconds();
		event_states[FIRE_LENGTH] = 0;
	}
}

}// GameLib

