#ifndef WINDOW_HPP
#define WINDOW_HPP

#ifdef unix
#include <glm/mat4x4.hpp>
#endif  // unix

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

#include "text.hpp"
#include "clock.hpp"
#include "../player/camera.hpp"

class Window : public sf::RenderWindow {
    private:
        bool isActive;
        Text fpsText;

        Clock clock;
        glm::mat4 projection;

        sf::Vector2i center;
        sf::Vector2i getMouseOffset (void) const;

    public:
        Window (int width, int height, const std::string &name);

        glm::mat4 getProjection (void) const;

        void handleEvents (Camera* player);
        bool active (void) const;

        void windowClear (void);
        void windowDisplay (void);

};

#endif  // WINDOW_HPP