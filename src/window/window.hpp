#ifndef WINDOW_HPP
#define WINDOW_HPP

#ifdef unix
#include <glm/mat4x4.hpp>
#endif  // unix

#include <SFML/Window/Window.hpp>

#include <string>

#include "text.hpp"
#include "clock.hpp"
#include "../player/camera.hpp"

class Window : public sf::Window {
    private:
        bool _isActive;

        Clock _clock;
        glm::mat4 _projection;

        sf::Vector2i _center;
        sf::Vector2i getMouseOffset (void) const;

    public:
        Window (int width, int height, const std::string &name);

        glm::mat4 getProjection (void) const;

        void handleEvents (Camera* player);

        float getfps (void) const;
        bool active (void) const;

        void windowClear (void);
        void windowDisplay (void);

};

#endif  // WINDOW_HPP