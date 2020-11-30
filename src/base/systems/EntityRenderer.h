#pragma once

#include <raylib.h>

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/System.h"
#include "core/World.h"

#include "base/components/Position.h"
#include "base/components/Sprite.h"

namespace base
{
    class EntityRenderer: public core::System
    {
    private:
    public:
        EntityRenderer()
        {
        }

        void render(core::World &world, core::Camera &camera) override
        {
            auto view = world.entities().view<Position, Sprite>();

            camera.with_entities([&]() {
                view.each([&](auto &position, auto &sprite) {
                    auto tex = sprite.texture;

                    auto destination = tex.bound().moved(position.pos2d() - tex.bound().bottom_center());

                    core::draw_texture(tex, destination, WHITE);
                });
            });
        }
    };
} // namespace base