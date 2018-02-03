#pragma once
#include <SFML/System.hpp>
namespace GameLib {

class Timer {
public:
    void Start() {
        clock.restart();
    }

    float GetTicks() {
        return clock.getElapsedTime().asMilliseconds();
    }

protected:
    sf::Clock clock;
};

}// GameLib
