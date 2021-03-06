/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file game.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "game.h"
#include "../utils/log.h"

#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <typeinfo>

#include <SFML/System.hpp>

#include "../utils/converter.h"

namespace GameLib {

static float accumulator = 0.0f;
static float target_frame_time = 0.0f;

// ------------------------------------------------------------
// sort predicate for renderable objects (for height)
// ------------------------------------------------------------
struct {
  bool operator()(const GameEntity *r1, const GameEntity *r2) const {
    return r1->renderable.z_order < r2->renderable.z_order;
  }
} sort_renderable;

// ------------------------------------------------------------
// constructor
// ------------------------------------------------------------
Game::Game(const std::string &gamename, unsigned int x, unsigned int y,
           unsigned int w, unsigned int h, bool fullscreen)
    : window(gamename, x, y, w, h, fullscreen), console(*this) {
  fps = 0;

  // inits static keyboard stuff
  Keyboard::Init();

  // how long one frame should take
  target_frame_time = 1.0f / static_cast<float>(Window::FPS);

  on_start();
}

// ------------------------------------------------------------
// Tick
// ------------------------------------------------------------
void Game::OnFrame() {
  gamestep_timer.Update();
  ++game_frame;

  // handle_input(event);
  // Simulate();
  render();
  calc_fps();
}

// ------------------------------------------------------------
// HandleInput
// ------------------------------------------------------------
void Game::HandleInput(WindowEvent &event) {
  window.PollEvent(event);

  switch (event.type) {
    case WINDOW_EVENT_CLOSE:
      running = false;
      break;

    case WINDOW_EVENT_MOUSE_CLICKED: {
      on_mouse_click(mouse.GetPosition().x - window.GetPosition().x,
                     mouse.GetPosition().y - window.GetPosition().y);

    } break;

    case WINDOW_EVENT_KEY_DOWN:
      console.OnKey(static_cast<keycode>(event.params.at(0)));
      break;

    case WINDOW_EVENT_MOUSE_WHEEL_MOVED:
      if (event.params.at(0) > 0) {
        camera.zoom(0.9);
      } else {
        camera.zoom(1.1);
      }
      break;

    case WINDOW_EVENT_MOUSE_MOVED:
      break;

    case WINDOW_EVENT_NONE:
      break;

    case WINDOW_EVENT_RESIZED:
      camera.OnWindowResized(event.params.at(0), event.params.at(1));
      window.OnResize(event.params.at(0), event.params.at(1));
      break;
  }
  event.Reset();
}

// ------------------------------------------------------------
// Simulate
// ------------------------------------------------------------
void Game::Simulate(float _dt) { step(_dt); }

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Game::render() {
  window.Clear();
  prepare_scene();
  for (auto entity : game_entities) {
    entity->renderable.Render(window);
  }
  prepare_hud();
  for (auto entity : hud_entities) {
    entity->renderable.Render(window);
  }
  console.Render(window);
  window.Present();
  window.SetView(camera);
  // limit_framerate();
}

// ------------------------------------------------------------
// step
// ------------------------------------------------------------
void Game::step(float dt) {
  for (auto entity : game_entities) {
    entity->Update(dt);
  }
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
// GetEntityNames
// ------------------------------------------------------------
std::vector<std::string> Game::GetEntityNames() {
  std::vector<std::string> names;
  for (auto entity : game_entities) {
    names.push_back("\"" + entity->GetName() + "\"");
  }
  std::sort(names.begin(), names.end());

  return names;
}

// ------------------------------------------------------------
// GetEntityNames
// ------------------------------------------------------------
GameEntity &Game::GetEntity(const std::string &name) {
  try {
    for (auto entity : game_entities) {
      if (entity->GetName() == name) {
        return *entity;
      }
    }
    throw "oops";
  } catch (...) {
    // fatal...
    std::cout << "Entity not found: " << name << std::endl;
  }
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Game::Call(std::vector<std::string> params) {
  if (params.size() == 0) return;

  if (params[0] == "list") {
    std::vector<std::string> texts = GetEntityNames();
    console.Echo(texts);
  }

  else if (params[0] == "fps") {
    std::vector<std::string> texts;
    texts.push_back(Converter::IntToString(static_cast<int>(fps)));
    console.Echo(texts);
  }

  else if (params[0] == "frame") {
    std::vector<std::string> texts;
    texts.push_back(Converter::IntToString(static_cast<int>(game_frame)));
    console.Echo(texts);
  }

  else if (params[0] == "quit" || params[0] == "q" || params[0] == "exit") {
    running = false;
  }

  else if (params[0] == "call") {
    if (params.size() > 1) {
      std::string entity_name = params[1];

      auto name_set = GameEntity::entity_names;

      std::vector<std::string> new_params(params.begin() + 2, params.end());

      for (auto entity : game_entities) {
        if (entity->GetName() == entity_name) {
          entity->Call(new_params);
          return;
        }
      }
      for (auto entity : hud_entities) {
        if (entity->GetName() == entity_name) {
          entity->Call(new_params);
          return;
        }
      }
      std::cout << "Entity not found: " << entity_name << std::endl;
    }
  }
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Game::Call(std::string func, std::string n, ...) {
  std::cout << "Game::Call: " << func << ", " << n << std::endl;
}

// ------------------------------------------------------------
// calc_fps
// ------------------------------------------------------------
void Game::calc_fps() {
  ++frames_this_second;
  float elapsed_time = gamestep_timer.GetFrameTime() - fps_timer;

  if (elapsed_time >= 1000) {
    fps_timer = gamestep_timer.GetFrameTime();
    fps = frames_this_second + 1;
    frames_this_second = 0;
  }
}
// ------------------------------------------------------------
// prepare_scene
// ------------------------------------------------------------
void Game::prepare_scene() {
  // sort the render list in z-order
  std::sort(game_entities.begin(), game_entities.end(), sort_renderable);
  window.SetView(camera);
}

// ------------------------------------------------------------
// prepare_hud
// ------------------------------------------------------------
void Game::prepare_hud() {
  // sort the render list in z-order
  std::sort(hud_entities.begin(), hud_entities.end(), sort_renderable);
  window.SetView(window.hud_view);
}

// ------------------------------------------------------------
// WorkingDirectory
// ------------------------------------------------------------
std::string Game::WorkingDirectory() {
  char path[128];
  getcwd(path, sizeof(path));
  return path;
}

// ------------------------------------------------------------
// limit_framerate
// ------------------------------------------------------------
void Game::limit_framerate() {
  // limit framerate
  float newnewtime = gamestep_timer.GetLiveTime();
  float gametime = gamestep_timer.GetFrameTime();
  float render_time = newnewtime - gametime;
  float target = (target_frame_time * 1000);
  while (render_time < target) {
    newnewtime = gamestep_timer.GetLiveTime();
    render_time = newnewtime - gamestep_timer.GetFrameTime();
  }
}

}  // namespace GameLib
