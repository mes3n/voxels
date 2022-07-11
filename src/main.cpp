#ifdef unix
#include <glm/vec3.hpp>
#endif  // unix

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "player/camera.hpp"
#include "window/window.hpp"
#include "world/chunk.hpp"

#include <iostream>

void render(Window* window, Chunk chunk) {
    window->windowClear();

    chunk.draw();

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

    // load chunk
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