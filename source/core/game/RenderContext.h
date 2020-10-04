#pragma once

#include <imgui.h>

#include "core/render/Target.h"

namespace core::game
{
    class RenderContext
    {
    private:
        int _width = 0;
        int _height = 0;

        render::Target _terrain{};
        render::Target _shadows{};
        render::Target _light{};
        render::Target _entities{};
        render::Target _overlay{};

        render::Target _composite{};

    public:
        int width() { return _width; }
        int height() { return _height; }

        render::Target &terrain() { return _terrain; }
        render::Target &shadows() { return _shadows; }
        render::Target &light() { return _light; }
        render::Target &entities() { return _entities; }
        render::Target &overlay() { return _overlay; }
        render::Target &composite() { return _composite; }

        RenderContext()
        {
            _width = GetScreenWidth();
            _height = GetScreenHeight();
        }

        template <typename TCallback>
        void use_and_do(TCallback callback)
        {
            callback();
        }

        void resize_to_fit(int width, int height)
        {
            _terrain.resize_to_fit(width, height);
            _shadows.resize_to_fit(width, height);
            _light.resize_to_fit(width, height);
            _entities.resize_to_fit(width, height);
            _overlay.resize_to_fit(width, height);
            _composite.resize_to_fit(width, height);

            _width = width;
            _height = height;
        }

        void resize_to_fit_the_screen()
        {
            resize_to_fit(GetScreenWidth(), GetScreenHeight());
        }

        void clear()
        {
            _terrain.use_and_do([]() {
                ClearBackground(BLACK);
            });

            _shadows.use_and_do([]() {
                ClearBackground({});
            });

            _entities.use_and_do([]() {
                ClearBackground({});
            });

            _overlay.use_and_do([]() {
                ClearBackground({});
            });
        }

        void compose()
        {
            composite().use_and_do([&]() {
                Rectangle rect{0, 0, (float)width(), (float)height()};
                DrawTexturePro(terrain().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(shadows().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(entities().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(light().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(overlay().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            });
        }

        void display()
        {
            ImGui::Begin("Render Context");

            ImGui::Text("Terrain Map");
            _terrain.display(1 / 8.0);
            ImGui::Separator();

            ImGui::Text("Shadow Map");
            _shadows.display(1 / 8.0);
            ImGui::Separator();

            ImGui::Text("Light Map");
            _light.display(1 / 8.0);
            ImGui::Separator();

            ImGui::Text("Entities Map");
            _entities.display(1 / 8.0);
            ImGui::Separator();

            ImGui::Text("Overlay Map");
            _overlay.display(1 / 8.0);
            ImGui::Separator();

            ImGui::Text("Final Result");
            _composite.display(1 / 8.0);
            ImGui::Separator();

            ImGui::End();
        }
    };
} // namespace core::game