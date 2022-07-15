#ifdef unix
#include <glm/vec3.hpp>
#endif  // unix

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "player/camera.hpp"
#include "window/window.hpp"
#include "world/chunk.hpp"

#include "world/skybox.hpp"

#include "print_info.hpp"


void render(Window &window, const Chunk &chunk, const Skybox &skybox) {
    window.windowClear();

    skybox.draw();
    chunk.draw();

    window.windowDisplay();

}


int main (int argc, char** argv) {

    // create window and initialize glew

    const unsigned int width = 1920;
    const unsigned int height = 1080;
    Window window (width, height, "OpenGL");

    // start camera
    Camera player(glm::vec3(0.0f, 1.8f, 0.0f));

    // compile and link shaders
    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");

    // load texture
    Texture texture("assets/blocks/grass.jpg");

    // load chunk
    Chunk chunk(&basicShader, &texture);
    Skybox skybox("shaders/skybox.vert", "shaders/skybox.frag", "assets/skybox/");

    // mainloop
    while (window.active()) {

        window.handleEvents(&player);

        basicShader.use();
        basicShader.setMat4("view", player.getView());
        basicShader.setMat4("projection", window.getProjection());

        skybox.update(player.getView(), window.getProjection());

        render(window, chunk, skybox);

        print_info(player.getPosition(), window.getfps());

    };

    window.setActive(false);

    return EXIT_SUCCESS;

}