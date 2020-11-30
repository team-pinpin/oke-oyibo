#pragma once

#include <entt.hpp>

#include "core/Builder.h"
#include "core/Player.h"
#include "core/System.h"
#include "core/Terrain.h"
#include "core/Time.h"
#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/RefPtr.h"
#include "utils/Vector.h"

namespace core
{
    class Registry;

    class World: public utils::RefCounted<World>
    {
    private:
        utils::RefPtr<Registry> _registry;
        Terrain _terrain;
        entt::registry _entities;
        utils::HashMap<entt::id_type, utils::OwnPtr<System>> _systems;
        utils::Vector<core::Player> _players;

    public:
        auto &terrain() { return _terrain; }

        auto &entities() { return _entities; }

        auto &registry() { return *_registry; }

        auto &systems() { return _systems; }

        auto &players() { return _players; }

        World(utils::RefPtr<Registry> registry, int width, int height);

        void add_player(core::Player &&);

        entity::Builder create_entity();

        void update(Time &);

        void render(Camera &);
    };
} // namespace core