#include "console.h"

#include "../game/game.h"
#include "../graphics/color.h"
#include "../graphics/primitives.h"
#include "../utils/converter.h"
#include <iostream>
#include <sstream>

namespace GameLib {

const std::string PREFIX = ":> ";
const std::string CURSOR = "_";

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Console::Console(Game *g)
 : GameEntity(new Physical(), this)
 , height(200)
 , text("fonts/terminus_bold.ttf", 20)
 , cursor("fonts/terminus_bold.ttf", 20)
 , game(g) {
	hud = true;
	text.SetColor(Color(0, 255, 0, 255));
	cursor.SetColor(Color(0, 255, 0, 255));

	name = "console";
	visible = false;
	history_iterator = 0;

	timer.Start();
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Console::~Console() {
	delete physical;
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Console::Render(Window &window) {
	if (visible) {

		//
		// draw background
		//
		Primitives::FillColor(Color(0, 0, 0, 255));
		Primitives::OutlineColor(Color(0, 0, 0, 255));
		Primitives::Rectangle(window, 0, 0, window.GetSize().x, height);

		Primitives::OutlineColor(Color(255, 255, 255, 255));
		Primitives::DrawLine(window, Vector3(0, 10), Vector3(window.GetSize().x, 10), 3);

		// std::cout << window.GetSize().x << std::endl;

		//
		// draw history
		//
		int line_height = 22;
		int y = height;
		y -= line_height;
		// 		for (auto it = history.rbegin(); it != history.rend(); ++it) {
		// 			text.SetText (*it);
		// 			y -= line_height;
		// 			text.SetPosition (0, y);
		// 			text.Render (window);
		// 		}

		//
		// draw echo list
		//
		for (auto it = echo_list.rbegin(); it != echo_list.rend(); ++it) {
			text.SetText("* " + *it);
			y -= line_height;
			text.SetPosition(0, y);
			text.Render(window);
		}

		//
		// draw current line
		//
		text.SetText(PREFIX + current_line);
		text.SetPosition(0, height - line_height);
		text.Render(window);

		if (timer.GetTicks() > 500) {
			timer.Start();
			show_cursor = !show_cursor;
		}

		//
		// draw cursor
		//
		std::string cursor_text;
		if (show_cursor) {
			for (int i = 0; i < current_line.size() + PREFIX.size(); ++i) {
				cursor_text += " ";
			}
			cursor_text += "_";
		}
		cursor.SetText(cursor_text);
		cursor.SetPosition(0, height - line_height);
		cursor.Render(window);
	}
}

// ------------------------------------------------------------
// OnKey
// ------------------------------------------------------------
void Console::OnKey(std::string &character) {

	if (character == "tab" || character == "escape") {
		visible = !visible;
		return;
	}

	if (visible) {
		if (character == "return") {
			execute();
			return;
		}

		if (character == "backspace") {
			if (current_line.length()) {
				current_line.pop_back();
			}
			return;
		}

		if (character == "up") {
			if (history.size()) {
				if (--history_iterator < 0) {
					history_iterator = 0;
				} else {
					current_line = history[history_iterator];
				}
			}
			return;
		}

		if (character == "down") {
			if (history.size()) {
				if (++history_iterator >= history.size()) {
					history_iterator = history.size() - 1;
				}
				current_line = history[history_iterator];
			}
			return;
		}

		if (character == "dash") {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
				character = "_";
			} else {
				character = "-";
			}
		}

		current_line += character;
	}
}

// ------------------------------------------------------------
// execute
// ------------------------------------------------------------
void Console::execute() {

	std::vector<std::string> spl = split(current_line);

	std::cout << "execute command: " << spl[0] << std::endl;

	history.push_back(current_line);
	history_iterator = history.size();
	current_line.clear();

	if (spl[0] == "echo") {
		if (spl.size() > 1) {
			echo_list.push_back(spl[1]);
		}
	}

	else {
		game->Call(spl);
	}
}

void Console::Echo(const std::vector<std::string> &texts) {
	for (auto it = texts.begin(); it != texts.end(); ++it) {
		echo_list.push_back(*it);
	}
}

} // GameLib
