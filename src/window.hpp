#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window.hpp>

#include <string>

class Window : public sf::Window {
    private:
        sf::Vector2i center;

    public:
        Window (int width, int height, const std::string &name);

        sf::Vector2i getMouseOffset (void);

};

#endif  // WINDOW_HPP