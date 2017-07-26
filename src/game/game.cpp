#include "game.h"

#include "../utils/converter.h"
#include <iostream>
#include <typeinfo>

namespace GameLib {

// ------------------------------------------------------------
// sort predicate for renderable objects (for height)
// ------------------------------------------------------------
struct {
  bool operator()(const GameEntity *r1, const GameEntity *r2) const {
	if (r1->renderable && r2->renderable) {
	  return r1->renderable->z_order < r2->renderable->z_order;
	}
	return false;
  }
} sort_renderable;

// ------------------------------------------------------------
// calc_fps
// ------------------------------------------------------------
void Game::calc_fps() {
  float currentTime = fps_clock.getElapsedTime().asSeconds();
  fps = 1.f / (currentTime - lastTime);
  lastTime = currentTime;
}

// ------------------------------------------------------------
// constructor
// ------------------------------------------------------------
Game::Game(const std::string &gamename, int x, int y, int w, int h,
		   bool fullscreen)
	: window(gamename, x, y, w, h, fullscreen), console(this) {
  AddEntity(camera);
  AddEntity(console);
  fps = 0;
}

// ------------------------------------------------------------
// destructor
// ------------------------------------------------------------
Game::~Game() {}

// ------------------------------------------------------------
// Loop
// ------------------------------------------------------------
void Game::Loop(float dt) {
  handle_keyboard();
  physics(dt);
  render();
  calc_fps();
}

// ------------------------------------------------------------
// AddEntity
// ------------------------------------------------------------
void Game::AddEntity(GameEntity &entity) {

  // hud entities go in a different list
  if (entity.hud) {
	hud_entities.push_back(&entity);
  } else {
	game_entities.push_back(&entity);
  }
}

// ------------------------------------------------------------
// render
// ------------------------------------------------------------
void Game::render() {

  // clear
  window.Clear();

  // sort the render list in z-order
  std::sort(game_entities.begin(), game_entities.end(), sort_renderable);

  // set camera
  window.SetView(camera.view);

  // render all game graphics
  for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
	if ((*it)->renderable) {
	  (*it)->renderable->Render(window);
	}
  }

  // non moving view for the hud
  window.SetView(hud_view);

  // render hud graphics
  for (auto it = hud_entities.begin(); it != hud_entities.end(); ++it) {
	if ((*it)->renderable) {
	  (*it)->renderable->Render(window);
	}
  }

  // present
  window.Present();
}

// ------------------------------------------------------------
// physics
// ------------------------------------------------------------
void Game::physics(float dt) {
  for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
	(*it)->Update(dt);
  }
}

// ------------------------------------------------------------
// handle_keyboard
// ------------------------------------------------------------
void Game::handle_keyboard() {
  // check inputs
  WindowEvent event = window.PollEvent();

  switch (event.type) {
  case WINDOW_EVENT_CLOSE:
	running = false;
	break;

  default:
  case WINDOW_EVENT_NONE:
	break;

  case WINDOW_EVENT_MOUSE_CLICKED: {
	sf::Vector2i position = sf::Mouse::getPosition();
	std::cout << position.x - window.GetPosition().x - 4 << ", "
			  << position.y - window.GetPosition().y - 24 << std::endl;
  } break;
  case WINDOW_EVENT_KEY_DOWN:
	console.OnKey(event.param);
	break;

  case WINDOW_EVENT_MOUSE_WHEEL_MOVED:
	float z = std::stof(event.param);
	if (z > 0) {
	  camera.ZoomIn();
	} else {
	  camera.ZoomOut();
	}
	break;
  }
}

// ------------------------------------------------------------
// GetEntityNames
// ------------------------------------------------------------
std::vector<std::string> Game::GetEntityNames() {
  std::vector<std::string> names;
  for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
	names.push_back((*it)->GetName() + " [" + typeid(*it).name() + "]");
  }
  std::sort(names.begin(), names.end());

  return names;
}

// ------------------------------------------------------------
// GetEntityNames
// ------------------------------------------------------------
GameEntity *Game::GetEntity(const std::string &name) {

  GameEntity *entity = nullptr;

  for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
	if ((*it)->GetName() == name) {
	  return *it;
	}
  }
  std::cout << "Entity not found: " << name << std::endl;

  return entity;
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Game::Call(std::vector<std::string> params) {

  if (params.size()) {

	if (params[0] == "list") {
	  std::vector<std::string> texts = GetEntityNames();
	  console.Echo(texts);
	}

	else if (params[0] == "fps") {
	  std::vector<std::string> texts;
	  texts.push_back(IntToString((int)fps));
	  console.Echo(texts);
	}

	else if (params[0] == "quit") {
	  running = false;
	}

	else if (params[0] == "call") {
	  if (params.size() > 1) {
		std::string entity_name = params[1];

		auto name_set = GameEntity::entity_names;

		std::vector<std::string> new_params(params.begin() + 2, params.end());

		for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
		  if ((*it)->GetName() == entity_name) {
			(*it)->Call(new_params);
			return;
		  }
		}
		std::cout << "Entity not found: " << entity_name << std::endl;
	  }
	}
  }
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Game::Call(std::string func, std::string n, ...) {}

} // GameLib
