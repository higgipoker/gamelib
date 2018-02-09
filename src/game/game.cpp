/****************************************************************************
 * Copyright (C) 2018 by Paul Higgins
 *
 * This file is part of GameLib.
 *
 *   Box is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Box is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with GameLib. If not, see <http://www.gnu.org/licenses/>
 ****************************************************************************/
/**
 * @file game.cpp
 * @author Paul Higgins
 * @date 2018
 * @brief game implementation file
 */

#include "game.h"

#include <assert.h>
#include <iostream>
#include <typeinfo>

#include <SFML/System.hpp>

#include "../utils/converter.h"

namespace GameLib {

static sf::Clock gameclock;
static sf::Time currentTime;
static float dt = 0.001f;
static float accumulator = 0.0f;

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
// constructor
// ------------------------------------------------------------
Game::Game(const std::string &gamename, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullscreen)
    : window(gamename, x, y, w, h, fullscreen), console(this) {
    AddEntity(camera);
    AddEntity(console);
    fps = 0;
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

        case WINDOW_EVENT_MOUSE_CLICKED:
            on_mouse_click(sf::Mouse::getPosition().x - window.GetPosition().x, sf::Mouse::getPosition().y - window.GetPosition().y);
            break;

        case WINDOW_EVENT_KEY_DOWN:
            console.OnKey(event.param);
            break;

        case WINDOW_EVENT_MOUSE_WHEEL_MOVED:
            if (std::stof(event.param) > 0) {
                camera.ZoomIn();
            } else {
                camera.ZoomOut();
            }
            break;

        case WINDOW_EVENT_MOUSE_MOVED:
            break;

        case WINDOW_EVENT_NONE:
            break;
    }
}

// ------------------------------------------------------------
// with thanks to Glenn Fielder (https://gafferongames.com/post/fix_your_timestep/)
// ------------------------------------------------------------
void Game::Simulate() {
    sf::Time newTime = gameclock.getElapsedTime();
    float frameTime = newTime.asSeconds() - currentTime.asSeconds();

    if (frameTime > Window::FPS) {
        frameTime = Window::FPS;
    }

    currentTime = newTime;
    accumulator += frameTime;

    int times = 0;
    while (accumulator >= dt) {
        step(dt);
        accumulator -= dt;
        ++times;
    }

    // std::cout << times << " sim steps per frame" << std::endl;
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Game::Render() {

    // clear
    window.Clear();

    // sort the render list in z-order
    std::sort(game_entities.begin(), game_entities.end(), sort_renderable);
    std::sort(hud_entities.begin(), hud_entities.end(), sort_renderable);

    // set camera view
    window.SetView(camera.GetView());

    // render all game graphics
    for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
        (*it)->renderable->Render(window);
    }

    // non moving view for the hud
    render_hud();

    // flip buffers
    window.Present();
}

// ------------------------------------------------------------
// render_hud
// ------------------------------------------------------------
void Game::render_hud() {
    // hud view dimensions should match main camera view
    hud_view.setSize(camera.GetView().getSize());
    hud_view.setCenter(sf::Vector2f(hud_view.getSize().x / 2, hud_view.getSize().y / 2));

    // activate hud view for rendering
    window.SetView(hud_view);

    // render hud graphics
    for (auto it = hud_entities.begin(); it != hud_entities.end(); ++it) {
        (*it)->renderable->Render(window);
    }
}

// ------------------------------------------------------------
// step
// ------------------------------------------------------------
void Game::step(float dt) {
    for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
        (*it)->Update(dt);
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
    for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
        names.push_back("\"" + (*it)->GetName() + "\"");
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
    if (params.size() == 0)
        return;

    if (params[0] == "list") {
        std::vector<std::string> texts = GetEntityNames();
        console.Echo(texts);
    }

    else if (params[0] == "fps") {
        std::vector<std::string> texts;
        texts.push_back(Converter::IntToString(static_cast<int>(fps)));
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

            for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
                if ((*it)->GetName() == entity_name) {
                    (*it)->Call(new_params);
                    return;
                }
            }
            for (auto it = hud_entities.begin(); it != hud_entities.end(); ++it) {
                if ((*it)->GetName() == entity_name) {
                    (*it)->Call(new_params);
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

} // GameLib
