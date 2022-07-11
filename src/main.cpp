#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Mouse.hpp>

#ifdef unix
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif  // unix

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "player/camera.hpp"
#include "window/window.hpp"
#include "world/chunk.hpp"

#include "window/clock.hpp"
#include <iostream>
#include <vector>

void render(Window* window, Chunk chunk) {
    window->windowClear();

    chunk.use();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, chunk.getAmount());

    window->windowDisplay();

}


int main (int argc, char** argv) {

    // create window and initialize glew

    const unsigned int width = 1920;
    const unsigned int height = 1080;
    Window window (width, height, "OpenGL");

    // start camera
    Camera player(glm::vec3(0.0f, 1.8f, 0.0f));

    // compile and link shaders
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // load texture
    Texture texture("grass.jpg", GL_TEXTURE_2D);

    // load cube
    Chunk chunk;

    // mainloop
    while (window.active()) {

        window.handleEvents(&player);

        shader.setMat4("view", player.getView());
        shader.setMat4("projection", window.getProjection());

        shader.use();
        texture.use();
        render(&window, chunk);

    };

    window.setActive(false);

    return EXIT_SUCCESS;

}