#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Mouse.hpp>

#ifdef unix
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif  // unix

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "window.hpp"
#include "clock.hpp"

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


int main (int argc, char** argv) {

    // create window and initialize glew

    const unsigned int width = 1920;
    const unsigned int height = 1080;
    Window window (width, height, "OpenGL");

    glm::mat4 view;  // character poistion/view
    glm::mat4 projection;  // window view

    // start camera
    Camera player(glm::vec3(0.0f, 1.8f, 0.0f));

    // start clock
    Clock clock;

    // compile and link shaders
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // load texture
    Texture texture("grass.jpg", GL_TEXTURE_2D);

    // load cube
    Cube cube;

    std::vector<glm::vec3> chunk;

    for (int i = -8; i < 8; i++) {
        for (int j = -52; j < 1; j++) {
            for (int k = -8; k < 8; k++) {
                chunk.push_back(glm::vec3(1.0f * i, 1.0f * j, 1.0f * k));
            }
        }
    }


    // mainloop
    bool running = true;
    while (running) {

        float dt = clock.dt();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
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
                            running = false;
                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }
        }
        sf::Vector2i offset = window.getMouseOffset();
        if (offset.x && offset.y) {
            player.setFacing(offset.x, offset.y, dt);
        }

        if (window.hasFocus()) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player.moveForwards(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player.moveLeft(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.moveBackwards(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.moveRight(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                player.moveUp(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                player.moveDown(dt);
            }
        }

        view = player.view();

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.use();
        texture.use();
        cube.use();
        render(&window, chunk, shader);

        // std::cout << 1/dt << std::endl;

    };

    window.setActive(false);

    return EXIT_SUCCESS;

}