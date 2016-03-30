#include <window/window.h>
#include <window/constants.h>

#include <log/log.h>

namespace window {
    bool GLFWWindow::errored = false;

    void GLFWWindow::error_callback(int error, const char *description) {
        LOG_ERR("GLFW error: ", description);
        GLFWWindow::errored = true;
    }

    void GLFWWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        // do nothing for now
    }

    void GLFWWindow::char_callback(GLFWwindow *window, unsigned int codepoint) {
        // do nothing for now
    }

    GLFWWindow::GLFWWindow() : window(nullptr) {
        // initialize GLFW
        glfwSetErrorCallback(GLFWWindow::error_callback);
        if (!glfwInit()) {
            throw WindowCreationError("Failed to initialize GLFW");
        }
        // set up window
        window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE, NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw WindowCreationError("Failed to create window");
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, GLFWWindow::key_callback);
        glfwSetCharCallback(window, GLFWWindow::char_callback);
        // initialize GLEW
        ::glewExperimental = true;
        if (auto error = glewInit() ^ GLEW_OK) {
            glfwDestroyWindow(window);
            glfwTerminate();
            throw WindowCreationError(std::string("Failed to initialize GLEW: ") + reinterpret_cast<const char *>(glewGetErrorString(error ^ GLEW_OK)));
        }
    }
}
