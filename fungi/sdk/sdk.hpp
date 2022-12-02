#pragma once
#include "game/c_player.hpp"
#include "game/c_world.hpp"
#include "game/c_item.hpp"
#include "game/c_loot_item.hpp"

namespace sdk
{
	inline c_player* local_player;
	inline c_world* game_world;
	inline unity::c_camera* camera;
}