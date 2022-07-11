#include "clock.hpp"

#include <iostream>

Clock::Clock () 
: sf::Clock::Clock() {
    
    prevTime = this->getElapsedTime().asSeconds();
}

float Clock::dt (void) {
    float dt;
    
    dt = this->getElapsedTime().asSeconds() - prevTime;
    prevTime = this->getElapsedTime().asSeconds();

    return dt;

}