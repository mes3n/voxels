#include "clock.hpp"

#include <iostream>

Clock::Clock () 
: sf::Clock::Clock() {
    
    _prevTime = this->getElapsedTime().asSeconds();
}

float Clock::dt (void) {
    float dt;
    
    dt = this->getElapsedTime().asSeconds() - _prevTime;
    _prevTime = this->getElapsedTime().asSeconds();

    return dt;

}