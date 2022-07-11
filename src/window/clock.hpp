#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/System/Clock.hpp>


class Clock : sf::Clock {
    private:
        float _prevTime;

    public:
        
        Clock ();

        float dt ();
};

#endif  // CLOCK_HPP