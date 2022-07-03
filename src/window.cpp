#include "window.hpp"

#ifdef unix
#include <GL/glew.h>
#endif  // unix

sf::ContextSettings createContext (void) {
    sf::ContextSettings context;

    context.depthBits = 24;
    context.antialiasingLevel = 8;
    context.majorVersion = 4;
    context.minorVersion = 6;

    return context;
}

Window::Window (int width, int height, const std::string &name) 
: sf::Window (sf::VideoMode(width, height, 32), name, sf::Style::Close, createContext()) {

    this->setActive(true);
    this->setMouseCursorVisible(false);
    this->setFramerateLimit(30);

    this->setPosition(sf::Vector2i(1681, 0));

    center = sf::Vector2i(1920*0.5, 1080*0.5);
    sf::Mouse::setPosition(center);

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glViewport(0, 0, width, height);

}

sf::Vector2i Window::getMouseOffset (void) {
    if (this->hasFocus()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this);

        sf::Mouse::setPosition(center, *this);
        return sf::Vector2i(center.x - mousePos.x, center.y - mousePos.y);
    }
    else {
        return sf::Vector2i(0, 0);
    }
}