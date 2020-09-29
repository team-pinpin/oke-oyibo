#include <imgui.h>
#include <raylib.h>

#include "glue/Glue.h"

int main(void)
{
    glue::initialize();

    while (!glue::should_exit())
    {
        glue::begin_frame();

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        ImGui::End();

        ImGui::Begin("The world is mine");
        ImGui::Text("Lol this is too easy!");
        ImGui::End();

        glue::end_frame();
    }

    glue::uninitialize();

    return 0;
}