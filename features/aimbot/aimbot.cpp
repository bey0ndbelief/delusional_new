#include "aimbot.hpp"
#include "../../sdk/math/math.hpp"
#include "../../menu/config/config.hpp"

int hitbox;
int aimbot_fov;
int autowall_dmg;
bool autowall_b = true;
bool is_knife(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_KNIFE, WEAPON_KNIFEGG, WEAPON_KNIFE_BUTTERFLY, WEAPON_KNIFE_FALCHION, WEAPON_KNIFE_FLIP, WEAPON_KNIFE_GHOST, WEAPON_KNIFE_GUT, WEAPON_KNIFE_GYPSY_JACKKNIFE, WEAPON_KNIFE_KARAMBIT, WEAPON_KNIFE_M9_BAYONET, WEAPON_KNIFE_PUSH, WEAPON_KNIFE_STILETTO, WEAPON_KNIFE_T, WEAPON_KNIFE_TACTICAL, WEAPON_KNIFE_URSUS, WEAPON_KNIFE_WIDOWMAKER, WEAPON_KNIFEGG };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_grenade(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_FRAG_GRENADE, WEAPON_HEGRENADE, WEAPON_INCGRENADE, WEAPON_SMOKEGRENADE, WEAPON_TAGRENADE, WEAPON_MOLOTOV , WEAPON_DECOY };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_bomb(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_C4 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_pistol(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_GLOCK, WEAPON_ELITE, WEAPON_P250, WEAPON_TEC9, WEAPON_CZ75A, WEAPON_USP_SILENCER, WEAPON_HKP2000, WEAPON_FIVESEVEN };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_heavy_pistol(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_DEAGLE, WEAPON_REVOLVER };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_shotgun(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_NOVA, WEAPON_XM1014, WEAPON_SAWEDOFF, WEAPON_MAG7 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_heavy(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_M249, WEAPON_NEGEV };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_smg(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_MAC10, WEAPON_MP7, WEAPON_UMP45, WEAPON_P90, WEAPON_BIZON, WEAPON_MP9, WEAPON_MP5SD };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_rifle(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_AK47,WEAPON_AUG,WEAPON_FAMAS,WEAPON_GALILAR,WEAPON_M4A1,WEAPON_M4A1_SILENCER, WEAPON_SG556 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_sniper(void* weapon) {
	if (!weapon)
		return false;


	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_AWP, WEAPON_SSG08 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool is_auto_sniper(void* weapon) {
	if (!weapon)
		return false;

	auto current_weapon = reinterpret_cast<weapon_t*>(weapon);
	int id = current_weapon->item_definition_index();
	static const std::vector<int> v = { WEAPON_G3SG1, WEAPON_SCAR20 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

void get_aimbot_settings(void* weapon) {
	static int hitbox_num;

	if (is_pistol(weapon))
	{
		hitbox_num = c::aimbot::pistol_hitbox;
		aimbot_fov = c::aimbot::pistol_aimbot_fov;
		autowall_dmg = c::aimbot::pistol_autowall_dmg;
	}
	else if (is_heavy_pistol(weapon)) {
		hitbox_num = c::aimbot::heavy_pistol_hitbox;
		aimbot_fov = c::aimbot::heavy_pistol_aimbot_fov;
		autowall_dmg = c::aimbot::heavy_pistol_autowall_dmg;
	}
	else if (is_shotgun(weapon)) {
		hitbox_num = c::aimbot::shotgun_hitbox;
		aimbot_fov = c::aimbot::shotgun_aimbot_fov;
		autowall_dmg = c::aimbot::shotgun_autowall_dmg;
	}
	else if (is_heavy(weapon)) {
		hitbox_num = c::aimbot::heavy_hitbox;
		aimbot_fov = c::aimbot::heavy_aimbot_fov;
		autowall_dmg = c::aimbot::heavy_autowall_dmg;
	}
	else if (is_smg(weapon)) {
		hitbox_num = c::aimbot::smg_hitbox;
		aimbot_fov = c::aimbot::smg_aimbot_fov;
		autowall_dmg = c::aimbot::smg_autowall_dmg;
	}
	else if (is_rifle(weapon)) {
		hitbox_num = c::aimbot::rifle_hitbox;
		aimbot_fov = c::aimbot::rifle_aimbot_fov;
		autowall_dmg = c::aimbot::rifle_autowall_dmg;
	}
	else if (is_sniper(weapon)) {
		hitbox_num = c::aimbot::sniper_hitbox;
		aimbot_fov = c::aimbot::sniper_aimbot_fov;
		autowall_dmg = c::aimbot::sniper_autowall_dmg;
	}
	else if (is_auto_sniper(weapon)) {
		hitbox_num = c::aimbot::autosniper_hitbox;
		aimbot_fov = c::aimbot::autosniper_aimbot_fov;
		autowall_dmg = c::aimbot::autosniper_autowall_dmg;
	}

	switch (hitbox_num) {
	case 0:
		hitbox = hitbox_head;
		break;
	case 1:
		hitbox = hitbox_neck;
		break;
	case 2:
		hitbox = hitbox_chest;
		break;
	case 3:
		hitbox = hitbox_pelvis;
		break;
	}
}

bool can_fire(weapon_t* weap, c_usercmd* cmd) {
	float flServerTime = (float)(g::local->get_tick_base() * interfaces::globals->interval_per_tick);

	if (g::local->next_attack() < flServerTime) {
		return (weap->next_primary_attack() < flServerTime);
	}
	return false;
}

bool hitscan(vec3_t eye_pos, player_t* player, vec3_t& ret_hitbox, float minimum_damage, float minimum_damage_visible) {
	float mindmg = min(minimum_damage, player->health());
	float mindmgvis = min(minimum_damage_visible, player->health());
	float currdmg = 0;
	vec3_t currhitbox = vec3_t{};

	std::vector<int> hitbox_ints;

	hitbox_ints.push_back(hitbox);

	std::vector<vec3_t> hitbox_points, head_multipoint, all_points;
	if (hitbox_ints.size()) {
		for (auto muie_snek : hitbox_ints) {
			hitbox_points.push_back(player->get_hitbox_position(muie_snek));
		}
		for (auto cacat : hitbox_points) {
			all_points.push_back(cacat);
		}
	}

	bool visible = false;
	if (all_points.size()) {
		for (auto hitbox : all_points) {
			float damage = autowall::damage(hitbox);
			if (damage > currdmg) {
				currdmg = damage;
				currhitbox = hitbox;
				visible = false;
				if (g::local->can_see_player_pos(player, hitbox))
					visible = true;
			}
		}

		float bestdmg = visible ? mindmgvis : mindmg;
		if (currdmg > bestdmg && currhitbox.x != 0.f && currhitbox.y != 0.0f) {
			ret_hitbox = currhitbox;
			return true;
		}
	}

	return false;
}

vec3_t calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewangles) {
	vec3_t delta = source - destination;
	vec3_t angles;
	angles.x = math::rad2deg(atanf(delta.z / std::hypotf(delta.x, delta.y))) - viewangles.x;
	angles.y = math::rad2deg(atanf(delta.y / delta.x)) - viewangles.y;
	angles.z = 0.0f;

	if (delta.x >= 0.0)
		angles.y += 180.0f;

	angles.normalize();
	return angles;
}

static inline int aimbone;
int get_nearest_bone(player_t* entity, c_usercmd* user_cmd) {
	auto local_player = reinterpret_cast<player_t*>(interfaces::ent_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)
		return false;

	float best_dist = 360.f;

	matrix_t matrix[MAXSTUDIOBONES];

	if (!entity->setup_bones(matrix, 128, BONE_USED_BY_HITBOX, 0.0f))
		return -1;

	studio_hdr_t* studio_model = interfaces::model_info->get_studio_model(entity->model());
	if (!studio_model)
		return -1;

	studio_hitbox_set_t* set = studio_model->hitbox_set(entity->hitbox_set());
	if (!set)
		return -1;

	for (int i = 0; i < set->hitbox_count; i++) {
		if (i >= hitbox_max)
			continue;

		studio_box_t* hitbox = set->hitbox(i);

		if (!hitbox)
			continue;

		vec3_t angle = calculate_angle(local_player->get_eye_pos(), vec3_t(matrix[hitbox->bone][0][3], matrix[hitbox->bone][1][3], matrix[hitbox->bone][2][3]), user_cmd->view_angles);
		float this_dist = std::hypotf(angle.x, angle.y);

		if (best_dist > this_dist) {
			best_dist = this_dist;
			aimbone = hitbox->bone;
			continue;
		}
	}
	return aimbone;
}



player_t* get_best_target(c_usercmd* cmd) {
    float ofov = aimbot_fov;
    float nfov = 0;
    player_t* target = nullptr;

    for (int i = 0; i < interfaces::globals->max_clients; i++) {
        auto player = reinterpret_cast<player_t*>(interfaces::ent_list->get_client_entity(i));

        if (!player || player->dormant() || player == g::local || player->team() == g::local->team() ||
            !(player->is_alive() && player->health() > 0) || player->has_gun_game_immunity())
			continue;

        vec3_t eyepos = g::local->get_eye_pos();
        vec3_t position = player->get_hitbox_position(hitbox);


        auto entity_bone_pos = player->get_bone_position(get_nearest_bone(player, cmd));
        auto angle = calculate_angle(g::local->get_eye_pos(), entity_bone_pos, cmd->view_angles);
        nfov = std::hypotf(angle.x, angle.y);

        if (nfov < ofov) {
            if (autowall_b && hitscan(eyepos, player, position, autowall_dmg, 1.f)) {
                ofov = nfov;
                target = player;
            }
            else if (!autowall_b && g::local->can_see_player_pos(player, player->get_eye_pos())) {
                ofov = nfov;
                target = player;
            }
        }
    }
    return target;
}

void aimbot::run(c_usercmd* cmd) {
	if (!c::aimbot::aimbot || !g::local->is_alive() || !GetAsyncKeyState(c::aimbot::aimbot_key))
		return;

	auto weapon = g::local->active_weapon();
	if (!is_rifle(weapon) && !is_shotgun(weapon) && !is_heavy_pistol(weapon) && !is_auto_sniper(weapon) && !is_pistol(weapon) && !is_sniper(weapon) && !is_smg(weapon) && !is_heavy(weapon))
		return;

	get_aimbot_settings(weapon);

	player_t* target = get_best_target(cmd);

	static auto weapon_recoil_scale = interfaces::console->get_convar("weapon_recoil_scale")->get_float();

	if (target) {
		vec3_t eyepos = g::local->get_eye_pos();
		vec3_t position;

		if (c::backtrack::backtrack && c::aimbot::aim_at_bt) {
			int bone_id = 8;
			auto& record = backtrack.data[target->index()];

			if (auto modelStudio = interfaces::model_info->get_studio_model(target->model()); modelStudio != nullptr) {
				auto hitboxSet = modelStudio->hitbox_set(0);

				if (hitboxSet != nullptr) {
					auto hitbox_ = hitboxSet->hitbox(hitbox);

					if (hitbox_ != nullptr) {
						bone_id = hitbox_->bone;
					}
				}
			}

			float best_record = FLT_MAX;
			int best_index = -1;

			for (int j = 0; j < static_cast<int>(record.size()) - 2; j++) {
				auto& a = record[j];
				auto angle_a = calculate_angle(g::local->get_eye_pos(), a.m_matrix[bone_id].get_origin(), cmd->view_angles);
				auto hypot_a = angle_a.length_2d();

				if (hypot_a < best_record) {
					best_record = hypot_a;
					best_index = j;
				}
			}

			if (best_index != -1) {
				position = record[best_index].m_matrix[bone_id].get_origin();
			}
			else {
				position = target->get_hitbox_position(hitbox);
			}
		}
		else {
			position = target->get_hitbox_position(hitbox);
		}

		vec3_t viewangles = math::calc_angle(eyepos, position);
		viewangles.clamp();
		vec3_t delta = cmd->view_angles - viewangles;
		delta.clamp();
		vec3_t finalang = cmd->view_angles - delta;
		finalang.clamp();

		if ((can_fire(weapon, cmd) && GetAsyncKeyState(c::aimbot::aimbot_key) && !c::aimbot::non_sticky_aimbot) || (can_fire(weapon, cmd) && GetAsyncKeyState(c::aimbot::aimbot_key) && c::aimbot::non_sticky_aimbot && cmd->buttons & in_attack)) {
			cmd->view_angles = finalang - (g::local->aim_punch_angle() * weapon_recoil_scale);

			if (!c::aimbot::aimbot_silent)
				interfaces::engine->set_view_angles(cmd->view_angles);
		}
	}
}
