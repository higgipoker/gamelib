#pragma once

#include "../graphics/renderable.h"
#include "../graphics/text.h"
#include "../game/game_entity.h"
#include "../utils/timer.h"

namespace GameLib{
class Game;
class Console : public GameEntity, public Renderable{
public:

	/**
	 * \brief construct
	 */
	Console( Game *g);

	/**
	* \brief render
	* \param window render target
	*/
	virtual void Render(Window &window) override;

	/**
	 * \brief key press
	 * \param character the char pressed
	 */
	void OnKey(const std::string &character);

	/**
	 * \brief echo something
	 * \param texts strings to echo
	 */
	void Echo(const std::vector< std::string > &texts);
private:

	// console height
	int height;

	/// text renderable
	Label text;

	/// cursor
	Label cursor;

	/// current text
	std::string current_line;

	/// command history
	std::vector<std::string> history;

	/// track current history pointer
	std::vector<std::string>::iterator history_iterator;

	/// an echo list
	std::vector<std::string> echo_list;

	/// pointer to game for function calls
	Game *game;

	/// a timer
	Timer timer;

	/**
	 * \brief render the cursor
	 */
	bool show_cursor=false;

	/**
	 * \brief execute the current command
	 */
	void execute();

};

}// GameLib
