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
// destructor
// ------------------------------------------------------------
Game::~Game() {
}

// ------------------------------------------------------------
// with thanks to Glenn Fielder (https://gafferongames.com/post/fix_your_timestep/)
// ------------------------------------------------------------
void Game::Simulate() {
    sf::Time newTime = gameclock.getElapsedTime();
    float frameTime = newTime.asSeconds() - currentTime.asSeconds();
    if (frameTime > Window::FPS)
        frameTime = Window::FPS;
    currentTime = newTime;
    accumulator += frameTime;

    int times = 0;
    while (accumulator >= dt) {
        step(dt);
        accumulator -= dt;
        ++times;
    }
    std::cout << times << std::endl;
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
    if (params.size() == 0)
        return;

    if (params[0] == "list") {
        std::vector<std::string> texts = GetEntityNames();
        console.Echo(texts);
    }

    else if (params[0] == "fps") {
        std::vector<std::string> texts;
        texts.push_back(Converter::IntToString((int)fps));
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
}

} // GameLib
