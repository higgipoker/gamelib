#include "console.h"

#include <iostream>
#include <sstream>
#include "../game/game.h"
#include "../graphics/primitives.h"
#include "../graphics/color.h"

namespace GameLib {

const std::string PREFIX = ":> ";
const std::string CURSOR = "_";

// ------------------------------------------------------------
// split a string
// ------------------------------------------------------------
std::vector<std::string> split (std::string str) {
	std::vector<std::string> internal;
	std::stringstream ss (str); // Turn the string into a stream.
	std::string tok;

	while (std::getline (ss, tok, ' ')) {
		internal.push_back (tok);
	}

	return internal;
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Console::Console (Game *g) :
	text ("fonts/terminus_bold.ttf", 20),
	cursor ("fonts/terminus_bold.ttf", 20),
	game (g) {
	hud = true;
	text.SetColor (Color (0, 255, 0, 255));
	cursor.SetColor (Color (0, 255, 0, 255));

	// a wee trick
	this->renderable = this;

	name = "console";
	visible = false;
	history_iterator = history.end();

	timer.Start();
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Console::Render (Window &window) {
	if (visible) {

		//
		// draw background
		//
		Primitives::fill_color = Primitives::outline_color = Color (0, 0, 0, 255);
		Primitives::Rectangle (window, 0, 0, window.GetSize().x, window.GetSize().y / 3);

		//
		// draw history
		//
		int line_height = 22;
		int y = window.GetSize().y / 3;
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
			text.SetText ("* " + *it);
			y -= line_height;
			text.SetPosition (0, y);
			text.Render (window);
		}

		//
		// draw current line
		//
		text.SetText (PREFIX + current_line);
		text.SetPosition (0, window.GetSize().y / 3 - line_height);
		text.Render (window);

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
		cursor.SetText (cursor_text);
		cursor.SetPosition (0, window.GetSize().y / 3 - line_height);
		cursor.Render (window);
	}
}

// ------------------------------------------------------------
// OnKey
// ------------------------------------------------------------
void Console::OnKey (const std::string &character) {

	if (character == "tab") {
		visible = !visible;
		return;
	}

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
			if (history_iterator != history.begin()) {
				--history_iterator;
				current_line =  *history_iterator;
			}
		}
		return;
	}

	if (character == "down") {
		if (history.size()) {
			if (history_iterator != history.end() - 1) {
				++history_iterator;
				current_line =  *history_iterator;
			}
		}
		return;
	}

	if (visible) {
		current_line += character;
	}

}

// ------------------------------------------------------------
// execute
// ------------------------------------------------------------
void Console::execute() {

	std::vector<std::string> spl = split (current_line);

	std::cout << "execute command: " << spl[0] << std::endl;

	if(spl[0] == "quit"){
		game->Call("quit");
	}

	if (spl.size() > 1) {
		std::cout << "with parameters: ";

		for (unsigned int i = 1; i < spl.size(); ++i) {
			std::cout << spl[i];
			if (i != spl.size() - 1) {
				std::cout << ", ";
			}
		}
	}

	std::cout << std::endl;
	history.push_back (current_line);
	history_iterator = history.end() ;
	current_line.clear();

	if (spl[0] == "call") {
		if (spl.size() > 1) {
			game->Call (spl[1]);
		}
	}

	if (spl[0] == "echo") {
		if (spl.size() > 1) {
			echo_list.push_back (spl[1]);
		}
	}
}

void Console::Echo (const std::vector< std::string > &texts) {
	for (auto it = texts.begin(); it != texts.end(); ++it) {
		echo_list.push_back (*it);
	}
}

}// GameLib
