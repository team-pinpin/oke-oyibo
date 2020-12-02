#include "game/scene/InGame.h"

#include "core/Keyboard.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "base/components/LightSource.h"
#include "base/components/Player.h"
#include "base/components/Sprite.h"
#include "game/components/Hunger.h"
#include "game/components/Thirst.h"
#include "game/components/Stamina.h"
#include "game/Generator.h"
#include "game/components/Pickable.h"
#include "game/components/Inventory.h"
#include "game/inventory/Stack.h"
#include "game/inventory/Item.h"

namespace game
{

    InGame::InGame(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg)
    {
    }

    InGame::~InGame()
    {
    }

    void InGame::on_switch_in()
    {
        auto world = utils::make<core::World>(registry(), 256, 256);

        world->add_player({"bob", utils::own<core::Keyboard>()});
        world->players()[0].camera().zoom_in();
        world->players()[0].camera().speed(10);

        world->create_entity()
            .with<base::Position>(64.0f, 64.0f, 0.0f)
            .with<base::Acceleration>()
            .with<base::Velocity>()
            .with<base::LightSource>(128.0f, WHITE)
            .with<game::Health>(10, 10)
            .with<game::Hunger>(20.0f, 20.0f)
            .with<game::Thirst>(20.0f, 20.0f)
            .with<base::Player>(0)
            .with<base::Sprite>(registry().texture("character"))
            .with<game::Stamina>(20.0f, 20.0f)
            .with<game::Inventory>();


        Stack stack(Item("Mon_Item", core::Texture()), 12);
        world->create_entity()
            .with<game::Pickable>(stack)
            .with<base::Position>(60.0f,60.0f,0.0f)
            .with<base::LightSource>(50.0f, WHITE)
            .with<base::Sprite>(registry().texture("table"));

        _editor = utils::own<editor::Editor>(world);
        _editor->open<editor::Entities>();
        _editor->open<editor::Inspector>();
        _editor->open<editor::Profiler>();
        _editor->open<editor::Systems>();
        _editor->open<editor::Viewport>();

        _game = utils::own<game::Game>(world);

        game::Generator gen;
        gen.generate_enemy(*world, registry());
        gen.generate_food(*world,registry());
    }

    void InGame::on_switch_out()
    {
    }

    void InGame::update(core::Time &time)
    {
        if (IsKeyPressed(KEY_F3))
        {
            _debugging = !_debugging;
        }

        if (_debugging)
        {
            _editor->update(time);
        }
        else
        {
            _game->update(time);
        }
    }

    void InGame::render()
    {
        if (_debugging)
        {
            _editor->render();
            _editor->display();
        }
        else
        {
            _game->render();
        }
    }

} // namespace game
