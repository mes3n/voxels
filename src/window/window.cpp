#include "window.hpp"

#ifdef unix
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#endif  // unix

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

sf::ContextSettings createContext (void) {
    sf::ContextSettings context;

    context.depthBits = 24;
    context.antialiasingLevel = 8;
    context.majorVersion = 4;
    context.minorVersion = 6;

    return context;
}

Window::Window (int width, int height, const std::string &name) 
: sf::RenderWindow (sf::VideoMode(width, height, 32), name, sf::Style::Close, createContext())
, fpsText("fonts/basic-regular.ttf") {


    this->setActive(true);
    isActive = true;
    this->setMouseCursorVisible(false);
    this->setFramerateLimit(120);

    setPosition(sf::Vector2i(1681, 0));

    center = sf::Vector2i(1920*0.5, 1080*0.5);
    sf::Mouse::setPosition(center);

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    // glFrontFace(GL_CW);

    glViewport(0, 0, width, height);
    projection = glm::perspective(
        glm::radians(45.0f), (GLfloat)width/(GLfloat)height, 0.1f, 100.f
    );
}

glm::mat4 Window::getProjection (void) const {
    return projection;
}

sf::Vector2i Window::getMouseOffset (void) const {
    if (this->hasFocus()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this);

        sf::Mouse::setPosition(center, *this);
        return sf::Vector2i(center.x - mousePos.x, center.y - mousePos.y);

    }
    else {
        return sf::Vector2i(0, 0);
    }
}

void Window::windowClear (void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // some fancy color
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Window::windowDisplay (void) {
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);
    // glBindVertexArray(0);
    // this->pushGLStates();
    // this->draw(fpsText.getText());
    // this->popGLStates();
    this->display();

}

void Window::handleEvents (Camera* player) {
    float dt = clock.dt();
    
    sf::Event event;
    while (this->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                isActive = false;
                break;

            case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                projection = glm::perspective(
                    glm::radians(45.0f), (GLfloat)event.size.width/(GLfloat)event.size.height, 0.1f, 100.f
                );
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        isActive = false;
                        break;

                    default:
                        break;
                }

            default:
                break;
        }
    }
    if (this->hasFocus()) {

        sf::Vector2i offset = this->getMouseOffset();
        if (offset.x && offset.y) {
            player->setFacing(offset.x, offset.y, dt);
        }

        float vx = 0.0f;
        float vy = 0.0f;
        float vz = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            vx += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            vz -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            vx -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            vz += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            vy += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            vy -= 1.0f;
        }
        player->move(vx, vy, vz, dt);
    }
    fpsText.setTextFromFloat((float)1.0f/dt);
}

bool Window::active (void) const {
    return isActive;
}
