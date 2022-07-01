#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

// #include <SFML/OpenGL.hpp>
#ifdef unix
#include <GL/glew.h>
#endif  // unix

#include "shaders/shader.hpp"

#include <iostream>

void render(sf::Window* window) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glDrawArrays(GL_TRIANGLES, 0, 9);


    window->display();

}

void triangle(sf::Vector3f center, GLuint vbo) {
    GLfloat vertices[] = {
        center.x - 0.5f, center.y - 0.5f, center.z + 0.0f,
        center.x + 0.5f, center.y - 0.5f, center.z + 0.0f,
        center.x + 0.0f, center.y + 0.5f, center.z + 0.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main (int argc, char** argv) {

    sf::Window window(sf::VideoMode(900, 900), "OpenGL", sf::Style::Default);
    glewInit();

    GLuint shaderProgram = glCreateProgram();
    loadShader("shaders/basic.vert", GL_VERTEX_SHADER, shaderProgram);
    loadShader("shaders/basic.frag", GL_FRAGMENT_SHADER, shaderProgram);
    glLinkProgram(shaderProgram);
    
    window.setActive(true);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    triangle(sf::Vector3f(0.f, 0.f, 0.f), vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    bool running = true;
    while (running) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                running = false;

                case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);

                case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                    running = false;

                    default:
                    break;
                }

                default:
                break;
            }
        }
        
        render(&window);

    };

    window.setActive(false);

    return 0;

}