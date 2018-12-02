// ImGui GLFW binding with OpenGL3 + shaders
// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include <imgui.h>

struct GLFWwindow;

namespace aie {

bool        ImGui_Init(GLFWwindow* window, bool install_callbacks);
void        ImGui_Shutdown();
void        ImGui_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
void        ImGui_InvalidateDeviceObjects();
bool        ImGui_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
void        ImGui_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void        ImGui_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void        ImGui_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void        ImGui_CharCallback(GLFWwindow* window, unsigned int c);

} // namespace aie