// Link statically with GLEW
#define GLEW_STATIC

// Headers
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

void createCube(GLuint* vbo, float x, float y, float z) {

    GLfloat vertices[] = {
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + -0.5f, y + -0.5f, z +  0.5f,
        x + -0.5f, y + 0.5f, z +  0.5f,
        x + 0.5f,  y + 0.5f, z + -0.5f,
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + -0.5f, y + 0.5f, z + -0.5f,
        x + 0.5f,  y + -0.5f, z +  0.5f,
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + 0.5f,  y + -0.5f, z + -0.5f,
        x + 0.5f,  y +  0.5f, z + -0.5f,
        x + 0.5f,  y + -0.5f, z + -0.5f,
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + -0.5f, y +  0.5f, z +  0.5f,
        x + -0.5f, y +  0.5f, z + -0.5f,
        x + 0.5f,  y + -0.5f, z +  0.5f,
        x + -0.5f, y + -0.5f, z +  0.5f,
        x + -0.5f, y + -0.5f, z + -0.5f,
        x + -0.5f, y +  0.5f,  z + 0.5f,
        x + -0.5f, y + -0.5f,  z + 0.5f,
        x + 0.5f,  y + -0.5f,  z + 0.5f,
        x + 0.5f,  y +  0.5f, z +  0.5f,
        x + 0.5f,  y + -0.5f, z + -0.5f,
        x + 0.5f,  y +  0.5f, z + -0.5f,
        x + 0.5f,  y + -0.5f, z + -0.5f,
        x + 0.5f,  y +  0.5f, z +  0.5f,
        x + 0.5f,  y + -0.5f, z +  0.5f,
        x + 0.5f,  y + 0.5f,  z + 0.5f,
        x + 0.5f,  y + 0.5f, z + -0.5f,
        x + -0.5f, y + 0.5f, z + -0.5f,
        x + 0.5f,  y + 0.5f, z +  0.5f,
        x + -0.5f, y +  0.5f, z + -0.5f,
        x + -0.5f, y +  0.5f, z +  0.5f,
        x + 0.5f,  y + 0.5f,  z + 0.5f,
        x + -0.5f, y + 0.5f,  z + 0.5f,
        x + 0.5f,  y + -0.5f,  z + 0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 6;

    sf::Window window(sf::VideoMode(900, 900, 32), "OpenGL", sf::Style::Default, settings);

    // Initialize GLEW
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    createCube(&vbo, 0.5, 0, 0);
    createCube(&vbo, -0.5, 0, 0);

    for (int i; i < 2; i++) {
        // Create a Vertex Buffer Object and copy the vertex data to it

    }

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        running = false;
                        break;
                }
                break;
            }
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 2*12*3);

        // Swap buffers
        window.display();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    window.close();

    return 0;
}
