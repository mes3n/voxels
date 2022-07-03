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

    sf::ContextSettings context;
    context.depthBits = 24;
    context.antialiasingLevel = 8;
    context.majorVersion = 4;
    context.minorVersion = 6;
    sf::Window window(sf::VideoMode(900, 900, 32), "OpenGL", sf::Style::Default, context);
    window.setActive(true);
    window.setMouseCursorVisible(false);
    sf::Vector2i windowCenter = sf::Vector2i(450, 450);
    glewInit();

    glEnable(GL_DEPTH_TEST);

    glm::mat4 view;  // character poistion/view

    glm::mat4 projection;  // window view

    // start camera
    Camera player(glm::vec3(0.0f, 0.0f, -15.0f));

    // compile and link shaders
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // load texture
    Texture texture("grass.jpg", GL_TEXTURE_2D);

    // load cube
    Cube cube;

    std::vector<glm::vec3> cubePoss;

    for (int i = -50; i < 50; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = -50; k < 50; k++) {
                cubePoss.push_back(glm::vec3(1.0f * i, 1.0f * j, 1.0f * k));
            }
        }
    }

    bool firstMouse = true;
    sf::Vector2i mousePrev = sf::Vector2i(-1, -1);

    // mainloop
    bool running = true;
    while (running) {


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

                // case sf::Event::MouseMoved:
                //     if (firstMouse) {
                //         mousePrevX = event.mouseMove.x;
                //         mousePrevY = event.mouseMove.y;
                //         firstMouse = false;
                //     }
                //     std::cout << event.mouseMove.x - mousePrevX << ", " << event.mouseMove.y - mousePrevY << std::endl;
                //     player.setFacing((float)(event.mouseMove.x - mousePrevX), (float)(event.mouseMove.y - mousePrevY));
                //     view = player.view();
                //     mousePrevX = event.mouseMove.x;
                //     mousePrevY = event.mouseMove.y;
                    
                //     break;

                default:
                    break;
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x != windowCenter.x && mousePos.y != windowCenter.y) {
            if (firstMouse) {
                firstMouse = false;
            }
            player.setFacing(windowCenter.x - mousePos.x, windowCenter.y - mousePos.y);
            sf::Mouse::setPosition(windowCenter, window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.moveForwards(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.moveLeft(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.moveBackwards(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.moveRight(1.0f);
        }

        view = player.view();

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.use();
        texture.use();
        cube.use();
        render(&window, cubePoss, shader);

    };

    window.setActive(false);

    return EXIT_SUCCESS;

}