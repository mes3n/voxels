#include "clock.hpp"

Clock::Clock () 
: sf::Clock::Clock() {
    
    _prevTime = this->getElapsedTime().asSeconds();
}

float Clock::dt (void) {
    float dt;
    
    dt = this->getElapsedTime().asSeconds() - _prevTime;
    _prevTime = this->getElapsedTime().asSeconds();

    _fps = (float)1.0f/dt;

    return dt;

}

float Clock::getfps (void) const {
    return _fps;
}