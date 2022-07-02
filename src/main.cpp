#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Image.hpp>

// #include <SFML/OpenGL.hpp>
#ifdef unix
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif  // unix

#include "shader.hpp"
#include "texture.hpp"

#include <iostream>
#include <vector>

void render(sf::Window* window, std::vector<glm::vec3> cubePoss, Shader shader) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto pos : cubePoss) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        
        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

    }

    window->display();

}

void triangle(sf::Vector3f center, GLuint vbo) {

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        0
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main (int argc, char** argv) {

    // create window and initialize glew

    sf::ContextSettings context(24, 8, 2, 4, 6);
    context.antialiasingLevel = 8;
    context.majorVersion = 4;
    context.minorVersion = 6;
    sf::Window window(sf::VideoMode(900, 900, 32), "OpenGL", sf::Style::Default, context);
    window.setActive(true);
    glewInit();

    glEnable(GL_DEPTH_TEST);

    glm::mat4 view = glm::mat4(1.0f);  // character position
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -15.0f));

    glm::mat4 projection;  // characte view

    // compile and link shaders
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // load texture
    Texture texture("grass.jpg", GL_TEXTURE_2D);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    // create triangle
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    triangle(sf::Vector3f(0.f, 0.f, 0.f), vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    std::vector<glm::vec3> cubePoss;

    for (int i = -5; i < 6; i++) {
        for (int j = -5; j < 6; j++) {
            if (!(i == 4 && j == 3) && !(i == -3 && j == 4) && !(j == -4))
                cubePoss.push_back(glm::vec3(1.0f * i, 1.0f * j, 0.0f));
        }
    }

    // mainloop
    bool running = true;
    while (running) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;

                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    projection = glm::perspective(
                        glm::radians(45.f), (GLfloat)event.size.width/(GLfloat)event.size.height, 0.1f, 100.f
                    );

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
        
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.use();
        texture.use();
        glBindVertexArray(vao);
        render(&window, cubePoss, shader);

    };

    window.setActive(false);

    return EXIT_SUCCESS;

}