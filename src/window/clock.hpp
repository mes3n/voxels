#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/System/Clock.hpp>

class Clock : sf::Clock {
    private:
        float _prevTime;
        float _fps;

    public:
        
        Clock ();

        float dt (void);
        float getfps (void) const;
};

#endif  // CLOCK_HPP