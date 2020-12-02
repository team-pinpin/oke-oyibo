#include "game/Generator.h"

#include "base/components/LightSource.h"
#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"

#include "core/Camera.h"
#include "core/Registry.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "game/components/Enemy.h"
#include "game/components/Pickable.h"
#include "game/systems/EnemyMove.h"

namespace game
{
    Generator::Generator()
    {
    }

    Generator::~Generator()
    {
    }

    //generate enemy sprite list
    void Generator::create_enemy_sprite()
    {
        this->enemy_sprites.push_back("zombie");
        this->enemy_sprites.push_back("big-slime");
        this->enemy_sprites.push_back("skeleton");
        this->enemy_sprites.push_back("slime");
        this->enemy_sprites.push_back("wisp");
    }

    //generate enemy on the map
    void Generator::generate_enemy(core::World &world, core::Registry &reg)
    {
        create_enemy_sprite();
        for (int i = 0; i < 100; i++)
        {
            for (string enemy : enemy_sprites)
            {
                //random positions
                this->randomX = rand() % world.terrain().bound().width();
                this->randomY = rand() % world.terrain().bound().height();

                //generate enemy entity in the world
                world.create_entity()
                    .with<game::Enemy>()
                    .with<game::EnemyMove>()
                    .with<base::Position>(randomX, randomY, 0.0f)
                    .with<base::Acceleration>()
                    .with<base::Velocity>()
                    .with<game::Health>(10, 10)
                    .with<base::Sprite>(reg.texture(enemy));
            }
        }
    }

    //generate food sprite list
    void Generator::create_food_sprite()
    {
        this->food_sprites.push_back("food");
        this->food_sprites.push_back("water");
    }

    //generate food on the map
    void Generator::generate_food(core::World &world, core::Registry &reg)
    {
        create_food_sprite();
        for (int i = 0; i < 100; i++)
        {
            for (string food : food_sprites)
            {
                //Set random positions
                this->randomX = rand() % world.terrain().bound().width();
                this->randomY = rand() % world.terrain().bound().height();

                Stack stack(Item("Item " + food, core::Texture()), 12);
                //generate item entity
                world.create_entity()
                    .with<game::Pickable>(stack)
                    .with<base::Position>(randomX, randomY, 0.0f)
                    .with<base::LightSource>(30.0f, WHITE)
                    .with<base::Sprite>(reg.texture(food));
            }
        }
    }

    //generate the world
    void Generator::generate_world()
    {
    }

} // namespace game
